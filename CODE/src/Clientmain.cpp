#include <SockClient.h>
#include <unistd.h>
#include<details.h>
//take port number and ip from command line
int main(int argc, char *argv[])
{

	try {
		if(argc<3){
                        throw("Insufficient arguments\nUsage: <IP Address> <Port Number>");
                }
                else {
			int newfd, flags=0,option;
			
			//allocate dynamic memory
			Client *S = new Client(atoi(argv[2]), argv[1]);
			details *d;
			char buf[MAX_BUF];
			void *buffer;
			
			S->Create_Socket();//connect server to the client
			S->ConnectClient();
			newfd = S->getCliSockfd();//get client socket
			cout<<"Do you want to register or login?"<<endl;
			cout<<"Enter 1 to Register"<<endl;
			cout<<"Enter 2 to login"<<endl;
			cin>>option;
			cout<<endl;
			
			//Select option to either register or login
			switch(option)
			{
				//to register and login
				case 1:
					send(newfd,"1",2,0);
					recv(newfd,buf,sizeof(buf),0);
					if(strcmp(buf,"register")==0)
					{	
						buffer=d->choose(option);
						d=(details *)buffer;
						send(newfd,d,sizeof(details),0);
						memset(&buf,0,MAX_BUF);
					}
					recv(newfd,buf,sizeof(buf),0);
					if(strcmp(buf,"success")==0)
					{
						cout<<endl;
						cout<<"Registration successfull"<<endl;
					}
					else
					{
						cout<<endl;
						cout<<"registration unsuccessful"<<endl;
						exit(0);
					}
					cout<<"You can now continue by logging in"<<endl;
					send(newfd,"2",2,0);
					recv(newfd,buf,sizeof(buf),0);	
					if(strcmp(buf,"login")==0)
					{
						buffer=d->choose(2);
						d=(details *)buffer;
						send(newfd,d,sizeof(details),0);
						memset(&buf,0,MAX_BUF);
						recv(newfd,buf,sizeof(buf),0);
						if(strcmp(buf,"success")==0)
						{
							cout<<endl;
							cout<<"login successful"<<endl;
							cout<<"You can now continue to chat with other users"<<endl;
				
						}
						if(strcmp(buf,"failure")==0)
						{
							cout<<"\nlogin unsuccessful"<<endl;
							cout<<"Session Terminated"<<endl;
							kill(getpid(),SIGINT);
						}
					}
					break;
					
				//login
				case 2:
					send(newfd,"2",2,0);
					recv(newfd,buf,sizeof(buf),0);	
					if(strcmp(buf,"login")==0)
					{
						buffer=d->choose(2);
						d=(details *)buffer;
						send(newfd,d,sizeof(details),0);
						memset(&buf,0,MAX_BUF);
						recv(newfd,buf,sizeof(buf),0);
						if(strcmp(buf,"success")==0)
						{
							cout<<"login successful"<<endl;
							cout<<"You can now continue to chat with other users"<<endl;
						}
						if(strcmp(buf,"failure")==0)
						{
							cout<<"\nLogin Unsuccessful"<<endl;
							cout<<"Terminated, Please Register to login"<<endl;
							kill(getpid(),SIGINT);
						}
					}
					break;
			}
			
			//thread recieve any mesage sent by server 
			thread readmsg(RecvData, newfd, flags); 	
			
			//thread to send messages to the server
			thread writemsg(SendData, newfd, flags); 
	
			//stop the threads
			readmsg.join();
			writemsg.join();
			
			//close client socket
			S->cliClose(S->getCliSockfd());
		}
	}
	catch(const char* str) {
		cout<<"Exception: "<<str<<endl;
	}
	return 0;
}
