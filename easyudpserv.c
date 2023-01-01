
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

#define MAX_SEQ_NUMS	10

int idx = 0;
int lastSeqNums[MAX_SEQ_NUMS];

void callback(SDI *sdi);

int main(int argc, char *argv[]) {

	SDI *sdi = NULL;

	memset(lastSeqNums, 0, sizeof(lastSeqNums));

	// The client and server program must be on different systems or interfaces.
	// If you have a two nic card system then you can run both client and server on
	// same system.

	sdi = easyUdp("192.168.0.121", "192.168.0.15", 8383, 1, &callback);
	if( sdi == NULL) {
		printf("Can not create server socket.\n");
		exit(1);
	}

	sdi->sendCount = 2;		// Set send number count, how many times the packet is sent.

	while(true) {
		sleep(2);
	}

	easyUdpFree(sdi);

	return 0;
}

void callback(SDI *sdi) {
	bool seenFlag = false;

	// Check if we have seen this seqNum before.
	for (int i = 0; i < MAX_SEQ_NUMS; i++) {
		if (lastSeqNums[i] == sdi->udpData.seqNum) {
			// we have seen this seqnum before.
			seenFlag = true;
		}
	}
	if (seenFlag == true)
		return;

	if (idx >= MAX_SEQ_NUMS)
		idx = 0;

	lastSeqNums[idx++] = sdi->udpData.seqNum;
	
	sdi->udpData.dataBuffer[sdi->udpData.dataSize] = '\0';

	printf("Got buffer %s size %d, seqNum %d from %s\n",
			sdi->udpData.dataBuffer, sdi->udpData.dataSize, sdi->udpData.seqNum, inet_ntoa(sdi->from.sin_addr));

	// Do something with the data.
}
