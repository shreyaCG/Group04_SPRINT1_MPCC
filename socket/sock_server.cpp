#include "sock_server.h"

myServer::myServer()
{
}
void myServer::create_socket(string ip_addr, int port_no)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0){
		perror("[-] SOCKET ERROR");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] SERVER SOCKET IS CREATED"<<endl;
	
	server_length = sizeof(server_addr);
	memset(&server_addr, '\0', server_length);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_no);
	server_addr.sin_addr.s_addr = inet_addr((const char*)ip_addr.c_str());
}
void myServer::bind_server()
{
	server_length = sizeof(server_addr);
	server_bind = bind(sockfd, (struct sockaddr*)&server_addr, server_length);
	if(server_bind<0){
		perror("[-] BIND ERROR");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] SERVER IS BINDED TO PORT"<<endl;

	server_listen = listen(sockfd, MAXCONN);
	if(server_listen<0){
		perror("[-] LISTEN ERROR");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] SERVER IS LISTENING TO THE CLIENTS..."<<endl;
}
void myServer::receive_message()
{
}
void myServer::send_message()
{
}
void myServer::accept_client()
{
	client_length = sizeof(client_addr);
//	int i, sd, client_socket[30];

	fd_set master;
	
//	for(;;)
//	{
//	                     
	//	int ready_fd = select(MAX, &master, nullptr, nullptr, nullptr);
	//	if(FD_ISSET(sockfd, &master)){
			while(1){
				
				FD_ZERO(&master);
				FD_SET(sockfd , &master);
				
        			MAX = sockfd;
				//FD_SET(server_listen, &master);
				
			/*	for(i=0;i<max_clients;i++)
				{
					sd = client_socket[i];
					if(sd>0){
						FD_SET(sd, &master);
					}
						if(sd>MAX){
							MAX = sd;
						}
					
				}*/
				int activity = select(MAX +1 , &master, NULL, NULL, NULL);
				if(activity<0){
					perror("SELECT ERROR");
					exit(EXIT_FAILURE);
				}
				if(FD_ISSET(sockfd, &master)){
					
				if((new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_length))<0){
					perror("ACCEPT ERROR");
					exit(EXIT_FAILURE);
				}
				char message[BSIZE] = "WELCOME";
				write(new_sockfd, message, strlen(message));
				cout<<"Welcome sent"<<endl;
				//bzero(message, strlen(message));

                          
                          /*     for(i=0;i<max_clients;i++){
					if(client_socket[i]==0){
						client_socket[i]=new_socket;
						cout<<"Adding sockets"<<i<<endl;
						break;
					}
				}*/
				
			       
                               
				      
				       
			       }
			       char buf[BSIZE] ={'\0',};
			      // memset(buf,0,sizeof(buf));
			       read(new_sockfd, buf, BSIZE);
			       cout<<"client"<<ntohs(client_addr.sin_port)<<"sent"<<buf<<endl;
			       
			      // close(new_sockfd);
				}
			}

			
		/*	for(i=0;i<max_clients;i++){
				sd = client_socket[i];
				if(FD_ISSET(sd, &master)){
					char cli[BSIZE] = {'\0',};
					write(sd, cli,sizeof(cli));
				}
			}*/
		













				/*cout<<"Message from client";
				read(new_sockfd, client_buf, sizeof(client_buf));
				cout<<client_buf<<endl;
				char* message = "Hello";
				write(new_sockfd, (const char* )message, sizeof(client_buf));*/

	/*	if((select(MAX, &copy, nullptr, nullptr, nullptr))<0){
			perror("[-] SELECT ERROR");
			exit(EXIT_FAILURE);
		}
		for(int i=0;i<MAX;i++){
			if(FD_ISSET(i, &copy)){
				if(i == server_listen){
					new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_length);
					//cout<<"[+] SERVER ACCEPTED THE CLIENT"<<endl;
					if(new_sockfd<0){
						perror("[-] ACCEPT ERROR");
						exit(EXIT_FAILURE);
					}
					
					FD_SET(new_sockfd, &master);
					string welcome = "WELCOME";
					send (new_sockfd,welcome.c_str(), welcome.size() +1, 0);
				}
				else{
					FD_CLR(i, &copy);
					close(sockfd);
		if((select(MAX, &copy, nullptr, nullptr, nullptr))<0){
			perror("[-] SELECT ERROR");
			exit(EXIT_FAILURE);
		}
		for(int i=0;i<MAX;i++){
			if(FD_ISSET(i, &copy)){
				if(i == server_listen){
					new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_length);
					//cout<<"[+] SERVER ACCEPTED THE CLIENT"<<endl;
					if(new_sockfd<0){
						perror("[-] ACCEPT ERROR");
						exit(EXIT_FAILURE);
					}
					
					FD_SET(new_sockfd, &master);
					string welcome = "WELCOME";
					send (new_sockfd,welcome.c_str(), welcome.size() +1, 0);
				}
				else{
					FD_CLR(i, &copy);
					close(sockfd);
			}
			close(new_sockfd);
		}
	}

}	*/


myServer::~myServer()
{
}
