#include <Sock_Server.h>
#include <details.h>

/*Creation of Server Socket using socket() system call and
error handling, if server socket is not created.
setsockopt() is used to connect multiple sockets of client.
Taking IP Address and Port Number through command line arguments.*/
void Server::create_socket()
{
	int option = true;
	server_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socketfd < 0)
	{
		log("Fatal log:socket() error");
		exit(EXIT_FAILURE);
	}
	if(setsockopt(server_socketfd, SOL_SOCKET, SO_REUSEADDR, (char *)&option, sizeof(option))<0)
	{
		log("Fatal log: etsockopt() error");
		exit(EXIT_FAILURE);
	}	
	log("Info log: [+] Server Socket Created");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portno);
	server_addr.sin_addr.s_addr = inet_addr((const char*)ipaddr.c_str());
}

/*Bind the server to a port using bind() and error handling if server 
is not binded to the port.
Server is waiting for the client connection
and error handling if server is not waiting for the clients.*/
void Server::bind_listen()
{
	int Is_bind=bind(server_socketfd,(struct  sockaddr*)&server_addr,sizeof(server_addr));
	if(Is_bind<0)
	{
		log("Fatal log: bind() error");
		exit(EXIT_FAILURE);
	}
	log("Info log: [+] Server bind to the port");
	if(listen(server_socketfd, 5)<0)
	{
		log("Fatal log: listen() error");
		exit(EXIT_FAILURE);
	}
	log("Info log: [+] Server listening to the clients");
}
/*Server accepts the client which is trying to connect using accept() system call
 and error handling is done if the client connections are not accepted*/
int Server::acceptclient(int sfd)
{
	len = sizeof(client_addr);
	Client_Socketfd = accept(sfd, (struct sockaddr *)&client_addr, &len);
	if(Client_Socketfd<0)
	{
		log("Fatal log: accept() failed");
		exit(EXIT_FAILURE);
	}
	log("Info log: [+] Server accepts the client");
	return Client_Socketfd;
}
//close the server socket
void Server::Server_Close(int socketfd)
{
	close(socketfd);
}
/*user registration is done  followed by login with the help of switch case
 the socket fds of all the active clients are stored in vector*/
void Server::registeruser_login(int newfd,vector<int>&v,int* clisockets,char UIDS[SIZE][SIZE])
{
	details *d1 = new details; 
	char user_data[MAX_BUF] = {'\0',};
        char buf[MAX_BUF]={'\0',};	
	int flag=0;
	int recvoption=recv(newfd,buf,MAX_BUF,0);
	//check whether client wants to login or register
	switch(atoi(buf))
	{
		//registeration
		case 1:
		if(send(newfd,"register",9,0)<0)
		{
			log("Fatal log: send() error");
			exit(EXIT_FAILURE);
		}
		//Receieved UserID and Password
		if(recv(newfd,&user_data,sizeof(user_data),0)<0)
		{
			log("Fatal log: recv() error");
			exit(EXIT_FAILURE);
		}
		//Stores registered users in a file
		d1->database(user_data);
		if(send(newfd,"success",8,0)<0)
		{
			log("Fatal log: send() error");
			exit(EXIT_FAILURE);
		}
		break;
		//login
		case 2:
		if(send(newfd,"login",8,0)<0)
		{
			log("Fatal log: send() error");
			exit(EXIT_FAILURE);
		}
		memset(user_data,0,sizeof(user_data));
		//Receives the login credentials
		if(recv(newfd,&user_data,sizeof(user_data),0)<0)
		{
			log("Fatal log: recv() error");
			exit(EXIT_FAILURE);
		}
		//Verify if the login credentials matches the registered credentials			
		fstream fs;
		string line;
		fs.open("data/registered.txt");
		if(fs.is_open())
		{
			while(!fs.eof())
			{
				getline(fs,line);		
				if((strcmp(user_data,line.c_str())==0))
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
			{
				//Tokenize the login credentials
				string middle;
				vector<string> vstring;
        			stringstream check(user_data);
        			while(getline(check,middle,'|'))
        			{
                			vstring.push_back(middle);
        			}
				d1->setUID((char*)vstring[0].c_str());
				d1->setPassword((char*)vstring[1].c_str());
				if(send(newfd,"success",8,0)<0)
				{
					log("Fatal log: recv() error");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				if(send(newfd,"failure",8,0)<0)
				{
					log("Fatal log: recv() error");
					exit(EXIT_FAILURE);
				}
			}
		}
		fs.close();	
		break;
	}
	//add the active client socketfd's in a vector
	for(int i=0;i<MAXCLIENT;i++)
	{
		if(clisockets[i] == 0)
		{
			clisockets[i] = newfd;
			log("Info log: [+] Adding the client sockfds to the list");
			strcpy(UIDS[i],d1->getUID());
			v.push_back(newfd);
			break;
		}
	}
}
/*iterate through the vector which has active client fds and
 broadcast the message sent by one client to all other clients connected to the server
 along witheir respective user ID*/
void Server::broadcast_msg(char* msg,vector<int>&v,int sockFD,int servfd,int* clisockets,char UIDS[SIZE][SIZE])
{
	string UID;
	memset(&UID,0,MAX_BUF);
	//to get the user ID of the client which is sending the message	
	for(int i=0;(i<v.size())&&(clisockets[i] !=0 );i++)
	{
		int socket=clisockets[i];
		if(socket==sockFD && socket!=servfd && socket!=0)
		{
			UID=UIDS[i];
			break;
		}
	}
	//broadcast the message to all the active clients
	for(int i=0;(i<v.size())&&(clisockets[i] !=0 );i++)
	{
		int socket = clisockets[i];
		
		if(socket != sockFD && socket != servfd && socket !=0)
		{
			char tbuff[MAX_BUF] = {'\0',};
			strcpy(tbuff, "Message sent by ");
			strcat(tbuff,UID.c_str());
			strcat(tbuff,": ");
			strcat(tbuff,msg);
			strcat(tbuff,"\r\n");							
      			write(socket, tbuff, strlen(tbuff));
		}
	}
}	
/*select() allows the server to monitor multiple client connected
 and checks when client sends data to process .
 Any client that is disconnected will be handled
 the message sent by one client is broadcasted to all other active cllients*/
void Server :: serv_select()
{
	int SocketFD,max_socket;
	char buff[MAX_BUF]={'\0'};
	details *d2=new details;
	vector<int>v_clientsock;
	char uids[SIZE][SIZE];
	int client_sockets[SIZE];
	for(int i=0;i<MAXCLIENT;i++)
	{
		client_sockets[i] = 0;	
	}
	int serverfd =getServSockfd();
	fd_set readfds,master;
	FD_ZERO(&master);
	while(true)
	{	
		readfds = master;
		//clear the sock set fds
		FD_ZERO(&readfds);
		//Add the serverfd to the fd_set
		FD_SET(serverfd,&readfds);
		max_socket = serverfd;
		
		for(int i=0;i<MAXCLIENT;i++)
		{
			SocketFD= client_sockets[i];
			//if valid socket desc... then add to readfds lists
			if(SocketFD > 0)
				FD_SET(SocketFD,&readfds);
			//highest fds number, need it for the select fucntion
			if(SocketFD > max_socket)
				max_socket = SocketFD;
		}
		int SelectSocket = select(max_socket+1,&readfds,NULL,NULL,NULL);
		//Registration and login

		if(FD_ISSET(serverfd, &readfds))
		{		
			int Client_Socket = acceptclient(serverfd);
			registeruser_login(Client_Socket,v_clientsock,client_sockets,uids);
		
		}
		for(int i=0;i<MAXCLIENT;i++)
		{
			SocketFD = client_sockets[i];
			if(FD_ISSET (SocketFD, &readfds))
			{
				memset(buff,0,MAX_BUF);
				int readVal = read(SocketFD, buff,MAX_BUF);
				if(readVal==0)
				{
					log("Info log: [+] Client disconnected ");
					close(SocketFD);
					client_sockets[i] = 0;
					if(v_clientsock.size()==1)
					{
						v_clientsock.erase(v_clientsock.begin());
					}
					else
					{
						v_clientsock.erase(v_clientsock.begin()+i);	
					}
				}
				else
				{
					//broadcast message	
					broadcast_msg(buff,v_clientsock,SocketFD,serverfd,client_sockets,uids);	
					memset(buff,0,MAX_BUF);
				}

			}
		}

	}// end of while loop
	Server_Close(getServSockfd());
}
/*this function creates a logfile which stores all the log messages at runtime
 along with the time stamp*/
void Server::log(string logs)
{
	FILE *logfile;
	char filename[100]="logs/Serverdata.log";
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
