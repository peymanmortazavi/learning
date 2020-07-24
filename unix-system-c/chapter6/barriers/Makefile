utils := utils.c
vector := vector.c
barserver := barserver.c $(utils)
barclient := barclient.c $(utils)
multibarserver := multibarserver.c $(utils) $(vector)
multibarclient := multibarclient.c $(utils) $(vector)

all: barserver barclient multibarserver multibarclient

barserver: $(barserver)
	cc -o barserver $(barserver)

barclient: $(barclient)
	cc -o barclient $(barclient)

multibarserver: $(multibarserver)
	cc -o multibarserver $(multibarserver)

multibarclient: $(multibarclient)
	cc -o multibarclient $(multibarclient)

clean:
	rm barclient barserver multibarserver multibarclient
