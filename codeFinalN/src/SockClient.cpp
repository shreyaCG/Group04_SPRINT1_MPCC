#include <SockClient.h>
#include <details.h>

//creates client sockets
void Client::Create_Socket()
{
	//client socket creation
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		log("Fatal log::socket() error");
		exit(EXIT_FAILURE);
	}
	log("Info log::[+] Client Socket Created");
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(Port);
	server_addr.sin_addr.s_addr = inet_addr((const char*)ipaddr.c_str());
	
	log("Info log::[+] Client bind to port number and ip_address");
}
//connect the client to the server
void Client::ConnectClient()
{
	//connect the client 
	int ret = connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret < 0)
	{
		log("Fatal log::connect() error: ");
		exit(EXIT_FAILURE);
	}
	log("Info log::[+] Client connected to the server");
}

//close the client socket
void Client::cliClose(int sfd)
{
	close(sfd);
}

// function send message to client that the chatroom is full
void RecvData(int clientSocketFd, int flags)
{

   int dataRecvd;
   char rcvDataBuf[MAX_BUF];

   while(1)
   {
      memset(&rcvDataBuf, 0, MAX_BUF);
      dataRecvd = recv(clientSocketFd, rcvDataBuf, MAX_BUF, flags);
    
      if(dataRecvd>0) 
	      cout<<rcvDataBuf<<endl;
   }
}

// this function sends data taken from the terminal to the server
void SendData(int clientSocketFd, int flags)
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
void Client::log(string logs)
{
	FILE *logfile;
	char filename[100]="logger/Clientdata.log";
	time_t ltime=time(NULL);
	struct tm res;
	char TIMESTAMP[32];
	char* msg = const_cast<char*>(logs.c_str());
	localtime_r(&ltime,&res);
	asctime_r(&res,TIMESTAMP);

	logfile=fopen(filename,"a+");
	fprintf(logfile,"\n~~%s\t%s\n-------------\n",TIMESTAMP,msg);
	fclose(logfile);
}
