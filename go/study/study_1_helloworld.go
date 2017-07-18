package main

import (
	"fmt"
)

func main() {
	fmt.Println(hello())
}


func hello()(a string) {
    return "hello world"
}