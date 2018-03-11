package main

import (
	"fmt"
	"strconv"
)

func hello() (a string) {
	return "hello world"
}

func funcIf(first int, cond int) {
	if first <= 0 {
		fmt.Printf("first is less than or equal to 0\n")
	} else if first > 0 && first < 5 {
		fmt.Printf("> 0 < 5\n")
	} else if cond == 0 {
		fmt.Printf("cond")
	}

	return
}

// 字符串和数字互相转换, 处理函数的错误返回
func functionReturnError() {
	var orig string = "111"
	var newS string

	fmt.Printf("The size of ins is: %d\n", strconv.IntSize)

	an, err := strconv.Atoi(orig)
	if err != nil {
		fmt.Printf("Orig %s is not an integer - exiting whith error\n", orig)
		return
	}

	fmt.Printf("The integer is %d\n", an)
	an = an + 5
	newS = strconv.Itoa(an)
	fmt.Printf("The new string is %s\n", newS)
}

// 循环体
func loop() {
	for i := 0; i < 15; i++ {
		fmt.Printf("loop: %d\n", i)
	}
}

func loop_2() {
	for i := 0; i < 25; i++ {
		for j := 0; j < i; j++ {
			fmt.Printf("G")
		}
		fmt.Printf("\n")
	}
}

// loop
func loop_2_2() {
	str := ""
	for i := 0; i < 15; i++ {
		str += "G"
		fmt.Printf("%s\n", str)
	}
}

// switch case && loop
func loop_3() {
	for i := 0; i < 100; i++ {
		switch {
		case i%15 == 0:
			fmt.Println("FizzBuzz")
		case i%3 == 0:
			fmt.Println("Fizz")
		case i%5 == 0:
			fmt.Println("Buzz")
		default:
			fmt.Println(i)
		}
	}
}

// 死循环
func loop_4() {
	i := 10
	for i > 0 {
		i = i - 1
		fmt.Println(i)
	}
}

func main() {
	loop_4()
}
