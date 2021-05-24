package main

import "fmt"

func test(values []int, number int) {
	fmt.Printf("Call Number %5d\n", number)
	fmt.Printf("\ta Cap: %d, Values: %v\n\n", cap(values), values)
	if len(values) > 0 {
		values[0] *= 10
	}
	values = append(values, number)
	fmt.Printf("\tb Cap: %d, Values: %v\n\n", cap(values), values)
	if number > 0 {
		test(values, number-1)
	}
	fmt.Printf("\tc Cap: %d, Values: %v\n\n", cap(values), values)
	fmt.Printf("Done Number %5d\n\n", number)
}

func test_returning(values []int, number int) []int {
	fmt.Printf("Call Number %5d\n", number)
	fmt.Printf("\ta Cap: %d, Values: %v\n\n", cap(values), values)
	if len(values) > 0 {
		values[0] *= 10
	}
	values = append(values, number)
	fmt.Printf("\tb Cap: %d, Values: %v\n\n", cap(values), values)
	if number > 0 {
		values = test_returning(values, number-1)
	}
	fmt.Printf("\tc Cap: %d, Values: %v\n\n", cap(values), values)
	fmt.Printf("Done Number %5d\n\n", number)
	return values
}

func main() {
	test(nil, 2)
	test_returning(nil, 2)
}
