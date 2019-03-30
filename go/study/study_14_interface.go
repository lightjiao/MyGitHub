package main

import (
	"fmt"
)

// 声明接口类型、继承接口并实现多态
type Shaper interface {
	Area() float32
}

type Square struct{ side float32 }

func (s *Square) Area() float32 {
	return s.side * s.side
}

type Rectangle struct {length, width float32}

func (s Rectangle)Area() float32 {
	return s.length * s.width
}

func testDuoTai(){
	s := Square{1}
	r := Rectangle{1, 2}

	shaperList := []Shaper{&s, r}
	for _, shaper := range shaperList {
		//fmt.Printf("area is : %f", shaper.Area())

		switch t := shaper.(type) {
		case *Square:
			fmt.Printf("*Square area is : %f\n", t.Area())
		case *Rectangle:
			fmt.Printf("*Rectangle area is : %f\n", t.Area())
		case Rectangle:
			fmt.Printf("Rectangle area is : %f\n", t.Area())
		case nil:
			fmt.Printf("nil value: nothing to check?\n")
		}
	}
}

func main() {
	testDuoTai()
}

type hi interface {
	SayHi()
}
type hello interface {
	SayHello()
}
type world interface {
	hi
	hello
}

func assertInterface() {

}