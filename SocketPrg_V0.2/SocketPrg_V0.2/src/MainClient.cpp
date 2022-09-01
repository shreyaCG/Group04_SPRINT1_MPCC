#include <ClientSocket.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	int csockfd, flags=0;
	char buff[MAX_BUF];
	promise<int> dataready{};
    promise<void> consumed{};
	ClientSocket *S = new ClientSocket(atoi(argv[2]), argv[1]);

	S->cliConn();
	csockfd = -1;
	csockfd = S->getCliSockfd();
	
	//readData1(csockfd,buff);
	
	/*while(1){
	
	memset(buff, 0, MAX_BUF);

	writeData1(csockfd,buff);
	if(strcmp(buff, "bye")==0)
		break;
	else{
			memset(buff,0,MAX_BUF);
      		read(csockfd,buff,MAX_BUF);
      		cout<<buff<<endl;
      		memset(buff,0,MAX_BUF);
      		
		}
	}
	*/

	 // beginning threads to asynchronously send and receive data from the server
   thread worker_r(recv_data, csockfd, flags); // this thread is responsible to constantly checking if server 
                                    // has sent some data or not and then print data in the console.

   thread worker_s(send_data, csockfd, flags); // this thread is responsible for taking input from the terminal
                                    // at any point of time and sending it to the server

   // stop the threads
   worker_r.join();
   worker_s.join();


	S->cliClose(S->getCliSockfd());
	return 0;
}