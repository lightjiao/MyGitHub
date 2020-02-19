package main

import (
	"fmt"
	"strconv"
)

func main() {

	fmt.Printf("The size of ints is: %d\n", strconv.IntSize)

	var orig string = "234"
	an, err := strconv.Atoi(orig)
	if err != nil {
		fmt.Printf("Orig %s is not an integer string, exit with errot", orig)
		return
	}

	fmt.Printf("The integer is %s\n", an)
	an += 5
	newS := strconv.Itoa(an)
	fmt.Printf("The new string is : %s\n", newS)
}