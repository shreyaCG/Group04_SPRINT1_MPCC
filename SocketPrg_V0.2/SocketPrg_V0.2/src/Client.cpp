#include <ClientSocket.h>





void ClientSocket::cliConn()
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket() error");
		exit(EXIT_FAILURE);
	}
	cout<<"[+]Client Socket Created"<<endl;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(protno);
	server_addr.sin_addr.s_addr = inet_addr((const char*)ipaddr.c_str());
	
	cout<<"[+]Client bind to port no:"<<protno<<" and ip_address: "<<ipaddr<<endl;
	
	int ret = connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret < 0)
	{
		perror("connect() error: ");
		exit(EXIT_FAILURE);
	}

	cout<<"[+]Client connected to the server"<<endl;
}



void ClientSocket::cliClose(int sfd)
{
	close(sfd);
}

/*
void readData(promise<int>& dataready, promise<void>& consumed,int &sfd, char* buff)
{
	int n = dataready.get_future().get();    // wait for data ready
	std::cout <<"N:"<<n << endl;
    dataready = promise<int>{};  // reset
    consumed.set_value();        // mark data as consumed

	int ret = read(sfd,buff,MAX_BUF);
	cout<<"Client: "<<buff<<endl;
	//return ret;
}

void readData1(int &a)
{
	cout<<"Hello: "<<a<<endl;
}

void writeData(promise<int>& dataready, promise<void>& consumed,int &sfd, char*buff)
{
	// cout<<"Enter msg: ";
	// cin>>buff;
	int ret = write(sfd, buff, strlen(buff));
	if(strcmp(buff,"bye\n")==0)
	{
		exit(0);
	}

	


	consumed = promise<void>{};      // reset
    
	
	
	dataready.set_value(ret);          // make data available
       
    consumed.get_future().wait();    // wait for the data to be consumed
	
}

*/
void readData1(int &sfd, char*buff)
{
	memset(buff,0,sizeof(buff));
	//cout<<"From Server: "<<sfd<<endl;
	int ret = read(sfd,buff,MAX_BUF);
	cout<<buff<<endl;
	memset(buff,0,sizeof(buff));
}


void writeData1(int &sfd, char*buff)
{
	memset(buff,0,sizeof(buff));
	cout<<"Message: ";
	
	string temp;
	getline(cin,temp);
	
	strcpy(buff,temp.c_str());
	
	write(sfd,buff,strlen(buff));
	
}


// this function received data from the server and stores it in rcvDataBuf array
void recv_data(int clientSocketFd, int flags)
{

   int dataRecvd;
   char rcvDataBuf[MAX_BUF];

   while(1)
   {
      memset(&rcvDataBuf, 0, MAX_BUF);
      dataRecvd = recv(clientSocketFd, rcvDataBuf, MAX_BUF, flags);
      // if chatroom is full then exit
      if(!strcmp(rcvDataBuf,"#FULL"))
      {
         cout<<"Chatroom is full. Exiting"<<endl;
         close(clientSocketFd);
         exit(1);
      }
      if(dataRecvd>0) cout<<rcvDataBuf<<endl;
   }
}

// this function sends data taken from the terminal to the server
void send_data(int clientSocketFd, int flags)
{
   char sendDataBuf[MAX_BUF];
   int dataSent;

   while(1)
   {
      memset(&sendDataBuf, 0, MAX_BUF);
      cin.clear();

      cin.getline(sendDataBuf,MAX_BUF);
      
      dataSent = send(clientSocketFd, sendDataBuf, strlen(sendDataBuf), flags);
      if(!strcmp(sendDataBuf, "bye"))
      {
         close(clientSocketFd);
         exit(1);
      }
   }
}