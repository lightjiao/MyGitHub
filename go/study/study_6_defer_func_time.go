package main

import "time"

func funcStart(s string) (string, int64) {
	startTime := time.Now().UnixNano()
	println("function start: ", s)
	return s, startTime
}

func funcEnd(s string, startTime int64) {
	endTime := time.Now().UnixNano()
	println("function end: ", s)
	println("function spend nano time: ", endTime, startTime)
	println("function spend nano time: ", (endTime - startTime)/1000000)

}

func testFunc() {
	defer funcEnd(funcStart("testFunc"))
	time.Sleep(1000 * 1000 * 54)
	println("this is a function")
}


func main() {
	time.Sleep(1000 * 1000000)
	testFunc()
}