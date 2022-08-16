
#ifndef _EASYUPD_H_
#define _EASYUDP_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_DATA_SIZE	2048

typedef struct _udpData_ {
	int dataSize;
	int seqNum;
	char dataBuffer[MAX_DATA_SIZE];
} UdpData;

typedef struct _servDataInfo {
	int sock;
	int port;
	int maxSize;
	int seqNumStart;
	void (*callback) (struct _servDataInfo *sdi);
	char ipAddr[16];
	struct sockaddr_in from;
	UdpData udpData;
} SDI;

typedef struct _udpSendInfo {
	int sock;
	int port;
	int sendCount;
	int maxSize;
	int seqNumStart;
	char ipAddr[16];
	UdpData udpData;
} USI;

SDI *easyUdpServer(char *ipAddr, int port, int seqNumStart, void (*callback)(SDI *sdi));
void stopEasyUdpServer(SDI *sdi);

USI *easyUdpClient(char *ipAddr, int port, int seqNumStart, int sendCount);
int easyUdpSend(USI *usi, char *dataBuffer, int dataSize);

void easyUdpServerFree(SDI *sdi);
void easyUdpClientFree(USI *usi);

#endif
