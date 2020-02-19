package main

import (
	"fmt"
	"time"
)

// 一道经典面试题, @see https://www.v2ex.com/t/552620

func echoByte(b byte, begin, end chan bool) {
	for i := 0; i < 10; i++ {
		<-begin
		fmt.Printf("%c", b)
		end <- true
	}
}

func main() {
	AChan := make(chan bool)
	BChan := make(chan bool)
	CChan := make(chan bool)

	go echoByte('A', AChan, BChan)
	go echoByte('B', BChan, CChan)
	go echoByte('C', CChan, AChan)

	AChan <- true
	time.Sleep(1e9) // how to remove this sleep
}
