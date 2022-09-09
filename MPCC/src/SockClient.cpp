#include <SockClient.h>
#include <details.h>

/*creates client sockets and error handling is done if sockets are not created
 takes the port number and ipaddress through command line*/

void Client::Create_Socket()
{
	//client socket creation
	Client_Socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(Client_Socketfd < 0)
	{
		perror("socket() error");
		exit(EXIT_FAILURE);
	}
	log("Info log: [+] Client Socket Created");
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(Port);
	server_addr.sin_addr.s_addr = inet_addr((const char*)ipaddr.c_str());
	
	log("Info log: [+] Client bind to port");
}
/*connect the client to the server 
and error handling if connection is failed*/
void Client::ConnectClient()
{
	//connect the client 
	int Connect= connect(Client_Socketfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(Connect < 0)
	{
		log("Fatal log: connect() error: ");
		exit(EXIT_FAILURE);
	}
	log("Info log: [+] Client connected to the server");
}

//close the client socket
void Client::ClientClose(int socketfd)
{
	close(socketfd);
}


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

/*this function sends data message sent by the client
  from the terminal to the server*/
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
/*This function creates a logfile and stores all the log messages 
 along with the timestamp*/
void Client::log(string logs)
{
	FILE *logfile;
	char filename[100]="logs/Clientdata.log";
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
