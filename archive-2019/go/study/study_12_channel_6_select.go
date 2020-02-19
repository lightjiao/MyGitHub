package main

import (
	"fmt"
	"time"
)

// 验证channel 的select 以及default 的输出时机


func send(ch chan int) {
	for i := 0; ; i++ {
		ch <- i
	}
}

func selectRecv(ch1, ch2 chan int) {
	j := 1
	for {
		select {
		case i := <-ch1:
			fmt.Println("this is ch1, and number is: ", i)
		case i := <-ch2:
			fmt.Println("this is ch2, and number is: ", i)
		// ch1 和 ch2 的阻塞时间其实不多，1秒钟时间，ch1和ch2打印结果都在9w级别，default打印结果再12w左右，差距不大
		default:
			println("this is default, and number is: ", j)
			j++
		}
	}
}

func main() {
	ch1 := make(chan int)
	ch2 := make(chan int)
	go send(ch1)
	go send(ch2)
	go selectRecv(ch1, ch2)

	time.Sleep(1e9)
}
