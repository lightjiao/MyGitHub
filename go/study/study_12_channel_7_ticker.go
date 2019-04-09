package main

import (
	"fmt"
	"time"
)

// 通道与定时器的一些巧妙用法

// 1、 time.Ticker 结构体，这个对象以指定的时间间隔重复的向通道 time.Ticker.C 发送时间值

func main() {
	ticker := time.NewTicker(1e9)
	defer ticker.Stop()

	ch := make(chan int)
	go func() {
		for {
			time.Sleep(1e9)
			ch <- 1
		}
	}()

	go func() {
		for {
			select {
			case i := <-ch:
				fmt.Println(i)
			case <-ticker.C: // 一般用于定时的处理信息
				fmt.Println("this is timer ticker")
			}
		}
	}()

	time.Sleep(5 * 1e9)
}
