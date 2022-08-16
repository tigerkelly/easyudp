
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "easyudp.h"

int main(int argc, char *argv[]) {

	char recvBuf[1204];

	USI *usi = easyUdpClient("192.168.0.121", 8383, 2, 2);

	easyUdpSend(usi, "From easyudpcli 1", 17 );
	easyUdpSend(usi, "From easyudpcli 2", 17 );
	easyUdpSend(usi, "From easyudpcli 3", 17 );
	easyUdpSend(usi, "From easyudpcli 4", 17 );
	easyUdpSend(usi, "From easyudpcli 5", 17 );
	easyUdpSend(usi, "From easyudpcli 6", 17 );
	easyUdpSend(usi, "From easyudpcli 7", 17 );
	easyUdpSend(usi, "From easyudpcli 8", 17 );
	easyUdpSend(usi, "From easyudpcli 9", 17 );
	easyUdpSend(usi, "From easyudpcli 10", 17 );
	easyUdpSend(usi, "From easyudpcli 11", 17 );
	easyUdpSend(usi, "From easyudpcli 12", 17 );
	easyUdpSend(usi, "From easyudpcli 13", 17 );
	easyUdpSend(usi, "From easyudpcli 14", 17 );
	easyUdpSend(usi, "From easyudpcli 15", 17 );
	easyUdpSend(usi, "From easyudpcli 16", 17 );

	easyUdpClientFree(usi);

	return 0;
}
