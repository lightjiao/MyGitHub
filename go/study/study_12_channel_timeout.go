package main

import (
	"fmt"
	"time"
)

// channel 配合 timer 习惯用法，限制超时调用
func main() {
	timeout:= make(chan int)
	go func() {
		time.Sleep(3e9) // 限制一秒超时
		timeout<-1
	}()

	ch := make(chan int)
	go func() {
		for {
			time.Sleep(5e8)
			ch <- 99
		}
	}()

	go func() {
		for {
			select {
			case <-timeout:
				fmt.Println("time out")
				return
			case i := <-ch:
				fmt.Println("the number i: ", i)
			}
		}
	}()

	time.Sleep(5e9)
}