#include <SockServer.h>
#include <details.h>

/*Creation of Server Socket using socket() system call and
error handling, if server socket is not created.
setsockopt() is used to connect multiple sockets of client.
Taking IP Address and Port Number through command line arguments.*/
void Server::create_socket()
{
	int opt = true;
	Server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(Server_socket < 0)
	{
		log("Fatal log::socket() error");
		exit(EXIT_FAILURE);
	}
	if(setsockopt(Server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))<0)
	{
		log("Fatal log::setsockopt() error");
		exit(EXIT_FAILURE);
	}	
	log("Info log::[+] Server Socket Created");

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
	if (bind(Server_socket,(struct  sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		log("Fatal log::bind() error");
		exit(EXIT_FAILURE);
	}
	log("Info log::[+] Server bind to %d port number");
	if(listen(Server_socket, 5)<0)
	{
		log("Fatal log::listen() error");
		exit(EXIT_FAILURE);
	}
	log("Info log::[+] Server listening to the clients");
}

//Server accepts the client
int Server::acceptclient(int sfd)
{
	len = sizeof(client_addr);
	Client_socket = accept(sfd, (struct sockaddr *)&client_addr, &len);
	if(Client_socket<0)
	{
		log("Fatal log::accept() failed");
		exit(EXIT_FAILURE);
	}
	log("Info log::[+] Server accepts the client");
	return Client_socket;
}
//close the server socket
void Server::servClose(int sfd)
{
	close(sfd);
}
//create fd sets
void Server::create_fdset()
{
	readfds = master;
	//max_sd = serverfd;
	//clear the sock set fds
	FD_ZERO(&readfds);
	FD_SET(serverfd,&readfds);
	max_socket = serverfd;
}

/*check if new client is connected and add the client sockets to the fd_set
and get the highest fds number required for select() function */
void Server::Add_Client_sockets()
{
	for(int i=0;i<max_clients;i++)
	{
		socketfd = client_socket[i];
		///if valid socket desc... then add to readfds lists
		if(socketfd> 0)
			FD_SET(socketfd,&readfds);
		//highest fds number
		if(socketfd > max_socket)
			max_socket = socketfd;
	}
}

/*new client connections are accepted and  
user registration followed by login */
void Server::registeruser_login(string &s,int &f)
{
	details *d1 = new details;
	char user_data[MAX_BUF] = {'\0',}; 
	int flag=0;
	char buf[MAX_BUF];
	if(FD_ISSET(serverfd, &readfds))
	{		
		int Client_Socketfd= acceptclient(serverfd);	
		int recvoption=recv(Client_Socketfd,buf,MAX_BUF,0);
		//check whether client wants to login or register
		switch(atoi(buf))
		{
			//register and login
			case 1:
				if(send(Client_Socketfd,"register",9,0)<0)
				{
					perror("send() error");
					exit(EXIT_FAILURE);
				}
				recv(Client_Socketfd,&user_data,sizeof(user_data),0);
				d1->database(user_data);
				send(Client_Socketfd,"success",8,0);
				break;
			//login
			case 2:
				send(Client_Socketfd,"login",8,0);
				memset(user_data,0,sizeof(user_data));
				recv(Client_Socketfd,&user_data,sizeof(user_data),0);

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
						send(Client_Socketfd,"success",8,0);

					}
					else
					{
						send(Client_Socketfd,"failure",8,0);
					}
				}
				fs.close();
				
				break;
		}
		//add the clients connecting to the server in a vector
		for(int i=0;i<max_clients;i++)
		{
			if(client_socket[i] == 0)
			{
				client_socket[i] = Client_Socketfd;
				log("Info log::[+] Adding the client sockfds to the list");
				strcpy(uids[i],d1->getUID());
				vs_csock.push_back(Client_Socketfd);
				break;
			}
		}
	}//end if fd_ISSET
}
//handle the clients that are disconnected
void Server::handledisconnect()
{
	socklen_t len = sizeof(getClientAddr());
	uint16_t port;
	struct sockaddr_in address = getClientAddr();
	getpeername(socketfd,(struct sockaddr*)&address, &len);						
	cout<<"[+] Client disconnected with IP: "<<inet_ntoa(address.sin_addr);
	cout<<" and with port number: "<<ntohs(address.sin_port)<<endl;
	cout<<"[+] Closing Socket with port  "<<ntohs(address.sin_port)<<endl;
	close(socketfd);
	client_socket[i] = 0;
}
//broadcast the message sent by one client to all the active clients
void Server::broadcast_msg(string uid)
{
	string UID;
	memset(&UID,0,MAX_BUF);
	
	for(int i=0;(i<vs_csock.size())&&(client_socket[i] !=0 );i++)
	{
		int socket=client_socket[i];
		if(socket==socketfd && socket!=serverfd && socket!=0)
		{
			UID=uids[i];
			break;
		}
	}


	for(int i=0;(i<vs_csock.size())&&(client_socket[i] !=0 );i++)
	{
		int socket = client_socket[i];
		
		if(socket != socketfd && socket != serverfd && socket !=0)
		{
			char sbuff[MAX_BUF] = {'\0',};
			strcpy(sbuff, "Message sent by ");
			strcat(sbuff,UID.c_str());
			strcat(sbuff,": ");
			strcat(sbuff,buff);
			strcat(sbuff,"\r\n");							
			write(socket, sbuff, strlen(sbuff));

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
		client_socket[i] = 0;	
	}
	serverfd =getServSockfd();
	FD_ZERO(&master);
	while(true)
	{	
		//createfds	
		create_fdset();
		// for adding new client scket to set
		Add_Client_sockets();
		//check if the socket is ready
		int Select_socket = select(max_socket+1,&readfds,NULL,NULL,NULL);
		//check if fds are set
		registeruser_login(userid,f);
		for(int i=0;i<max_clients;i++)
		{
			socketfd  = client_socket[i];
			if(FD_ISSET (socketfd, &readfds))
			{
				memset(buff,0,MAX_BUF);
				if((read(socketfd, buff,MAX_BUF)) == 0)
				{
					handledisconnect();	
			
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
	servClose(getServSockfd());
}
int Server::log(string logs)
{
	FILE *logfile;
	char filename[100]="log/Serverdata.log";
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
Server::~Server()
{
}
