package main

import (
	"fmt"
	"time"
)

// 验证channel是何时被关闭的

func sendChan(ch chan int) {
	for i := 0; i < 10; i++ {
		ch <- i
	}
	close(ch) // 通道是需要显式的关闭
}

func recvChan(ch chan int) {
	for i := range ch {
		fmt.Println(i)
	}

	fmt.Println("recv end, because the ch is closed.")
}

func main() {
	ch := make(chan int)
	//theBlockCh := make(chan int)

	go sendChan(ch)
	go recvChan(ch)

	time.Sleep(1 *1e9)
	//close(ch) // 通道是需要显式的关闭
	//time.Sleep(1 *1e9)
}
