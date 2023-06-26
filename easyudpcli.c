
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "easyudp.h"

SDI *sdi = NULL;

void clientCallback(SDI *sdi);

int main(int argc, char *argv[]) {

	char recvBuf[1204];

	// The 1 argument is an Ip address is to bind to or use NULL for all interfaces.
	// The 2 argument is the IP address to the server, this is were easyUdoSend sends packets to.
	// The 3 argumnet is the port number to listen on and send to.
	// The 4 argument is the starting seqence number, normally 1 or greater.
	// The 5 argument is the callback function, to be called each time a packet arrives.

	EasyData ed;
	memset(&ed, 0, sizeof(EasyData));

	ed.listenPort = 8383;
	ed.seqNumStart = 2;
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
		} else if (strcmp(argv[i], "-c") == 0) {
			ed.sendCount = atoi(argv[i+1]);
		}
	}

	if (ed.servIp[0] == '\0') {
		printf("No server address given. -s 192.168.0.24\n");
		exit(1);
	}


	sdi = easyUdp(&ed, clientCallback);

	easyUdpSend(sdi, "From easyudpcli 1", 0 );
	easyUdpSend(sdi, "From easyudpcli 2", 0 );
	easyUdpSend(sdi, "From easyudpcli 3", 0 );
	easyUdpSend(sdi, "From easyudpcli 4", 0 );
	easyUdpSend(sdi, "From easyudpcli 5", 0 );
	easyUdpSend(sdi, "From easyudpcli 6", 0 );
	easyUdpSend(sdi, "From easyudpcli 7", 0 );
	easyUdpSend(sdi, "From easyudpcli 8", 0 );
	easyUdpSend(sdi, "From easyudpcli 9", 0 );
	easyUdpSend(sdi, "From easyudpcli 10", 0 );
	easyUdpSend(sdi, "From easyudpcli 11", 0 );
	easyUdpSend(sdi, "From easyudpcli 12", 0 );
	easyUdpSend(sdi, "From easyudpcli 13", 0 );
	easyUdpSend(sdi, "From easyudpcli 14", 0 );
	easyUdpSend(sdi, "From easyudpcli 15", 0 );
	easyUdpSend(sdi, "From easyudpcli 16", 0 );

	// Without this loop responses are not seen, if the server sends responses.
	// Replace this loop with another loop in your program.
	while(1) {
		sleep(2);
	}

	easyUdpFree(sdi);

	return 0;
}

void clientCallback(SDI * sdi) {

     int sn = ntohl(sdi->udpData.seqNum);
     int ds = ntohl(sdi->udpData.dataSize);

    sdi->udpData.dataBuffer[ds] = '\0';
    printf("client: '%s', (sn=%d) (len=%d) %s:%d\n", sdi->udpData.dataBuffer, sn, ds, inet_ntoa(sdi->from.sin_addr), ntohs(sdi->from.sin_port));
}
