#include <ServerSocket.h>

int main(int argc, char *argv[])
{
	int csockfd, client_sock[30];
	
	int max_clients = 30;

	int serverfd, sd, max_sd;
	
	int readVal;

	vector <int> vs_csock;
	char buff[MAX_BUF];
	//create master socket
	fd_set master;
	// set of sock_desc...
	fd_set readfds;
	int socketCount=0;

	for(int i=0;i<max_clients;i++)
		client_sock[i] = 0;

	
	
	ServerSocket *S = new ServerSocket(atoi(argv[2]), argv[1]);
	
	S->servConn();
	serverfd = S->getServSockfd();
	FD_ZERO(&master);
	

	while(true)
	{
		
		readfds = master;
		max_sd = serverfd;
		//clear the sock set fds
		FD_ZERO(&readfds);

		//add master_sock to be monitored
		FD_SET(serverfd,&readfds);

		max_sd = serverfd;

		// for adding childs socket to set
		for(int i=0;i<max_clients;i++)
		{
			sd = client_sock[i];

			//if valid socket desc... then add to readfds lists
			if(sd > 0)
				FD_SET(sd,&readfds);
			//highest fds number, need it for the select fucntion
			if(sd > max_sd)
				max_sd = sd;

		}




		int socketCount = select(max_sd+1,&readfds,NULL,NULL,NULL);
		
		if((socketCount <0) && (errno != EINTR))
		{
			cout<<"select error"<<endl;
		}
		if(FD_ISSET(serverfd, &readfds)){
			
			int newSockfd = S->servAccept(serverfd);
			

			writeData1(newSockfd, buff);

			cout<<"Sent the Welcome Message to the client"<<endl;
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

		for(int i=0;i<max_clients;i++)
		{
			sd  = client_sock[i];
			if(FD_ISSET (sd, &readfds))
			{
				memset(buff,0,MAX_BUF);
				if((readVal = read(sd, buff,MAX_BUF)) == 0)
				{
					socklen_t len = sizeof(S->getClientAddr());
			        uint16_t port;
			        struct sockaddr_in* addressInternet;
			        struct sockaddr_in address = S->getClientAddr();
					getpeername(sd,(struct sockaddr*)&address, &len);
						

					cout<<"Host disconnected with IP: "<<inet_ntoa(address.sin_addr);
					cout<<" and with PortNO: "<<ntohs(address.sin_port)<<endl;
					cout<<"Closing Socket: "<<sd<<endl;
					close(sd);
					client_sock[i] = 0;
					
					if(vs_csock.size()==1)
					{
							vs_csock.erase(vs_csock.begin());
					}
					else
						vs_csock.erase(vs_csock.begin()+i);
					//cout<<"Size: "<<vs_csock.size()<<endl;
					
				}
				else
				{
					
					for(int i=0;(i<vs_csock.size())&&(client_sock[i] !=0 );i++)
					{
						int outSock = client_sock[i];
						//cout<<"Client: "<<outSock<<endl;
						if(outSock != sd && outSock != serverfd && outSock !=0)
						{
							//ostringstream ss;
							//ss << "Socket # "<<sd<<": "<<buff<<"\r\n";
							char tbuff[MAX_BUF] = {'\0',};
							strcpy(tbuff, "Socket # ");
							string temp_str=to_string(sd); 
							strcat(tbuff,temp_str.c_str());
							strcat(tbuff,": ");
							strcat(tbuff,buff);
							strcat(tbuff,"\r\n");
							
							//string sbuff = ss.str();
							//strcpy(sbuff.c_str(),tbuff);
							write(outSock, tbuff, strlen(tbuff));

						}
					}
					memset(buff,0,MAX_BUF);
					// buff[readVal] = '\0';
					// send(sd, buff, strlen(buff),0);
				}
			}
		}

		

		
		
	}// end of while loop

	
	S->servClose(S->getServSockfd());
	return 0;
}


