package main

import (
	"fmt"
	"./package/package1"
)

func main()  {
	str := package1.ReturnString()
	fmt.Print(str, "\n")
	fmt.Print(package1.PackageInt, "\n")
	fmt.Print(package1.PackageFloat, "\n")
}