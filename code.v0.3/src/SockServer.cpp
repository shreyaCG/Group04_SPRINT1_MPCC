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
	//bind the server to a port
	if (bind(Server_socket,(struct  sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		log("Fatal log::bind() error");
		exit(EXIT_FAILURE);
	}
	log("Info log::[+] Server bind to %d port number");
	//wait for client connection
	if(listen(Server_socket, 5)<0)
	{
		log("Fatal log::listen() error");
		exit(EXIT_FAILURE);
	}
	log("Info log::[+] Server listening to the clients");
}

/*Server accepts the client which is trying to connect using accept() system call
and error handling is done if the client connections are not accepted*/
int Server::acceptclient(int socketfd)
{
	len = sizeof(client_addr);
	if((accept(socketfd, (struct sockaddr *)&client_addr, &len))<0)
	{
		log("Fatal log::accept() failed");
		exit(EXIT_FAILURE);
	}
	log("Info log::[+] Server accepts the client");
	return Client_socket;
}
//close the server socket 
void Server::servClose(int socketfd)
{
	close(socketfd);
}
/*fd sets are created and cleared
  the server socketfd is stored into the fdset
  max_socket is set to the server socketfd*/
void Server::create_fdset()
{
	readfds = master;//copy of fdset
	FD_ZERO(&readfds);//clear the fd set
	FD_SET(serverfd,&readfds);//store serverfd in fdset
	max_socket = serverfd;
}

/*check if new client is connected and add the client sockets to the fd_set
and get the highest fd's number which is required for select() function */
void Server::Add_Client_sockets()
{
	for(int i=0;i<max_clients;i++)
	{
		socketfd = client_socket[i];
		///if valid socket decriptors then add them to fd_set
		if(socketfd> 0)
			FD_SET(socketfd,&readfds);
		//highest fds number
		if(socketfd > max_socket)
			max_socket = socketfd;
	}
}

/*checking if the serverfd is present in the set and
user registration is done  followed by login with the help of switch case
the socket fds of all the active clients are stored in vector*/
void Server::registeruser_login(string &s,int &f)
{
	details *d1 = new details;
	char user_data[MAX_BUF] = {'\0',}; 
	char buf[MAX_BUF];
	int flag=0;
	//check if serverfd is present in set
	if(FD_ISSET(serverfd, &readfds))
	{		
		int Client_Socketfd= acceptclient(serverfd);	
		int recvoption=recv(Client_Socketfd,buf,MAX_BUF,0);
		//check whether client wants to login or register
		switch(atoi(buf))
		{
			//registration
			case 1:
				if(send(Client_Socketfd,"register",9,0)<0)
				{
					log("Fatal log: send() error");
					exit(EXIT_FAILURE);
				}
				//Recieves the userID and Password
				if(recv(Client_Socketfd,&user_data,sizeof(user_data),0)<0)
				{
					log("Fatal log: recv() error");
					exit(EXIT_FAILURE);
				}
				//Store the registered credentials in a file
				d1->database(user_data);
				//Sends success message if registration is successful
				send(Client_Socketfd,"success",8,0);
				break;
			//login
			case 2:
				if(send(Client_Socketfd,"login",8,0)<0)
				{
					log("Fatal log: recv() error");
					exit(EXIT_FAILURE);
				}
				memset(user_data,0,sizeof(user_data));
				//Recieved login credentials
				if(recv(Client_Socketfd,&user_data,sizeof(user_data),0)<0)
				{
					log("Fatal log: recv() error");
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
						//Tokenize the login Credentials 
						string middle;
						vector<string> vstring;
        					stringstream check(user_data);
        					while(getline(check,middle,'|'))
        					{
                					vstring.push_back(middle);
        					}
						d1->setUID((char*)vstring[0].c_str());
						d1->setPassword((char*)vstring[1].c_str());
						send(Client_Socketfd,"success",8,0);

					}
					else
					{
						//Login is failed fo users that are not registered
						send(Client_Socketfd,"failure",8,0);
					}
				}
				fs.close();
				
				break;
		}
		//add the active client socketfd's in a vector
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
/*The IPAddress and port number of the disconnected clients are displayed
 and their socket fd's are erased from the vector*/
void Server::handledisconnect()
{
	socklen_t len = sizeof(getClientAddr());
	uint16_t port;
	struct sockaddr_in address = getClientAddr();
	getpeername(socketfd,(struct sockaddr*)&address, &len);						
	log("Info log: [+] Client disconnected ");
	log("Info log: [+] Socket closed");
	close(socketfd);
	client_socket[i] = 0;
	if(vs_csock.size()==1)
	{
		vs_csock.erase(vs_csock.begin());
	}
	else
	{
		vs_csock.erase(vs_csock.begin()+i);					
	}
	
}
/*iterate through the vector which has active client fds and 
 broadcast the message sent by one client to all other clients connected to the server
 along witheir respective user ID*/ 
void Server::broadcast_msg(string uid)
{
	string UID;
	memset(&UID,0,MAX_BUF);
	//to get the user ID of the client which is sending the message
	for(int i=0;(i<vs_csock.size())&&(client_socket[i] !=0 );i++)
	{
		int socket=client_socket[i];
		if(socket==socketfd && socket!=serverfd && socket!=0)
		{
			UID=uids[i];
			break;
		}
	}
	//broadcast the message to all the active clients
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
/* select() allows the server to monitor multiple client connected 
 and checks when client sends data to process .
 * Any client that is disconnected will be handled
 * the message sent by one client is broadcasted to all other active cllients*/
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
		//Registration and login
		registeruser_login(userid,f);
		for(int i=0;i<max_clients;i++)
		{
			socketfd  = client_socket[i];
			if(FD_ISSET (socketfd, &readfds))
			{
				memset(buff,0,MAX_BUF);
				if((read(socketfd, buff,MAX_BUF)) == 0)
				{
					//handle the clients that are disconnected
					handledisconnect();	
				}
				else
				{
					//broadcast message	
					broadcast_msg(userid);	
					memset(buff,0,MAX_BUF);
				}

			}//end of FD_ISSET
		}

	}// end of while loop
	servClose(getServSockfd());
}
/*this function creates a logfile which stores all the log messages at runtime 
 along with the time stamp*/
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
