
#ifndef _EASYUPD_H_
#define _EASYUDP_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define DEFAULT_LOOKBACK_NUM	16
#define DEFAULT_MAX_SIZE		2048
#define DEFAULT_START_SEQNUM	2
#define DEFAULT_SENDCOUNT		2
#define MAX_SENDCOUNT			8

typedef struct _udpData_ {
	int dataSize;
	int seqNum;
	char dataBuffer[DEFAULT_MAX_SIZE];
} UdpData;

typedef struct _easysetup {
	int listenPort;
	int sendCount;
	int seqNumStart;
	int maxLookBack;
	char servIp[16];
	char ifAddr[16];
} EasyData;

typedef struct _servDataInfo {
	int sock;
	int listenPort;
	int sendCount;
	int maxSize;
	int seqNumStart;
	int maxLookBack;
	void (*callback) (struct _servDataInfo *sdi);
	char servIp[16];
	char ifAddr[16];
	struct sockaddr_in from;
	UdpData udpData;
} SDI;

// SDI *easyUdp(char *bindIp, char *servIp, int port, int seqNumStart, void (*callback)(SDI *sdi));
SDI *easyUdp(EasyData *ed, void (*callback)(SDI *sdi));

int easyUdpSend(SDI *sdi, char *dataBuffer, int dataSize);
int easyUdpRespond(SDI *sdi, char *dataBuffer, int dataSize);

void easyUdpFree(SDI *sdi);

#endif
