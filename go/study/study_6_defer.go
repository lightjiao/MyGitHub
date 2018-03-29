package main

import (
	"log"
	"io"
	"fmt"
)


// 使用defer记录函数的入参和出参
func func1(s string) (n int, err error) {
	defer func() {log.Printf("func1(%q) = %d, %v", s, n, err)}()

	return 7, io.EOF
}

// 使用defer实现代码追踪 - 一个基础但十分实用的实现代码执行追踪的方案就是在进入和离开某个函数打印相关的消息
func trace(s string) string {
	fmt.Println("entering:", s)
	return s
}

func un(s string) {
	fmt.Println("leaving:", s)
}

func funcA() {
	defer un(trace("funcA"))
	fmt.Println("in funcA")
}

func funcB() {
	defer un(trace("funcB"))
	fmt.Println("in funcB")
	funcA()
}

func main() {
	funcB()
}
