package main

import (
	"fmt"
	"time"
)

// 协程的协程是否会随着「父协程」的消亡而消亡？
func fatherRoutines() {
	fmt.Println("this is father go routines")
	go childRoutines()
}

func childRoutines() {
	time.Sleep(1*1e9)
	fmt.Println("this is child go routines")
}

func main() {
	go fatherRoutines()
	time.Sleep(2 * 1e9)
}