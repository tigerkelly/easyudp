
/*
 * easyudp.c - An example of how to move data across a UDP/IP connection.
 *
 * Copyright (c) 2023 Richard Kelly Wiles (rkwiles@twc.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *  Created on: Aug 10, 2022
 *      Author: Kelly Wiles
 */
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
