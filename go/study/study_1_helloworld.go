package main

import "fmt"

func main() {
	fmt.Println(hello())
	funcIf(1, 2)
}

func hello() (a string) {
	return "hello world"
}

func funcIf(first int, cond int) {
	if first <= 0 {
		fmt.Printf("first is less than or equal to 0\n")
	} else if first > 0 && first < 5 {
		fmt.Printf("> 0 < 5\n")
	} else if cond == 0 {
		fmt.Printf("cond")
	}

	return
}
