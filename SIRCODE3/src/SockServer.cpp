#include <SockServer.h>
#include <details.h>

/*Creation of Server Socket using socket() system call and
error handling, if server socket is not created.
setsockopt() is used to connect multiple sockets of client.
Taking IP Address and Port Number through command line arguments.*/
void Server::create_socket()
{
	int opt = true;
	server_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socketfd < 0)
	{
		log("Fatal log:socket() error");
		exit(EXIT_FAILURE);
	}
	if(setsockopt(server_socketfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))<0)
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
//Server accepts the client
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
//create fd sets
void Server::Create_fdset()
{
	readfds = master;
	//clear the sock set fds
	FD_ZERO(&readfds);
	FD_SET(serverfd,&readfds);
	max_socket = serverfd;
}

//check the number of clients connected and the maximum sockets created
void Server::Add_ClientSocketfd()
{
	for(int i=0;i<max_clients;i++)
	{
		SocketFD= client_sockets[i];
		///if valid socket desc... then add to readfds lists
		if(SocketFD > 0)
			FD_SET(SocketFD,&readfds);
		//highest fds number, need it for the select fucntion
		if(SocketFD > max_socket)
			max_socket = SocketFD;
	}
}

//check if the fd is set
void Server::registeruser_login(string &s,int &f)
{
	details *d1 = new details;
	char user_data[MAX_BUF] = {'\0',}; 
	int flag=0;
	char buf[MAX_BUF];
	if(FD_ISSET(serverfd, &readfds))
	{		
		int Client_Socket = acceptclient(serverfd);	
		int recvoption=recv(Client_Socket,buf,MAX_BUF,0);
		//check whether client wants to login or register
		switch(atoi(buf))
		{
			//register and login
			case 1:
				if(send(Client_Socket,"register",9,0)<0)
				{
					log("Fatal log: send() error");
					exit(EXIT_FAILURE);
				}
				recv(Client_Socket,&user_data,sizeof(user_data),0);
				d1->database(user_data);
				send(Client_Socket,"success",8,0);
				break;
			//login
			case 2:
				send(Client_Socket,"login",8,0);
				memset(user_data,0,sizeof(user_data));
				recv(Client_Socket,&user_data,sizeof(user_data),0);
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
						string middle;
						vector<string> vstring;
        					stringstream check(user_data);
        					while(getline(check,middle,'|'))
        					{
                					vstring.push_back(middle);
        					}
						d1->setUID((char*)vstring[0].c_str());
						d1->setPassword((char*)vstring[1].c_str());
						f=1;
						send(Client_Socket,"success",8,0);

					}
					else
					{
						send(Client_Socket,"failure",8,0);
					}
				}
				fs.close();
				
				break;
		}
		//add the clients connecting to the server in a vector
		for(int i=0;i<max_clients;i++)
		{
			if(client_sockets[i] == 0)
			{
				client_sockets[i] = Client_Socket;
				log("Info log: [+] Adding the client sockfds to the list");
				strcpy(uids[i],d1->getUID());
				vs_csock.push_back(Client_Socket);
				break;
			}
		}
	}//end if fd_ISSET
}
//handle the clients that are disconnected
void Server::handle_disconnect()
{
	socklen_t len = sizeof(getClientAddr());
	uint16_t port;
	struct sockaddr_in address = getClientAddr();
	getpeername(SocketFD,(struct sockaddr*)&address, &len);						
	log("Info log: [+] Client disconnected ");
	log("Info log: [+] Closing Socket with port  ");
	close(SocketFD);
	client_sockets[i] = 0;
}
//broadcast the message sent by one client to all the active clients
void Server::broadcast_msg(string uid)
{
	string UID;
	memset(&UID,0,MAX_BUF);
	
	for(int i=0;(i<vs_csock.size())&&(client_sockets[i] !=0 );i++)
	{
		int socket=client_sockets[i];
		if(socket==SocketFD && socket!=serverfd && socket!=0)
		{
			UID=uids[i];
			break;
		}
	}

	for(int i=0;(i<vs_csock.size())&&(client_sockets[i] !=0 );i++)
	{
		int socket = client_sockets[i];
		
		if(socket != SocketFD && socket != serverfd && socket !=0)
		{
			char tbuff[MAX_BUF] = {'\0',};
			strcpy(tbuff, "Message sent by ");
			strcat(tbuff,UID.c_str());
			strcat(tbuff,": ");
			strcat(tbuff,buff);
			strcat(tbuff,"\r\n");							
      			write(socket, tbuff, strlen(tbuff));
		}
	}
}	
//checks if the socket is ready for reading or writing
void Server :: serv_select()
{
	string userid="";
	int f=0;
	for(int i=0;i<max_clients;i++)
	{
		client_sockets[i] = 0;	
	}
	serverfd =getServSockfd();
	FD_ZERO(&master);
	while(true)
	{	
		//createfds	
		Create_fdset();
		// for adding new client scket to set
		Add_ClientSocketfd();
		//check if the socket is ready
		int SelectSocket = select(max_socket+1,&readfds,NULL,NULL,NULL);
		//check if fds are set
		registeruser_login(userid,f);
		for(int i=0;i<max_clients;i++)
		{
			SocketFD = client_sockets[i];
			if(FD_ISSET (SocketFD, &readfds))
			{
				memset(buff,0,MAX_BUF);
				if((readVal = read(SocketFD, buff,MAX_BUF)) == 0)
				{
					handle_disconnect();	
			
					if(vs_csock.size()==1)
					{
						vs_csock.erase(vs_csock.begin());
					}
					else
					{
						vs_csock.erase(vs_csock.begin()+i);
					
					}
				}
				else
				{
				//broadcast message	
					broadcast_msg(userid);	
					memset(buff,0,MAX_BUF);
				}

			}
		}

	}// end of while loop
	Server_Close(getServSockfd());
}
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
