#include <ClientSocket.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	int csockfd, flags=0;
	char buff[MAX_BUF];
//	promise<int> dataready{};
//   	 promise<void> consumed{};
	ClientSocket *S = new ClientSocket(atoi(argv[2]), argv[1]);

	S->cliConn();
	csockfd = -1;
	csockfd = S->getCliSockfd();
	
	// this thread is responsible to constantly checking if server 
        // has sent some data or not and then print data in the console.
	thread worker_r(recv_data, csockfd, flags); 	
	// this thread is responsible for taking input from the terminal
	// at any point of time and sending it to the server
	thread worker_s(send_data, csockfd, flags); 
	
	// stop the threads
	worker_r.join();
	worker_s.join();
	S->cliClose(S->getCliSockfd());
	return 0;
}
