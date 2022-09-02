#include <SockServer.h>
#include<details.h>
//Creation of Server Socket
void Server::create_socket()
{
	int opt = true;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket() error");
		exit(EXIT_FAILURE);
	}

	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))<0)
	{
		perror("setsockopt() error");
		exit(EXIT_FAILURE);
	}
	
	cout<<"[+] Server Socket Created"<<endl;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(protno);
	server_addr.sin_addr.s_addr = inet_addr((const char*)ipaddr.c_str());
}
//Bind the server to a port and listen to the clients
void Server::bind_listen()
{
	int retbind = bind(sockfd,(struct  sockaddr*)&server_addr,sizeof(server_addr));
	if(retbind<0)
	{
		perror("bind() error");
		exit(EXIT_FAILURE);
	}
	cout<<"[+]Server bind to port no:"<<protno<<endl;
	if(listen(sockfd, 5)<0)
	{
		cout<<"[+]Server listening to the clients"<<endl;
	}
}
//Server accepts the client
int Server::acceptclient(int sfd)
{
	len = sizeof(client_addr);
	newsockfd = accept(sfd, (struct sockaddr *)&client_addr, &len);
	if(newsockfd<0)
	{
		perror("accept() failed");
		exit(EXIT_FAILURE);
	}
	cout<<"[+]Server accept the client"<<endl;
	return newsockfd;
}
//close the server socket
void Server::servClose(int sfd)
{
	close(sfd);
}
//function to recieve the message from client
int readData1(int &sfd, char*buff)
{
	
	memset(buff, 0, MAX_BUF);
	int ret = read(sfd,buff,MAX_BUF);
	
	return ret;
}
//function to send the message to the client
int writeData1(int &sfd, char*buff)
{
	memset(buff, 0, MAX_BUF);
	
	strcpy(buff,"Welcome!!!");
	int ret = write(sfd,buff,strlen(buff));
	memset(buff, 0, MAX_BUF);
	return ret;
}
//store the registered users in a file
/*void details::handleusers(details &d1)
{
//	list<string>l1;
//	map<int,string>map1;
	fstream fs;
	fs.open("registered.txt", ios::in | ios::app);
	fs<<d1.getUID()<<" ";
	fs<<d1.getPassword()<<endl;
	fs.close();
}*/
void details::validate(details &d1)
{

	string user=d1.getUID();
	string pass=d1.getPassword();
	map1.insert({user,pass});
	//map1[uid]=pass;
//	map1[uid]=pass;
	//cout<<uid<<endl;
	//cout<<pass<<endl;
	/*fstream fs;
	fs.open("registered.txt");
	string line;
	while(!fs.eof())
	{
		getline(fs,line);
		list1.push_back(line);
	}
	for(auto it =list1.begin();it!=list1.end();it++)
	{	
		string str=*it;
		int pos = str.find(" ");
	        string UID =str.substr(0,pos);	
                string pass=str.substr(pos+1);
		if(!UID.find("@"))
		{
			map1.insert({UID,pass});
			cout<<"works fine"<<endl;
		}
		else
		{
			cout<<"invalid uid"<<endl;

		}
	}*/
}
/*void details::displaymap()
{
	cout<<"contents of map"<<endl;
	for(auto &it : map1)
	{
		cout<<it.first<<" "<<it.second<<endl;
	}
}*/


	/*
	int lines=0;
	string line;
	string usr(user);
	fs.open("registered.txt",ios::in);
	if(fs.is_open())
	{
		while(getline(fs,line))
		{
			lines++;		
			if(line.find(usr,0)!=string::npos)
			{
				cout<<usr<<" exists "<<endl;
		
			}
		}
	}
	fs.close();*/
//create fd sets
void Server::createfds()
{
	readfds = master;
	max_sd = serverfd;
	//clear the sock set fds
	FD_ZERO(&readfds);
	FD_SET(serverfd,&readfds);
	max_sd = serverfd;
}
//check the number of clients connected and the maximum sockets created
void Server::countclient()		//details &d1)
{
	for(int i=0;i<max_clients;i++)
	{
		sd = client_sock[i];
		///if valid socket desc... then add to readfds lists
		if(sd > 0)
			FD_SET(sd,&readfds);
		//highest fds number, need it for the select fucntion
		if(sd > max_sd)
			max_sd = sd;
	}
}
/*void details::getdetails(details d1)
{
	cout<<"UserID: "<<uid<<endl;
	cout<<"password"<<password<<endl;
}*/
//check if the fd is set
void Server::checkfdset()
{
	details d1;
	//details d2;
	if(FD_ISSET(serverfd, &readfds))
	{		
		int newSockfd = acceptclient(serverfd);		
		//char user[MAX_BUF];
		//writeData1(newSockfd,buff );
		if(recv(newSockfd,&d1,sizeof(details),0)<0)
		{
			perror("recieve error");
		}
		cout<<"received obj"<<endl;
		d1.getdetails();
	//	d1.handleusers(d1);
		d1.validate(d1);
	//	d1.displaymap();
	//	cout<<d1.getUID()<<endl;
	//	cout<<d1.getPassword()<<endl;
		//d2=d2.getdetails(d1);
		memset(buff,0,MAX_BUF);
		for(int i=0;i<max_clients;i++)
		{
			if(client_sock[i] == 0)
			{
				client_sock[i] = newSockfd;
				cout<<"Adding the client sockfds to the list"<<endl;
				vs_csock.push_back(newSockfd);
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
//	struct sockaddr_in* addressInternet;
	struct sockaddr_in address = getClientAddr();
	getpeername(sd,(struct sockaddr*)&address, &len);						
	cout<<"Client disconnected with IP: "<<inet_ntoa(address.sin_addr);
	cout<<" and with port number: "<<ntohs(address.sin_port)<<endl;
	cout<<"Closing Socket with port  "<<ntohs(address.sin_port)<<endl;
	close(sd);
	client_sock[i] = 0;
}
//broadcast the message sent by one client to all the active clients
void Server::broadcast_msg()
{
	for(int i=0;(i<vs_csock.size())&&(client_sock[i] !=0 );i++)
	{
		int sock = client_sock[i];
		if(sock != sd && sock != serverfd && sock !=0)
		{
			char tbuff[MAX_BUF] = {'\0',};
			strcpy(tbuff, "Socket # ");
			string temp_str=to_string(sd); 
			strcat(tbuff,temp_str.c_str());
			strcat(tbuff,": ");
			strcat(tbuff,buff);
			strcat(tbuff,"\r\n");							
			write(sock, tbuff, strlen(tbuff));

		}
	}
}		
//checks if the socket is ready for reading or writing
void Server :: serv_select(int port,string ip)
{
	for(int i=0;i<max_clients;i++)
	{
		client_sock[i] = 0;	
	}
	serverfd =getServSockfd();
	FD_ZERO(&master);
	while(true)
	{	
		//createfds	
		createfds();
		// for adding new client scket to set
		countclient();
		//check if the socket is ready
		int socketCount = select(max_sd+1,&readfds,NULL,NULL,NULL);
		
		if((socketCount <0) && (errno != EINTR))
		{
			cout<<"select error"<<endl;
		}
		//check if fds are set
		checkfdset();	
		for(int i=0;i<max_clients;i++)
		{
			sd  = client_sock[i];
			if(FD_ISSET (sd, &readfds))
			{
				memset(buff,0,MAX_BUF);
				if((readVal = read(sd, buff,MAX_BUF)) == 0)
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
					broadcast_msg();
					memset(buff,0,MAX_BUF);
				}
			}
		}
	}// end of while loop
	
	servClose(getServSockfd());
}
