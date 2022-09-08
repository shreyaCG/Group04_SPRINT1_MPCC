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
			system("clear");
			int newfd, flags=0,option;
			
			//allocate dynamic memory
			Client *S = new Client(atoi(argv[2]), argv[1]);
			details d;

			S->Create_Socket();//connect server to the client
			S->ConnectClient();
			newfd = S->getCliSockfd();//get client socket

			char buf[MAX_BUF];
			
			cout<<"Do you want to register or login?"<<endl;
			cout<<"\tEnter 1 to Register"<<endl;
			cout<<"\tEnter 2 to login"<<endl;
			cout<<"Choose your option: ";
			cin>>option;
			
			//Select option to either register or login
			switch(option)
			{
				//to register and login
				case 1: 
					system("clear");
					send(newfd,"1",2,0);
					recv(newfd,buf,sizeof(buf),0);
					if(strcmp(buf,"register")==0)
					{
						d.setdetails();
						string str = d.toString();
						cout<<str<<endl;
						send(newfd,str.c_str(),str.length(),0);
					}
					memset(&buf,0,MAX_BUF);
					recv(newfd,buf,sizeof(buf),0);
					if(strcmp(buf,"success")==0)
					{
						cout<<endl;
						cout<<"Registration successfull"<<endl;
					}
					else
					{
						cout<<endl;
						cout<<"Registration unsuccessful"<<endl;
						exit(0);
					}
					break;	
				//	goto login_user;
				//login
				case 2: login_user:
					system("clear");
					send(newfd,"2",2,0);
					recv(newfd,buf,sizeof(buf),0);	
					if(strcmp(buf,"login")==0)
					{
						cout<<"Enter credentials to login"<<endl;
						d.setdetails();
						string str1 = d.toString();
						cout<<str1<<endl;
						send(newfd,str1.c_str(),str1.length(),0);

						//d=(details *)buff;
						//send(newfd,d,sizeof(details),0);
						
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
							//kill(getpid(),SIGINT);
							exit(0);
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
