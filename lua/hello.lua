--[[
Lua的数字只有double型，64bits，你不必担心Lua处理浮点数会慢（除非大于100,000,000,000,000），或是会有精度问题。
你可以以如下的方式表示数字，0x开头的16进制和C是很像的。

布尔类型只有nil和false是 false，数字0啊，‘’空字符串（’\0’）都是true！

另外，需要注意的是：lua中的变量如果没有特殊说明，全是全局变量，那怕是语句块或是函数里。变量前加local关键字的是局部变量。
theGlobalVar = 50
local theLocalVar = "local variable"

Lua没有++或是+=这样的操作

]] --
-- while 循环
sum = 0
num = 1
while num <= 100 do
    sum = sum + num
    num = num + 1
end
print("sum =", sum)

-- if语句
-- 1）不等于是“～=”，而不是!=
-- 2）io库的分别从stdin和stdout读写的read和write函数
-- 3）字符串的拼接操作符“..”
age = 4
sex = "Male"
if age == 40 and sex == "Male" then
    print("男人四十一枝花")
elseif age > 60 and sex ~= "Female" then
    print("old man without country!")
elseif age < 20 then
    io.write("too young, too naive!\n")
else
    local age = io.read()
    print("Your age is " .. age)
end

-- for 循环
sum = 0
for i = 1, 100 do -- i = 1; i< 100; i++
    sum = sum + i
end
print(sum)
sum = 0
for i = 1, 100, 2 do -- i = 1; i< 100; i+=2
    sum = sum + i
end
print(sum)
sum = 0
for i = 100, 1, -2 do -- i = 1; i< 100; i-=2
    sum = sum + i
end
print(sum)

-- untile循环 (do while吧)
sum = 2
repeat
    sum = sum ^ 2 -- 幂操作 --    print(sum)
until sum > 1000
print(sum)

-- 函数

-- 递归
function fib(n)
    if n < 2 then return 1 end
    return fib(n - 2) + fib(n - 1)
end
print(fib(3))

-- 闭包
function newCounter()
    local i = 0
    return function() -- anonymous function
        i = i + 1
        return i
    end
end
c1 = newCounter()
print(c1()) -- > 1
print(c1()) -- > 2

function myPower(x) return function(y) return y ^ x end end
power2 = myPower(2)
power3 = myPower(3)

print(power2(4)) -- 4的2次方
print(power3(5)) -- 5的3次方

-- Table
haoel = {name = "ChenHao", age = 37, handsome = True}
haoel.website = "123"
aaa = haoel.website
haoel.website = "https://coolshell.cn/"
local age = haoel.age
haoel.handsome = false
haoel.name = nil
print(haoel)

t = {[20] = 100, ['name'] = "ChenHao", [3.14] = "PI"}
print(t.name)
print(t[20])
print(t[3.14])

-- Table的数组 -- ! 下标竟然是从1开始的嘛?
arr = {10, 20, 30, 40, 50} -- 等价于 arr = {[1] = 10, [2] = 20, [3] = 30, [4] = 40, [5] = 50}
-- 所以，你也可以定义成不同的类型的数组，比如：
arr = {"string", 100, "haoel", function() print("coolshell.cn") end}
print(arr[4]())
for i = 1, #arr do print(arr[i]) end -- #{数组变量名} 表示数组的长度

-- ! 如果没有local关键字，全都是全局变量，Lua也是用Table来管理全局变量的，Lua把这些全局变量放在了一个叫“_G”的Table里。
print("\n##################\nthe _G and #")
for i = 1, #_G.arr do print(arr[i]) end

-- !我们可以通过下面的方式来遍历一个Table。
for k, v in pairs(t) do print(k, v) end
for key, value in pairs(_G) do print(key, value) end

-- !MetaTable 和 MetaMethod
-- !MetaTable 和 MetaMethod 是Lua中的重要的语法，MetaTable主要是用来做一些类似于C++重载操作符式的功能。
print("\n------------- MetaTable 和 MetaMethod")
-- 用table记录两个分数
fraction_a = {numerator = 2, denominator = 3}
fraction_b = {numerator = 4, denominator = 7}
-- 如何实现分数的相加
fraction_op = {}
function fraction_op.__add(f1, f2)
    ret = {}
    ret.numerator = f1.numerator * f2.denominator + f2.numerator *
                        f1.denominator
    ret.denominator = f1.denominator * f2.denominator
    return ret
end
-- 为之前定义的两个table设置MetaTable：（其中的setmetatble是库函数）
setmetatable(fraction_a, fraction_op)
setmetatable(fraction_b, fraction_op)
-- 于是你就可以这样干了：（调用的是fraction_op.__add()函数）
fraction_s = fraction_a + fraction_b
for key, value in pairs(fraction_s) do print(key, value) end

-- 至于__add这是MetaMethod，这是Lua内建约定的，其它的还有如下的MetaMethod：
--[[
__add(a, b)                     对应表达式 a + b
__sub(a, b)                     对应表达式 a - b
__mul(a, b)                     对应表达式 a * b
__div(a, b)                     对应表达式 a / b
__mod(a, b)                     对应表达式 a % b
__pow(a, b)                     对应表达式 a ^ b
__unm(a)                        对应表达式 -a
__concat(a, b)                  对应表达式 a .. b
__len(a)                        对应表达式 #a
__eq(a, b)                      对应表达式 a == b
__lt(a, b)                      对应表达式 a < b
__le(a, b)                      对应表达式 a <= b
__index(a, b)                   对应表达式 a.b
__newindex(a, b, c)             对应表达式 a.b = c
__call(a, ...)                  对应表达式 a(...)
]]

print("\n------------- “面向对象基础”")
-- “面向对象”
-- 所谓__index，说得明确一点，如果我们有两个对象a和b，我们想让b作为a的prototype只需要：
-- setmetatable(a, {__index = b})
Window_Prototype = {x = 0, y = 0, width = 100, height = 100}
MyWin = {title = "Hello"}
setmetatable(MyWin, {__index = Window_Prototype}) -- 这个行为更像是trait
-- print(MyWin.Window_Prototype.x)
print(MyWin.x)
-- 当表要索引一个值时如table[key], Lua会首先在table本身中查找key的值, 如果没有并且这个table存在一个带有__index属性的Metatable, 则Lua会按照__index所定义的函数逻辑查找

-- “trait”冲突了会怎样, "trait" 只能有一个，后面的会覆盖前面的
trait_1 = {name = "trait_1", age = 233}
trait_2 = {name = "trait_2"}
setmetatable(MyWin, {__index = trait_1})
setmetatable(MyWin, {__index = trait_2})
print(MyWin.x)
print(MyWin.name)
print(MyWin.age)

print("\n------------- “面向对象正式开始”")
-- “面向对象正式开始”
Person = {}
function Person:new(p)
    local obj = p
    if (obj == nil) then obj = {name = "ChenHao", age = 37, handsome = true} end
    self.__index = self
    return setmetatable(obj, self)
end

function Person:toString()
    return self.name .. " : " .. self.age .. " : " ..
               (self.handsome and "handsome" or "ugly")
end
--[[
1）self 就是 Person，Person:new(p)，相当于Person.new(self, p)
2）new方法的self.__index = self 的意图是怕self被扩展后改写，所以，让其保持原样
3）setmetatable这个函数返回的是第一个参数的值。
]]

-- 于是：我们可以这样调用：
me = Person:new()
print(me:toString())

kf = Person:new{name = "King's fucking", age = 70, handsome = false}
print(kf:toString())
