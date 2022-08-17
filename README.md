# easyudp
An easy to use UDP client and server library.

Use this library to send data to a server over UDP.  If you want bidirectional UDP between
client and server just use this same library in the other direction.  Both client and server
would have both a server and client socket.


This contains some code to help with reliablity of UDP but does not handle it all.

The test programs are easyudpserv.c and easyudpcli.c.

The functions are as follows.

The easyUdpServer function is the only call needed to setup a UDP server.

The easyUdpClient and easyUdpSend are used by the client to create a UDP socket and send data
to the server.

Read the source code for more information.

If you have any questions just ask.
