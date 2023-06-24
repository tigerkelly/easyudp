ARC=libeasyudp.a

all: $(ARC) easyudpserv easyudpcli

$(ARC): easyudp.o
	$(AR) -r $(ARC) easyudp.o

easyudp.o: easyudp.c easyudp.h
	cc -c easyudp.c -o easyudp.o

easyudpserv.o: easyudpserv.c easyudp.h
	cc -g -c easyudpserv.c -o easyudpserv.o

easyudpcli.o: easyudpcli.c easyudp.h
	cc -g -c easyudpcli.c -o easyudpcli.o

easyudpserv: easyudpserv.o easyudp.o
	cc easyudpserv.o -o easyudpserv -L./ -leasyudp -lpthread

easyudpcli: easyudpcli.o easyudp.o
	cc easyudpcli.o -o easyudpcli -L./ -leasyudp -lpthread

clean:
	rm -rf *.o easyudpserv easyudpcli libeasyudp.a
