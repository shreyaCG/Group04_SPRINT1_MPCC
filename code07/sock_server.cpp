#include "sockhead.h"

int main(int argc, char *argv[])
{
	int serverfd, sd, max_sd;
	char buff[MAX_BUF];
	TCP_Server *S = new TCP_Server(atoi(argv[2]), argv[1]);
	S->servConn();
	serverfd = S->getServSockfd();
	while(true)
	{
		int newSockfd = S->servAccept(serverfd);
		if(fork()==0){
				while(1){
				/*
				//read/write operations
				char buff[MAX_BUF] = {'\0',};
				memset(buff,0, sizeof(buff));
				read(newSockfd,buff, MAX_BUF);
				cout<<"Client "<<ntohs(S->getClientAddr().sin_port)<<" Sent: "<<buff<<endl;
				if(strcmp(buff,"bye")==0)
					break;
				char tbuff[MAX_BUF] = {'\0',};
				strcpy(tbuff,"From Server: ");
				strcat(tbuff,buff );
				write(newSockfd, tbuff, strlen(tbuff));
				
				memset(tbuff,0, MAX_BUF);
				memset(buff,0,MAX_BUF);
				*/
				int ret=0;
				char str[MAX_BUF];
				memset(&str,0,MAX_BUF);
				if((ret = read(newSockfd,&str, MAX_BUF))>0)
				{
					cout<<"ret: "<<ret<<endl;
					Test_Class *T =new Test_Class;
					//T = reinterpret_cast<Test_Class*>(&buff);
					cout<<str<<endl;
					//cout<<T->getName()<<endl;
					//cout<<T->getID()<<endl;
				}
				else{
					cout<<"Out"<<endl;
					break;
				}
				/*Test_Class T;
				if(read(newSockfd,&T, sizeof(T)))
				{
				cout<<T.getName()<<endl;
				cout<<T.getID()<<endl;
				}
				else
					break;
				*/
				}//end while /read/write
			}//close of fork if
			close(newSockfd);
			
			

	}
	close(serverfd);
	return 0;
}
