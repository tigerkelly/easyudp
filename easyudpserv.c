
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "easyudp.h"

SDI *sdi = NULL;

void callback(SDI *sdi);

int main(int argc, char *argv[]) {

	EasyData ed;
	memset(&ed, 0, sizeof(EasyData));
	ed.listenPort = 8383;
	ed.seqNumStart = 1;
	ed.sendCount = 2;
	ed.maxLookBack = 16;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			strcpy(ed.ifAddr, argv[i+1]);
		} else if (strcmp(argv[i], "-s") == 0) {
			strcpy(ed.servIp, argv[i+1]);
		} else if (strcmp(argv[i], "-p") == 0) {
			ed.listenPort = atoi(argv[i+1]);
		} else if (strcmp(argv[i], "-n") == 0) {
			ed.seqNumStart = atoi(argv[i+1]);
		}
	}

	if (ed.servIp[0] == '\0') {
		printf("No server address given. -s 192.168.0.24\n");
		exit(1);
	}

	// The client and server program must be on different systems or interfaces.
	// If you have a two nic card system then you can run both client and server on
	// same system.

	sdi = easyUdp(&ed, &callback);
	if( sdi == NULL) {
		printf("Can not create server socket.\n");
		exit(1);
	}

	// Replace this loop with another loop in your program.
	while(true) {
		sleep(2);
	}

	easyUdpFree(sdi);

	return 0;
}

void callback(SDI *sdi) {
	int sn = 0;
    int ds = 0;

    sn = ntohl(sdi->udpData.seqNum);
    ds = ntohl(sdi->udpData.dataSize);

	*(sdi->udpData.dataBuffer + ds) = '\0';

	printf("Got buffer '%s' size %d, seqNum %d from %s:%d\n",
			sdi->udpData.dataBuffer, ds, sn, inet_ntoa(sdi->from.sin_addr), sdi->from.sin_port);

	char rsp[64];

	sprintf(rsp, "Serv responce seq=%d", sn);

	easyUdpRespond(sdi, rsp, 0);

	// Do something with the data.
}
