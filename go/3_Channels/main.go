package main

import (
	"fmt"
	"sync"
)

func main() {
	wg := &sync.WaitGroup{}
	channel := make(chan int)
	wg.Add(1)
	go func(wg *sync.WaitGroup, ch <-chan int) {
		for value := range ch {
			fmt.Printf("Received Value: %v\n", value)
		}
		wg.Done()
	}(wg, channel)
	channel <- 12
	channel <- 24
	close(channel)
	wg.Wait()
}
