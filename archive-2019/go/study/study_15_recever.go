package main

import (
	"fmt"
	"reflect"
)

// 11.6是用方法集与接口 https://github.com/Unknwon/the-way-to-go_ZH_CN/blob/master/eBook/11.6.md
// 区分作用在变量上的方法与作用在

/*
作用于变量上的方法实际上是不区分变量到底是指针还是值的。
当碰到接口类型值时，这会变得有点复杂，原因是接口变量中存储的具体值是不可寻址的.

总结:

在接口上调用方法时，必须有和方法定义时相同的接收者类型或者是可以从具体类型 P 直接可以辨识的：

指针方法可以通过指针调用
值方法可以通过值调用
接收者是值的方法可以通过指针调用，因为指针会首先被解引用
接收者是指针的方法不可以通过值调用，因为存储在接口中的值没有地址
将一个值赋值给一个接口时，编译器会确保所有可能的接口方法都可以在此值上被调用，因此不正确的赋值在编译期就会失败。

译注

Go 语言规范定义了接口方法集的调用规则：

类型 *T 的可调用方法集包含接受者为 *T 或 T 的所有方法集
类型 T 的可调用方法集包含接受者为 T 的所有方法
类型 T 的可调用方法集不包含接受者为 *T 的方法
*/

// 代码示例

type List []int
func (l List) Len() int        { return len(l) }
func (l *List) Append(val int) { *l = append(*l, val) }

type Appender interface {
	Append(int)
}
func CountInto(a Appender, start, end int) {
	for i := start; i <= end; i++ {
		a.Append(i)
	}
}

func main() {
	var x float64 = 3.4
	fmt.Println("type:", reflect.TypeOf(x))
	v := reflect.ValueOf(x)
	fmt.Println("value:", v)
	fmt.Println("type:", v.Type())
	fmt.Println("kind:", v.Kind())
	fmt.Println("value:", v.Float())
	fmt.Println(v.Interface())
	fmt.Printf("value is %5.2e\n", v.Interface())
	y := v.Interface().(float64)
	fmt.Println(y)
}