all: barserver barclient

barserver: barserver.c utils.c
	cc -o barserver barserver.c utils.c

barclient: barclient.c utils.c
	cc -o barclient barclient.c utils.c

clean:
	rm barclient barserver
