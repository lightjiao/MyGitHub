#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Lights Jiao'

' url handlers '
import time, re, hashlib, json, logging, asyncio
from aiohttp import web

import markdown2

from coroweb import get, post
from models  import User, Blog, Comment, next_id
from apis    import APIError, APIValueError, APIPermissionError, APIResourceNotFoundError
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


def text2html(text):
    lines = map(lambda s: '<p>%s</p>' % s.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;'),filter(lambda s: s.strip() != '', text.split('\n')))
    #拆分一下？
    return ''.join(lines) # 这是什么意思，连接list行数据变成一个html？


#################### web页面的映射  ####################
#测试页面，展示用户
@get('/test')
async def test(request):
    users = await User.findAll()
    return {
        '__template__':'test.html',
        'users':users
    }


#示例页面，展示最简单的博客页面
@get('/')
async def index(request):
    blogs = await Blog.findAll()

    return {
        '__template__':'blogs.html',
        'blogs':blogs
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


#登出操作？
@get('/signout')
async def signout(request):
    referer = request.heafers.get('Referer')
    r = web.HTTPFound(referer or '/')
    r.set_cookie(COOKIE_NAME, '-deleted-', max_age=0, httponly=True)
    logging.info('user signed out.')
    return r


#博客页面
@get('/blog/{id}')
async def getBlog(id):
    blog     = await Blog.find(id)
    comments = await Comment.findAll('blog_id=?', [id], orderby='created_at desc')
    for c in comments:
        c.heml_content = text2html(c.content)
    blog.html_content = markdown2.markdown(blog.content)
    return {
        '__template__':'manage_blog_edit.html',  # 次数需要替换成真正的html页
        'blog':blog,
        'comments':comments
    }

#创建博客的页面
@get('/manage/blogs/create')
async def manageBlogCreate():
    return {
        '__template__':'manage_blog_edit.html',
        'id':'',
        'action':'/api/blogs'
    }


####################### 页面的API #######################
#一个简单的API，获取用户名
@get('/api/test')
async def API_GetUser():
    users = await User.findAll(orderby='created_at desc')
    for u in users:
        u.passwd = '******'
    return dict(users = users)


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
    return blog
















