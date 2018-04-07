package main

import "fmt"

func main_1() {
	var arr [6]int

	var slice1 []int = arr[2:5]

	for i := 0; i < len(arr); i++ {
		arr[i] = i
	}
	fmt.Print(arr, "\n")
	fmt.Print(slice1, "\n")

	fmt.Printf("len of slice is %d\n", len(slice1))
	fmt.Printf("capacity of slice is %d\n", cap(slice1))

	slice1 = arr[:]

	fmt.Printf("len of slice is %d\n", len(slice1))
	fmt.Printf("capacity of slice is %d\n", cap(slice1))

	slice1 = arr[4:5]

	fmt.Printf("len of slice is %d\n", len(slice1))
	fmt.Printf("capacity of slice is %d\n", cap(slice1))
}

// slice是一个引用，所以如果函数入参是一个slice，那么在函数里修改了slice的数值，会影响到函数外的slice以及源数组
func changeSlice(slice []int) []int  {
	slice[1] = 9
	return slice
}

// 模仿filter函数实现
func Filter(slice []int, fn func(int) bool) []int  {

	newSlice := make([]int, 0)
	for _, value :=range slice {
		if false == fn(value) {
			continue
		}
		newSlice = append(newSlice, value)
	}

	return newSlice
}


func deleteByAppend() {
	// 声明一个数组 0-9
	var arr [10]int
	for i := range arr {
		arr[i] = i
	}
	// 切片指向数组
	slice := arr[:]
	fmt.Print(slice)
	fmt.Print("\n")

	// 切片操作将将 7 之后的数据append到2 后面
	// slice = append(slice[:2], slice[7:]...)
	// 源数组的2之后下标的数会被修改
	// fmt.Print(arr)

	// 在索引i的位置插入元素x
	// slice = append(slice[:5], append([]int{100}, slice[5:]...)...)

	// 在索引 i 的位置插入长度为 j 的新切片
	slice = append(slice[:5], append(make([]int, 3), slice[5:]...)...)
	fmt.Print(slice)
	fmt.Print("\n")

	// 取出位于切片 a 最末尾的元素
	x := slice[len(slice)-1]
	slice = slice[:len(slice)-1]

	fmt.Print(x)
}

//练习 7.12
//编写一个函数，要求其接受两个参数，原始字符串 str 和分割索引 i，然后返回两个分割后的字符串。
func mySplit(str string, i int) (a string, b string) {
	slice := str[:]
	a = slice[:i]
	b = slice[i:]

	return a, b
}

//练习 7.13
//假设有字符串 str，那么 str[len(str)/2:] + str[:len(str)/2] 的结果是什么？
func testSlice() {
	str := "01"
	fmt.Print(str[len(str)/2:] + str[:len(str)/2], "\n")

	str = "012"
	fmt.Print(str[len(str)/2:] + str[:len(str)/2], "\n")

	fmt.Print(2/2, 3/2 , 1/2)
}

//练习 7.15
//编写一个程序，要求能够遍历一个数组的字符，并将当前字符和前一个字符不相同的字符拷贝至另一个数组。
func copyArrayNotRepeat(slice []byte) []byte {
	var pre byte
	newSlice := make([]byte, len(slice)/2)
	for i, value := range slice {
		if i == 0{
			pre = value
			continue
		}
		if value != pre {
			newSlice = append(newSlice, value)
		}
		pre = value
	}
	return newSlice
}


//练习 7.17
//在函数式编程语言中，一个 map-function 是指能够接受一个函数原型和一个列表，并使用列表中的值依次执行函数原型，公式为：map ( F(), (e1,e2, . . . ,en) ) = ( F(e1), F(e2), ... F(en) )。
//编写一个函数 mapFunc 要求接受以下 2 个参数：
//
//一个将整数乘以 10 的函数
//一个整数列表
//最后返回保存运行结果的整数列表。
func myMapFunc(f func(int) int, slice []int) []int {
	newSlice := make([]int, 0, len(slice))

	for _, value := range slice {
		newSlice = append(newSlice, f(value))
	}

	return newSlice
}

func main() {
	slice := make([]int, 10)
	for i:=range slice {
		slice[i] = i
	}

	fmt.Print(slice)
	result := myMapFunc(func(n int) int {return n * 10}, slice)
	fmt.Print(result)
}