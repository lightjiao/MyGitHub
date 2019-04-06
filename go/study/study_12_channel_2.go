package main

import (
	"fmt"
	"time"
)

// 验证 <-ch 语法的描述： 可以单独调用获取通道的（下一个）值，当前值会被丢弃，但是可以用来验证

func pushChan(ch chan int) {
	for i := 0; i < 10; i++ {
		ch <- i
	}
}

// out put 123456789
func main() {
	ch := make(chan int)
	go pushChan(ch)

	<-ch // the 0 number will be deprecated
	go func() {
		for {
			fmt.Print(<-ch)
		}
	}()

	time.Sleep(2 * 1e9)
}
