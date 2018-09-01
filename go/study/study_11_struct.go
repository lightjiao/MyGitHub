package main

import "fmt"

type student struct {
	name   string
	age    int
	height float32
}

// 结构体的方法
func (stu *student) isSingle() bool {
	return true
}

func initialization() {
	// new 初始化的是一个指针
	stuPoint := new(student)

	// 声明变量的是一个初始化0值的instance
	var stuInstance student

	fmt.Print(stuPoint, stuInstance)

	// 无论变量是一个结构体类型还是一个结构体类型指针，都使用同样的 选择器符（selector-notation） 来引用结构体的字段：
	fmt.Print(stuPoint.age, "\n")
	fmt.Print(stuInstance.age, "\n")
}

//练习 10.6 employee_salary.go
//定义结构体 employee，它有一个 salary 字段，给这个结构体定义一个方法 giveRaise 来按照指定的百分比增加薪水。

type employee struct {
	salary float32
}

func (employee *employee) giveRaise(percent float32) float32 {
	return employee.salary * (float32(1) + percent)
}

func main_2() {
	employee := new(employee)
	employee.salary = 100
	fmt.Print(employee.giveRaise(0.1))
}



//练习 10.8 inheritance_car.go - 练习go 的继承
//创建一个上面 Car 和 Engine 可运行的例子，并且给 Car 类型一个 wheelCount 字段和一个 numberOfWheels() 方法。
//创建一个 Mercedes 类型，它内嵌 Car，并新建 Mercedes 的一个实例，然后调用它的方法。
//然后仅在 Mercedes 类型上创建方法 sayHiToMerkel() 并调用它。

type Engine interface {
	start()
	stop()
}

type Car struct {
	Engine
	wheelCount int
}

func (car *Car) numberOfWheels() int {
	return car.wheelCount
}

func (car *Car) start() {
	return
}

func (car *Car) stop() {
	return
}

func (_ *Car) sayHiToMerkel(){
	fmt.Print("hi car")
}

type Mercedes struct {
	Car
}

func (_ *Mercedes) sayHiToMerkel(){
	fmt.Print("hi")
}

func main_3() {
	mercedes := new(Mercedes)
	mercedes.sayHiToMerkel()
	mercedes.start()
	mercedes.stop()
	fmt.Print(mercedes.numberOfWheels())

	car := new(Car)
	car.sayHiToMerkel()
}


//练习 10.11 magic.go：
//首先预测一下下面程序的结果，然后动手实验下：
type Base struct{}

func (*Base) Magic() {
	fmt.Println("base magic")
}

func (self *Base) MoreMagic() {
	self.Magic()
	self.Magic()
}

type Voodoo struct {
	Base
}

func (*Voodoo) Magic() {
	fmt.Println("voodoo magic")
}

func main() {
	v := new(Voodoo)
	v.Magic() // voodoo magic
	v.MoreMagic()  // base magic *2, TODO how can make it print voodoo magic ???
}