package main

import (
	"fmt"
	"strings"
)

// Expand replaces all $<var> names with the result of f("<var")
func expand(s string, f func(string) string) string {
	// Simlest form, not sure if fastest.
	// r, _ := regexp.Compile(`[$][\w_-]+`)
	// return r.ReplaceAllStringFunc(s, f)

	builder := strings.Builder{}
	builder.Grow(len(s))
	for len(s) > 0 {
		start := strings.Index(s, "$")
		if start == -1 {
			builder.WriteString(s)
			break
		}
		if start > 0 {
			builder.WriteString(s[:start])
		}
		end := strings.IndexAny(s[start+1:], " ,.!@#$%^&*()+\n\t")
		if end == -1 {
			builder.WriteString(f(s[start+1:]))
			break
		} else {
			builder.WriteString(f(s[start+1 : start+1+end]))
		}
		if start+end < len(s) {
			s = s[start+end+1:]
		}
	}
	return builder.String()
}

func replace(input string) string {
	return fmt.Sprintf("<Replace: %s>", input)
}

func main() {
	fmt.Println(expand("Hello $user, your phone number is $phone_number", replace))
}
