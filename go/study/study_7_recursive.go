package main

import (
	"fmt"
)

func fab(number int) (int) {
	if number <= 1{
		return number
	} else {
		return fab(number - 1) + fab(number - 2)
	}
}


func f() (ret int) {
	defer func() {
		ret++
	}()
	return 1
}


func main() {
	//for i:=0;i<10 ;i++  {
	//	fmt.Print(strconv.Itoa(fab(i)) + "\n")
	//}

	helloWorld := func() {fmt.Print("Hello world")}
	helloWorld()
	fmt.Printf(" hello world is of type %T and has value %v\n", helloWorld, helloWorld)

	fmt.Println(f())
}


