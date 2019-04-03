package main

import "fmt"

func test_1() {
	//defer fmt.Println("func: test_1")
	defer func() {
		fmt.Println("in the defer recover")
		err := recover()
		if err != nil {
			fmt.Printf("recover result: %v\n", err)
		}
	}()
	panic("this is a panic")
}

func test_2() {
	defer fmt.Println("func: test_2")
	test_1()
}

func main() {
	/* 打印结果
	panic: this is a panic
	func: test_1
	func: test_2
	 */
	 /*说明
	 在多层嵌套的函数调用中调用 panic，可以马上中止当前函数的执行，所有的 defer 语句都会保证执行并把控制权交还给接收到 panic 的函数调用者。
	 这样向上冒泡直到最顶层，并执行（每层的） defer，在栈顶处程序崩溃，并在命令行中用传给 panic 的值报告错误情况：这个终止过程就是 panicking
	 @see https://github.com/Unknwon/the-way-to-go_ZH_CN/blob/master/eBook/13.2.md
	  */
	test_2()
}
/*
Calling g.
Printing in g 0
Printing in g 1
Printing in g 2
Printing in g 3
Panicking!
 -- 这个没有 4
Defer in g 3
Defer in g 2
Defer in g 1
Defer in g 0
Recovered in f 4
Returned normally from f
 */