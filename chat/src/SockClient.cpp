#include <SockClient.h>
#include<details.h>
//connect the client to the server
void Client::create_socket()
{
	//client socket creation
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
}
void Client::clientconnect()
{
	//connect the client 
	int ret = connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret < 0)
	{
		perror("connect() error: ");
		exit(EXIT_FAILURE);
	}

	cout<<"[+]Client connected to the server"<<endl;
}
//close the client socket
void Client::Closesoc(int sfd)
{
	close(sfd);
}
//login using registered username
void writeuser(int &sfd, char*buff)
{
	memset(buff,0,sizeof(buff));
	cout<<"login with username: ";
	
	string temp;
	getline(cin,temp);
	
	strcpy(buff,temp.c_str());
	
	write(sfd,buff,strlen(buff));
	
}

// function send message to client that the chatroom is full
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
void details::setdetails()
{
	cout<<"Enter the uid: ";
	cin>>uid;
	cout<<"Enter the password: ";
	cin>>password;
	 
}
/*void details::setpass()
{
	cout<<"enter password: ";
	cin>>password;
}*/





