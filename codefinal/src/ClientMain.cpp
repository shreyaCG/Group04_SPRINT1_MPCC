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
			int new_Clientfd, flags=0,option;
			
			//allocate dynamic memory
			Client *C = new Client(atoi(argv[2]), argv[1]);
			details d;

			C->Create_Socket();//connect server to the client
			C->ConnectClient();
			new_Clientfd = C->getClientSockfd();//get client socket

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
					send(new_Clientfd,"1",2,0);
					recv(new_Clientfd,buf,sizeof(buf),0);
					if(strcmp(buf,"register")==0)
					{
						d.setdetails();
						string str = d.toString();
						cout<<str<<endl;
						send(new_Clientfd,str.c_str(),str.length(),0);
					}
					memset(&buf,0,MAX_BUF);
					recv(new_Clientfd,buf,sizeof(buf),0);
					if(strcmp(buf,"success")==0)
					{
						cout<<endl;
						cout<<"Registration successfull"<<endl;
						exit(1);
					}
					else
					{
						cout<<endl;
						cout<<"Registration unsuccessful"<<endl;
						exit(0);
					}
					break;	
				//login
				case 2:
					send(new_Clientfd,"2",2,0);
					recv(new_Clientfd,buf,sizeof(buf),0);	
					if(strcmp(buf,"login")==0)
					{
						d.setdetails();
						string str1 = d.toString();
						cout<<str1<<endl;
						send(new_Clientfd,str1.c_str(),str1.length(),0);
		
						memset(&buf,0,MAX_BUF);
						recv(new_Clientfd,buf,sizeof(buf),0);
						if(strcmp(buf,"success")==0)
						{
							cout<<"login successful"<<endl;
							cout<<"You can now continue to chat with other users"<<endl;
						}
						if(strcmp(buf,"failure")==0)
						{
							cout<<"\nLogin Unsuccessful"<<endl;
							cout<<"Terminated, Please Register to login"<<endl;
							exit(0);
						}
					}
					break;
			}
			
			//thread recieve any mesage sent by server 
			thread readmsg(RecvData, new_Clientfd, flags); 	
			
			//thread to send messages to the server
			thread writemsg(SendData, new_Clientfd, flags); 
	
			//stop the threads
			readmsg.join();
			writemsg.join();
			
			//close client socket
			C->clientClose(C->getClientSockfd());
		}
	}
	catch(const char* str) {
		cout<<"Exception: "<<str<<endl;
	}
	return 0;
}
