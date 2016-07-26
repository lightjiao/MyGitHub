#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#用type()函数动态的创建一个类
def fn(self, name = 'World'):
    print('Hello, %s.' % name)
Hello = type('Hello', (object,), dict(hello = fn))


#使用元类:
#metaclass
#除了使用type()动态创建类以外，要控制类的创建行为，还可以使用metaclass。
#metaclass，直译为元类，简单的解释就是：
#当我们定义了类以后，就可以根据这个类创建出实例，所以：先定义类，然后创建实例。
#但是如果我们想创建出类呢？那就必须根据metaclass创建出类，所以：先定义metaclass，然后创建类。
#连接起来就是：先定义metaclass，就可以创建类，最后创建实例。
#所以，metaclass允许你创建类或者修改类。换句话说，你可以把类看成是metaclass创建出来的“实例”。
#metaclass是Python面向对象里最难理解，也是最难使用的魔术代码。

class ListMetaclass(type):#metaclass 是类的模板, 所以必须从type 类型派生
    def __new__(cls, name, bases, attrs):
        attrs['add'] = lambda self, value: self.append(value)
        return type.__new__(cls, name, bases, attrs)

class MyList(list, metaclass = ListMetaclass):
    pass

#ORM全称“Object Relational Mapping”，即对象-关系映射，就是把关系数据库的一行映射为一个对象，也就是一个类对应一个表，这样，写代码更简单，不用直接操作SQL语句。
#要编写一个ORM框架，所有的类都只能动态定义，因为只有使用者才能根据表的结构定义出对应的类来。
#让我们来尝试编写一个ORM框架。

class Field(object):
    def __init__(self, name, column_type):
        self.name = name
        self.column_type = column_type

    def __str__(self):
        return '<%s:%s>' % (self.__class__.__name__, self.name)

class StringField(Field):
    def __init__(self, name):
        super(StringField, self).__init__(name, 'varchar(100)')

class IntegerField(Field):
    def __init__(self, name):
        super(IntegerField, self).__init__(name, 'bigint')

class ModelMetaclass(type):
    def __new__(cls, name, bases, attrs):
        if name == 'Model':
            return type.__new__(cls, name, bases, attrs)

        mappings = dict()

        for k, v in attrs.items():
            if isinstance(v, Field):
                print('Found mappind:%s==>%s' % (k, v))
                mappings[k] = v

        for k in mappings.keys():
            attrs.pop(k)

        attrs['__mappings__'] = mappings #保存属性和列的映射关系
        attrs['__table__'] = name #假设表名 和 类名 一致
        return type.__new__(cls, name, bases, attrs)

class Model(dict, metaclass = ModelMetaclass):
    def __init__(self, **kw):
        super(Model, self).__init__(**kw)

    def __getattr__(self, key):
        try:
            return self[key]
        except KeyError:
            raise AttributeError(r"'model' object has no attribute '%s'" % key)

    def __setattr__(self, key, value):
        self[key] = value

    def save(self):
        fields = []
        params = []
        args   = []
        for k, v in self.__mappings__.items():
            fields.append(v.name)
            params.append('?')
            #args.append(getattr(self, k, None))
            args.append(getattr(self, k))

        sql = 'insert into %s (%s) value (%s)' % (self.__table__, ','.join(fields), ','.join(params))
        print('SQL:%s'  % sql)
        print('ARGS:%s' % str(args))


class User(Model):
    # 定义类的属性到列的映射：
    id       = IntegerField('id')
    name     = StringField('username')
    email    = StringField('email')
    password = StringField('password')

u = User(id=12345, name='Michael', email='test@orm.org', password='my-pwd')
u.save()