#include <SockClient.h>
#include <unistd.h>
#include<details.h>
//take port number and ip from command line
int main(int argc, char *argv[])
{
	int newfd, flags=0;
	char buff[MAX_BUF];
	//allocate dynamic memory
	Client *C = new Client(atoi(argv[2]), argv[1]);
        details *d= new details;

	C->create_socket();
	C->clientconnect();
	//get client socket
	newfd = C->getCliSockfd();
	d->setdetails();
	//d->setpass();
	send(newfd,d,sizeof(details),0);	
	cout<<"obj sent"<<endl;

	//Create threads to send and recieve message
	thread recvmsg(recv_data, newfd, flags); 	
	thread sendmsg(send_data, newfd, flags); 
	
	// stop the threads
	recvmsg.join();
	sendmsg.join();

	//close client socket
	C->Closesoc(C->getCliSockfd());

	return 0;
}
