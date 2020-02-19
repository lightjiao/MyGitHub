package main

import (
	"fmt"
	"strconv"
)



func multiReturn() (returnA int, returnB int) {
	return 1, 2
}

func sum(a int, b int) (sum int) {
	return a + b
}

func sum2(a int, b int) (sum int) {
	sum = a + b
	return
}

func sum3(a int, b int, outInt *int) {
	*outInt = a + b
}

func printList(str ...string)  {
	printList2(str...)

	fmt.Print(str)
	fmt.Print("\n")
	i:=0
	for i<len(str)  {
		fmt.Print(str[i] + " ")
		i++
	}
	fmt.Print("\n")
}

func printList2(str ...string)  {
	fmt.Print(str)
}

func main() {
	a, b := multiReturn()
	fmt.Print(a, b, "\n")

	fmt.Printf(strconv.Itoa(sum(1, 2))+"\n")
	fmt.Printf(strconv.Itoa(sum2(1, 2))+"\n")

	n := 100
	outInt := &n
	sum3(1, 2, outInt)
	fmt.Printf(strconv.Itoa(n)+"\n")

	printList("a", "funcB", "c")
}