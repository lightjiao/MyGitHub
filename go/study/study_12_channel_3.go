package main

import (
	"fmt"
)

func f1(in chan int) {
	fmt.Println(<-in)
}

func main() {
	out := make(chan int)
	out <- 2 // 通道是阻塞的，没有接受者的通道会一直处于阻塞状态，此时主线程只有一个channel，并且处于阻塞状态，出现所有channel都是阻塞状态，导致panic
	go f1(out)
}