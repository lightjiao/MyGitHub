
// 这是我的实验性的包
package package1

// int变量
var PackageInt = 42

// float变量
var PackageFloat = 3.14

// 可以被外部调用的函数
func ReturnString() string  {
	return "hello world"
}

// 果然小写的函数在引用的时候看不见啊
func lowerCaseFunc() string {
	return "Hello lowercase"
}