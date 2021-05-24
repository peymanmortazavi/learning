package main

import (
	"fmt"
)

/*
	Rewrite topoSort to use maps instead of slices and eliminate the initial sort.
	Verify that the results, though nondeterministic, are valid topological orderings.
*/

// prereqs maps computer science courses to their prerequisites.
var prereqs = map[string]map[string]bool{
	"algorithms": {"data structures": false},
	"calculus":   {"linear algebra": false},

	"compilers": {
		"data structures":       false,
		"formal languages":      false,
		"computer organization": false,
	},

	"data structures":       {"discrete math": false},
	"databases":             {"data structures": false},
	"discrete math":         {"intro to programming": false},
	"formal languages":      {"discrete math": false},
	"networks":              {"operating systems": false},
	"operating systems":     {"data structures": false, "computer organization": false},
	"programming languages": {"data structures": false, "computer organization": false},
}

func main() {
	for i, course := range topoSort(prereqs) {
		fmt.Printf("%d:\t%s\n", i+1, course)
	}
}

func topoSort(m map[string]map[string]bool) []string {
	var order []string
	seen := make(map[string]bool)
	var visitAll func(items map[string]bool)

	visitAll = func(items map[string]bool) {
		for key := range items {
			if !seen[key] {
				seen[key] = true
				visitAll(m[key])
				order = append(order, key)
			}
		}
	}

	keys := map[string]bool{}
	for key := range m {
		//keys = append(keys, key)
		keys[key] = false
	}

	//sort.Strings(keys)
	visitAll(keys)
	return order
}
