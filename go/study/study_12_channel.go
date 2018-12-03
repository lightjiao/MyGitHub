package main

import (
	"fmt"
	"io/ioutil"
	"time"
)

func sendData(ch chan string) {
	ch <- "hello"
	ch <- "world"
	ch <- ","
	ch <- "hello"
	ch <- "light"
	ch <- "."
}

func getData(ch chan string) {
	for {
		input := <-ch
		fmt.Printf("%s", input)
	}
}

func logInfo(message string) {
	//fmt.Printf("%s", message)

	// write the whole body at once
	err := ioutil.WriteFile("output.txt", []byte(message), 0644)
	if err != nil {
		panic(err)
	}
}

func pump(ch chan int) {
	for i := 0; ; i++ {
		ch <- i
	}
}

func suck(ch chan int) {
	for {
		fmt.Println(<-ch)
	}
}

func sumBigArray(bigArray []int, ch chan int) {
	time.Sleep(2 * 1e9)

	var sum int
	for _, value := range bigArray {
		sum += value
	}

	ch <- sum
}

func main() {
	// 最简单的channel通讯数据, 默认情况下channel是阻塞的无缓冲的
	//ch := make(chan string)
	// //ch := make(chan string, 10)
	//go sendData(ch)
	//go getData(ch)
	//time.Sleep(1e9)

	// 协程打印日志
	// 心得：主进程结束后协程会立刻终止，意味着需要有通讯机制保证协程都执行完成之后主进程再退出
	//go logInfo("hello log info")
	//// 这个sleep 假装是一个通讯机制使得协程能够执行完
	//time.Sleep(1e9)

	// 这个证明了, 通道的输入是阻塞的, 有接受者才会传输数据，没有接受者，则不会传输数据
	//ch1 := make(chan int, 10)
	//go pump(ch1)       // pump hangs
	//fmt.Println(<-ch1) // prints only 0

	// 这个证明了，通道没有阻塞的时候（接受和传输都无限循环），一秒钟的运行结果
	//ch1 := make(chan int)
	//go suck(ch1)
	//go pump(ch1)
	//time.Sleep(1e9)

	// 写一个通道证明它的阻塞性，开启一个协程接收通道的数据，持续 15 秒，然后给通道放入一个值。在不同的阶段打印消息并观察输出
	//c := make(chan int)
	//// 如果加入通道的缓冲, 那么使得阻塞效果就没有了，通道不会阻塞到一直等待协程接收到数据
	//// c := make(chan int, 10)
	//go func() {
	//	time.Sleep(15 * 1e9)
	//	x := <-c
	//	fmt.Println("received", x)
	//}()
	//fmt.Println("sending", 10)
	//c <- 10
	//fmt.Println("sent", 10)

	// 利用协程的阻塞，使得main函数等待协程执行完成
	//ch := make(chan int)
	//go sumBigArray([]int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, ch)
	//// ... do something else for a while
	//sum := <- ch
	//fmt.Println(sum)

	// 通道的方向的应用：
	// 利用通道的方向实现选择器算法 (sieve prime-algorithm) 的输出素数
	//sievePrimeAlgorithm()
	// V2实现使得main函数更简洁
	sievePrimeAlgorithmV2()
}

func sievePrimeAlgorithmV2() {
	primes := sieveV2()
	for {
		fmt.Print(<-primes, " ")
	}
}

func generateV2() chan int {
	ch := make(chan int)
	go func() {
		for i := 2; ; i++ {
			ch <- i
		}
	}()
	return ch
}

func filterV2(chIn chan int, perime int) chan int {
	chOut := make(chan int)
	go func() {
		for {
			if i := <-chIn; i%perime != 0 {
				chOut <- i
			}
		}
	}()
	return chOut
}

func sieveV2() chan int {
	out := make(chan int)
	go func() {
		ch := generateV2()
		for {
			perime := <-ch
			ch = filterV2(ch, perime)
			out <- perime
		}
	}()

	return out
}

// 通道的方向的应用：
// 利用通道的方向实现选择器算法 (sieve prime-algorithm) 的输出素数
func sievePrimeAlgorithm() {
	ch := make(chan int)
	go numGenerate(ch) // 利用协程生成数字

	for {
		prime := <-ch
		fmt.Print(prime, " ")

		ch2 := make(chan int)
		go primeFilter(ch, ch2, prime)
		ch = ch2
	}
}

// 生产数字
func numGenerate(ch chan int) {
	for i := 2; ; i++ {
		ch <- i
	}
}

// 素数选择器
func primeFilter(in chan int, out chan int, prime int) {
	for {
		i := <-in

		// 拷贝通道输出的数字到另一个输入的通道，丢弃掉可以被素数整除的数字
		if i%prime != 0 {
			out <- i
		}
	}
}
