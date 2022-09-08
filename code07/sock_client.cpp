#include "sockhead.h"

int main(int argc, char *argv[])
{
	int serverfd, sd, max_sd;
	int csockfd;
	char buff[MAX_BUF];
	Test_Class T(1001,"Shankar");
	TCP_Client *C = new TCP_Client(atoi(argv[2]), argv[1]);
	C->cliConn();
	csockfd = -1;
	csockfd = C->getCliSockfd();
	//while(1){
	/*
	memset(&buff, 0, MAX_BUF);
	cin.clear();

    cin.getline(buff,MAX_BUF);
	write(csockfd,buff,strlen(buff));
	if(strcmp(buff, "bye")==0)
		break;
	else{
			memset(buff,0,MAX_BUF);
      		read(csockfd,buff,MAX_BUF);
      		cout<<buff<<endl;
      		memset(buff,0,MAX_BUF);
      		
		}
	*/
	string str = T.toString();
	//strcpy(buff,((char*)T).c_str());
	string str2 = "Hello|World";
	cout<<"ret: "<<str2.size()<<" \t"<<str2<<endl;
	cout<<"Length: "<<str2.length()<<endl;
	write(csockfd,str.c_str(),str.length());
	
	//write(csockfd,&T,sizeof(T));
	//}


	C->cliClose(C->getCliSockfd());
	return 0;
}
