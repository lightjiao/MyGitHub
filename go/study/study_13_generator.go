package main

//func generateRandomNumbers (n int) {
//	ch := make (chan float32)
//	sem := make (semaphore, n)
//
//	for i := 0; i < n; i++ {
//		go func () {
//			ch <- rand.Float()
//			close(ch)
//		} ()
//	}
//
//	// launch extra goroutine to eventually close ch
//	go func () {
//		sem.Wait(n)
//		close(ch)
//	}
//
//	return ch
//}