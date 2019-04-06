package main

import (
	"fmt"
)

// close 之后读取channel
func readClosedNoBufChannel() {
	// 读取关闭的无缓存通道：
	// 读取关闭后的无缓存通道，不管通道中是否有数据，返回值都为0和false。
	ch := make(chan int)
	go func() { ch <- 1 }() // 向通道中发送值并不会改变「读取关闭之后的无缓冲通道」的结果
	//time.Sleep(3*1e9)
	close(ch)
	for i := 1; i <= 3; i++ {
		t, ok := <-ch
		fmt.Println(t, ok) // print int 0, and result is false
	}
}

func readClosedHasBuffChannel() {
	// 读取关闭的有缓存通道：
	// 读取关闭后的有缓存通道，将缓存数据读取完后，再读取返回值为0和false。
	ch2 := make(chan int, 3)
	ch2 <- 1
	ch2 <- 2
	ch2 <- 3
	close(ch2)
	for i := 0; i < 10; i++ {
		t, ok := <-ch2
		fmt.Println(t, ok)
	}
}

func main() {
	readClosedNoBufChannel()
	readClosedHasBuffChannel()
}
