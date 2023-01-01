
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "easyudp.h"

#define MAX_SEQ_NUMS        10

int idx = 0;
int lastSeqNums[MAX_SEQ_NUMS];
SDI *sdi = NULL;

void clientCallback(SDI *sdi);

int main(int argc, char *argv[]) {

	char recvBuf[1204];

	// The 1 argument is an Ip address is to bind to or use NULL for all interfaces.
	// The 2 argument is the IP address to the server, this is were easyUdoSend sends packets to.
	// The 3 argumnet is the port number to listen on and send to.
	// The 4 argument is the starting seqence number, normally 1 or greater.
	// The 5 argument is the callback function, to be called each time a packet arrives.

	sdi = easyUdp("192.168.0.15", "192.168.0.121", 8383, 2, clientCallback);

	sdi->sendCount = 2;		// Set send number count, how many times the packet is sent.

	easyUdpSend(sdi, "From easyudpcli 1", 17 );
	easyUdpSend(sdi, "From easyudpcli 2", 17 );
	easyUdpSend(sdi, "From easyudpcli 3", 17 );
	easyUdpSend(sdi, "From easyudpcli 4", 17 );
	easyUdpSend(sdi, "From easyudpcli 5", 17 );
	easyUdpSend(sdi, "From easyudpcli 6", 17 );
	easyUdpSend(sdi, "From easyudpcli 7", 17 );
	easyUdpSend(sdi, "From easyudpcli 8", 17 );
	easyUdpSend(sdi, "From easyudpcli 9", 17 );
	easyUdpSend(sdi, "From easyudpcli 10", 17 );
	easyUdpSend(sdi, "From easyudpcli 11", 17 );
	easyUdpSend(sdi, "From easyudpcli 12", 17 );
	easyUdpSend(sdi, "From easyudpcli 13", 17 );
	easyUdpSend(sdi, "From easyudpcli 14", 17 );
	easyUdpSend(sdi, "From easyudpcli 15", 17 );
	easyUdpSend(sdi, "From easyudpcli 16", 17 );

	easyUdpFree(sdi);

	return 0;
}

void clientCallback(SDI * sdi) {
	 bool seenFlag = false;

     int sn = ntohl(sdi->udpData.seqNum);
     int ds = ntohl(sdi->udpData.dataSize);

    // Check if we have seen this seqNum before.
    for (int i = 0; i < MAX_SEQ_NUMS; i++) {
        if (lastSeqNums[i] == sn) {
            // we have seen this seqnum before.
            seenFlag = true;
        }
    }

    if (seenFlag == true)
        return;

    if (idx >= MAX_SEQ_NUMS)
        idx = 0;

    lastSeqNums[idx++] = sn;

    sdi->udpData.dataBuffer[ds] = '\0';
    printf("client: %s, %d\n", sdi->udpData.dataBuffer, ds);
}
