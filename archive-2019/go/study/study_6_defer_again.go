package main

import "fmt"

func trace(s string) string {
	fmt.Println("entering: ", s)
	return s
}

func unTrace(s string) {
	fmt.Println("leaving: ", s)
}

func a() {
	defer unTrace(trace("a"))
	fmt.Println("this is a")
}

func b()  {
	defer unTrace(trace("b"))
	fmt.Println("this is b")
	a()
}

//func main() {
//	b()
//
//	// enter b
//	// this is b
//	// enter a
//	// this is a
//	// leave a
//	// leave b
//}

func otherCall(s string) {
	defer otherCall(s)
	fmt.Println("this is other_call_1")
}

func otherCall2(s string){
	defer otherCall(s)
	fmt.Println("this is otherCall2")
}

// this will make stack over flow
func main() {
	otherCall("aa")
}