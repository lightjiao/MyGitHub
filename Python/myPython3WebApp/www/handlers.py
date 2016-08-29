#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Lights Jiao'

' url handlers '
import time, re, hashlib, json, logging, asyncio
from aiohttp import web

import markdown2

from coroweb import get, post
from models  import User, Blog, Comment, next_id
from apis    import APIError, APIValueError, APIPermissionError, APIResourceNotFoundError, Page
from config  import configs

#################### 一些算法，比如cookie加密 ####################
_RE_EMAIL = re.compile(r'^[a-z0-9\.\-\_]+\@[a-z0-9\-\_]+(\.[a-z0-9\-\_]+){1,4}$')
_RE_SHA1  = re.compile(r'^[0-9a-f]{40}$') #what is this?

COOKIE_NAME = 'awesession'
_COOKIE_KEY = configs.session.secret

#计算加密cookie
def user2cookie(user, max_age):
    # build cookie string by: id-expires-sha1
    expires = str(int(time.time() + max_age))
    s = '%s-%s-%s-%s' % (user.id, user.passwd, expires, _COOKIE_KEY)
    L = [user.id, expires, hashlib.sha1(s.encode('utf-8')).hexdigest()]
    return '-'.join(L)

#计算解密cookie
async def cookie2user(cookie_str):
    '''
    Parse cookie and load user if cookie is valid
    '''
    if not cookie_str:
        return None
    try:
        L = cookie_str.split('-')
        if len(L) != 3:
            return None
        uid, expires, sha1 = L
        if int(expires) < time.time():
            return None
        user = await User.find(uid)
        if user is None:
            return None
        s = '%s-%s-%s-%s' % (uid, user.passwd, expires, _COOKIE_KEY)
        if sha1 != hashlib.sha1(s.encode('utf-8')).hexdigest():
            logging.info('invalid sha1')
            return None
        user.passwd = '******'
        return user
    except Exception as e:
        logging.exception(e)
        return None


#检查管理员权限
def checkAdmin(request):
    if request.__user__ is None or not request.__user__.admin:
        raise APIPermissionError()


#将评论内容拼接成html格式
def text2html(text):
    lines = map(lambda s: '<p>%s</p>' % s.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;'),filter(lambda s: s.strip() != '', text.split('\n')))
    #拆分一下？
    return ''.join(lines) # 这是什么意思，连接list行数据变成一个html？


#获取页码
def getPageIndex(page_str):
    p = 1
    try:
        p = int(page_str)
    except ValueError as e:
        pass
    if p < 1:
        p = 1
    return p


########################## web页面的映射 ############################
########################## 用户浏览页面URL ##########################
#主页面
@get('/')
async def index(*, page = '1'):
    page_index = getPageIndex(page)
    num = await Blog.findNumber('count(id)')
    page = Page(num)
    if num == 0:
        blogs = []
    else:
        blogs = await Blog.findAll(orderby='created_at desc', limit=(page.offset, page.limit))
    return {
        '__template__':'blogs.html',
        'blogs':blogs,
        'page':page
    }

#注册页面
@get('/register')
async def register():
    return {
        '__template__':'register.html'
    }

#登录页面
@get('/signin')
async def signin():
    return {
        '__template__':'signin.html'
    }

#登出操作
@get('/signout')
async def signout(request):
    referer = request.heafers.get('Referer')
    r = web.HTTPFound(referer or '/')
    r.set_cookie(COOKIE_NAME, '-deleted-', max_age=0, httponly=True)
    logging.info('user signed out.')
    return r

#博客详情页面
@get('/blog/{id}')
async def getBlog(id):
    blog     = await Blog.find(id)
    comments = await Comment.findAll('blog_id=?', [id], orderby='created_at desc')
    for c in comments:
        c.heml_content = text2html(c.content)
    blog.html_content = markdown2.markdown(blog.content)
    return {
        '__template__':'blog.html',  # 次数需要替换成真正的html页
        'blog':blog,
        'comments':comments
    }


########################## 管理员管理URL ############################
@get('/manage')
def manage(*, page= '1'):
    return 'redirect:/manage/blogs'


#评论列表
@get('/manage/comments')
def manageComments(*, page='1'):
    return {
        '__template__':'manage_comments.html',
        'page_index':getPageIndex(page)
    }


#博客列表
@get('/manage/blogs')
def manageBlogs(*, page='1'):
    return {
        '__template__': 'manage_blogs.html',
        'page_index': getPageIndex(page)
    }


#创建博客的页面
@get('/manage/blogs/create')
async def manageBlogCreate():
    return {
        '__template__':'manage_blog_edit.html',
        'id':'',
        'action':'/api/blogs'
    }


#修改博客的页面
@get('/manage/blogs/edit')
async def manageBlogEdit(*, id):
    return {
        '__template__':'manage_blog_edit.html',
        'id':id,
        'action':'/api/blogs/%s' % id
    }


#用户列表页
@get('/manage/users')
async def manageUsers(*, page = '1'):
    return {
        '__template__':'manage_users.html',
        'page_index':getPageIndex(page)
    }




########################################################
####################### 页面的API #######################
########################################################
#注册的API
#写一个修饰器 修饰函数调用时候 打印函数名和入参
@post('/api/userRegister')
async def API_UserRegister(*, email, name, passwd):
    if not name or not name.strip():
        raise APIValueError('name')
    if not email or not _RE_EMAIL.match(email):
        raise APIValueError('email')
    if not passwd or not _RE_SHA1.match(passwd):
        raise APIValueError('passwd')

    users = await User.findAll('email = ?', [email])
    if len(users) > 0:
        raise APIError('register:failed', 'email', 'Email is already in use.')
    uid = next_id()

    sha1_passwd = '%s:%s' % (uid, passwd)

    user = User(
        id      = uid,
        name    = name.strip(),
        email   = email,
        passwd  = hashlib.sha1(sha1_passwd.encode('utf-8')).hexdigest(),
        image   = ''#''http://www.gravatar.com/avatar/%s?d=mm&s=120' % hashlib.md5(email.encode('utf-8')).hexdigest(), #???
    )
    await user.save()

    #make session cookie:
    r = web.Response()
    r.set_cookie(COOKIE_NAME, user2cookie(user, 86400), max_age=86400, httponly=True)
    user.passwd = '******'
    r.content_type = 'application/json'
    r.body = json.dumps(user, ensure_ascii=False).encode('utf-8')
    return r


#登录的API
@post('/api/userSignin')
async def API_UserSignin(*, email, passwd):
    if not email:
        raise APIValueError('email', 'Invalid email.')
    if not passwd:
        raise APIValueError('passwd', 'Invalid passwd.')

    users = await User.findAll('email=?' , [email])
    if len(users) == 0:
        raise APIValueError('email', 'Email not exist.')
    user = users[0]

    # check passwd:
    sha1 = hashlib.sha1()
    sha1.update(user.id.encode('utf-8'))
    sha1.update(b':')
    sha1.update(passwd.encode('utf-8'))

    logging.info('API_UserSignin checkParam: email:%s, passwd:%s, sha1:%s' % (user.email, user.passwd, sha1.hexdigest()))
    if user.passwd != sha1.hexdigest():
        raise APIValueError('passwd', 'Invalid password')

    #set cookie
    r = web.Response()
    r.set_cookie(COOKIE_NAME, user2cookie(user, 86400), max_age=86400, httponly=True)
    user.passwd = '******'
    r.content_type = 'application/json'
    r.body = json.dumps(user, ensure_ascii=False).encode('utf-8')
    return r

#获取用户列表的API
@get('/api/users')
async def API_Users(*, page = '1'):
    page_index = getPageIndex(page)
    num = await User.findNumber('count(id)')
    p = Page(num, page_index)
    if num == 0:
        return dict(page=p, users=())
    users = await User.findAll(orderby='created_at desc', limit=(p.offset, p.limit))
    for u in users:
        u.passwd = '******'
    return dict(page=p, users= users)


#查看博客列表, 带分页功能
@get('/api/blogs')
async def API_Blogs(*, page = '1'):
    page_index = getPageIndex(page) # 只是由str转换成int并且判断一下0 而已
    num = await Blog.findNumber('count(id)')
    p = Page(num, page_index)
    if num == 0:
        return dict(page=p, blogs=())
    blogs = await Blog.findAll(orderby='created_at desc', limit=(p.offset, p.limit))
    return dict(page=p, blogs=blogs)


#获取博客的API
@get('/api/blogs/{id}')
async def API_GetBlog(*, id):
    blog = await Blog.find(id)
    return blog


#创建博客的API
@post('/api/blogs')
async def API_CreateBlog(request, *, name, summary, content):
    checkAdmin(request)
    if not name or not name.strip():
        raise APIValueError('name', 'name cannot be empty.')
    if not summary or not summary.strip():
        raise APIValueError('summary', 'summary cannot be empty.')
    if not content or not content.strip():
        raise APIValueError('content', 'content cannot be empty.')

    blog = Blog(
        user_id    = request.__user__.id,
        user_name  = request.__user__.name,
        user_image = request.__user__.image,
        name       = name.strip(),
        summary    = summary.strip(),
        content    = content.strip()
    )
    await blog.save()
    return blog #这里的返回值是做什么用处的？


#修改日志的API
@post('/api/blogs/{id}')
async def API_UpdateBlog(id, request, *, name, summary, content):
    checkAdmin(request)
    blog = await Blog.find(id)
    if not name or not name.strip():
        raise APIValueError('name', 'name cannot be empty.')
    if not summary or not summary.strip():
        raise APIValueError('summary', 'summary cannot be empty.')
    if not content or not content.strip():
        raise APIValueError('content', 'content cannot be empty.')

    blog.name = name.strip()
    blog.summary = summary.strip()
    blog.content = content.strip()
    await blog.update
    return blog #这里的返回值是做什么用处的？


#删除日志的API
@post('/api/blogs/{id}/delete')
async def API_DeleteBlog(request, *, id):
    checkAdmin(request)
    blog = await Blog.find(id)
    await blog.remove()
    return dict(id = id) #这里的返回值是做什么用处的？













