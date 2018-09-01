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

func main() {
	employee := new(employee)
	employee.salary = 100
	fmt.Print(employee.giveRaise(0.1))
}
