utils := utils.c

all: server client

server: fifo_server.c $(utils)
	cc -o fifo_server fifo_server.c $(utils)

client: fifo_client.c $(utils)
	cc -o fifo_client fifo_client.c $(utils)
