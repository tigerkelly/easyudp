
all: easyudpserv easyudpcli

easyudp.o: easyudp.c easyudp.h
	cc -c easyudp.c -o easyudp.o

easyudpserv.o: easyudpserv.c easyudp.h
	cc -c easyudpserv.c -o easyudpserv.o

easyudpcli.o: easyudpcli.c easyudp.h
	cc -c easyudpcli.c -o easyudpcli.o

easyudpserv: easyudpserv.o easyudp.o
	cc easyudpserv.o easyudp.o -o easyudpserv -lpthread

easyudpcli: easyudpcli.o easyudp.o
	cc easyudpcli.o easyudp.o -o easyudpcli -lpthread

clean:
	rm -rf *.o easyudpserv easyudpcli
