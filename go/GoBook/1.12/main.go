package main

import (
	"flag"
	"fmt"
	"net/http"
	"os"
)

func main() {
	host := flag.String("host", "0.0.0.0", "Host name/IP address to listen on.")
	port := flag.Int("port", 5000, "Port to listen on.")
	address := fmt.Sprintf("%s:%d", *host, *port)

	http.HandleFunc("/", func(writer http.ResponseWriter, request *http.Request) {
		fmt.Fprintf(writer, "Query: %s\n", request.URL.RawQuery)
		if err := request.ParseForm(); err != nil {
			fmt.Fprintf(writer, "Error reading the form : %v\n", err)
			return
		}
		for key, value := range request.Form {
			fmt.Fprintf(writer, "%7s = %-10q\n", key, value)
		}
	})

	if err := http.ListenAndServe(address, nil); err != nil {
		fmt.Fprintf(os.Stderr, "Error starting server on %s : %v", address, err)
		os.Exit(1)
	}
}
