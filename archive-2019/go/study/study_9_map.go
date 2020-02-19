package main

import "fmt"

func simpleUse() {
	// 声明map类型的变量
	var mapList map[string]int
	var mapAssigned map[string]int

	// 初始化map类型的变量
	mapList = map[string]int{"one": 1, "two":2}
	fmt.Print("map list is: ", mapList, "\n")

	// map的这种赋值方式是一种引用, 修改mapAssigned的值会影响mapList中的值
	mapAssigned = mapList
	mapAssigned["three"] = 3
	fmt.Print("map assigned is: ", mapAssigned, "\n")
	fmt.Print("map list after assigned is: ", mapList, "\n")

	// 也可以用make声明map
	mapCreated := make(map[string]float32)
	// mapCreated2 := map[string]float32 is wrong, mapCreated2 := map[string]float32{} is right
	mapCreated2 := map[string]float32{"one": 1, "two":2}
	mapCreated["key"] = 4.5
	mapCreated2["key2"] = 99.9
	fmt.Print(mapCreated, "\n")
	fmt.Print(mapCreated2, "\n")

	// func 作为value的map
	funcMap := map[string]func()int{
		"one": func() int {
			return 1
		},
		"two": func() int {
			return 2
		},
	}
	fmt.Print(funcMap, "\n")
	fmt.Print(funcMap["one"], "\n")
	fmt.Print(funcMap["one"](), "\n")
	fmt.Print(funcMap["aaa"], "\n")
	//fmt.Print(funcMap["aaa"](), "\n") // invalid memory address or nil pointer dereference

	// 切片作为map的value
	//map1 := make(map[string][]int)
	//map2 := make(map[string]*[]int)
}

func simpleUse2() {
	// key是否存在在map中, 第二个值返回true则是存在的key, 第二个值返回false 则是不存在的key
	mp := make(map[string]string)
	value, isExist := mp["aaa"]
	fmt.Print(value, "\n", isExist)

	// 删除map中指定的key
	delete(mp, "aaa")
}

//练习 8.1
//创建一个 map 来保存每周 7 天的名字，将它们打印出来并且测试是否存在 Tuesday 和 Hollyday。
func weekMap()  {
	weekMap := map[int]string{
		1: "Monday",
		2: "Tuesday",
		3: "Wednesday",
		4: "Thursday",
		5: "Friday",
		6: "Saturday",
		7: "Sunday",
	}

	isHolidayExists := false
	for _, value := range weekMap{
		fmt.Print(value, "\n")
		if value == "Holiday" {
			isHolidayExists = true
		}
	}
	fmt.Print("holiday is exists: ", isHolidayExists, "\n")
}

// map是无序的, 需要一个排序的map, 需要先将map的key全取出来成一个slice(数组), 排序后遍历这个数组即可
// 也可以使用结构体列表(包含一个key值和一个value值的结构体)来达成相同的效果

func main()  {
	weekMap()
}