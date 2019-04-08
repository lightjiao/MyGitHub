package main

import "fmt"

// 编写一个程序，开启 3 个线程 A,B,C，这三个线程的输出分别为 A、B、C，每个线程将自己的
// 输出在屏幕上打印 10 遍，要求输出的结果必须按顺序显示。如：ABCABCABC....

// 还可以使用多个 channel 执行扇入(Fan In)操作，避免使用锁。
//首先说一下扇入的定义，Go blog 中是这样描述的：
//A function can read from multiple inputs and proceed until all are closed by multiplexing the input channels onto a single channel that's closed when all the inputs are closed. This is called fan-in.
//通过将多个输入 channel 多路复用到单个处理 channel 的方式，一个函数能够从多个输入 channel 中读取数据并处理。当所有的输出 channel 都关闭的时候，单个处理 channel 也会关闭。这就叫做扇入。
/*
	如图，多个输入，一个输出，即为扇入
	--> |\
	--> | |-->
	--> |/
*/

func gen(b byte, times int) <-chan byte {
	ch := make(chan byte)
	go func() {
		defer close(ch)
		for i := 0; i < times; i++ {
			ch <- b
		}
	}()
	return ch
}

func fanIn(times int, chans []<-chan byte) <-chan byte {
	ch := make(chan byte)
	go func() {
		defer close(ch)
		for i := 0; i < times; i++ {
			for _, input := range chans {
				ch <- <-input
			}
		}
	}()
	return ch
}

func main() {
	times := 10
	inputs := make([]<-chan byte, 0, 3)
	for _, v := range []byte{'A', 'B', 'C'} {
		inputs = append(inputs, gen(v, times))
	}

	for v := range fanIn(times, inputs) {
		fmt.Printf("%c", v)
	}
}
