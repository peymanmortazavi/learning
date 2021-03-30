package main

import (
	"fmt"

	"github.com/peymanmortazavi/learning/types/models"
)

func main() {
    arr := [3]int{1, 2, 3}  // an array of 3
    slice1 := arr[:]  // slice of an array
    slice2 := []int{}  // an empty slice, note the unspecified length

    fmt.Println(arr, slice1, slice2)

    table := map[string]int {
        "key1": 1,
        "key2": 2,
    }
    delete(table, "key1")
    table["key2"] += 1
    fmt.Println(table)
    fmt.Println(table["key3"])  // initialized to 0

    u := models.User {
        ID: 1,
        Name: "Peyman",
    }
    fmt.Println(u)
}
