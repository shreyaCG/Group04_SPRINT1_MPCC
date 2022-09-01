#include"Serv_Client.h"
mysoc::mysoc()
{
}
void mysoc::createsocket(int port,string IP)
{
         sockfd = socket(AF_INET, SOCK_STREAM, 0);
         if(sockfd < 0)
	 {
		 perror("socket() error: ");
		 exit(EXIT_FAILURE);
	 }

       // cout<<"[+] Server socket created successfully"<<endl;

	memset(&server_addr,0,sizeof(server_addr));

        server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr((const char*)IP.c_str());
}
void mysoc::server()
{

	  rbind = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
          if(rbind < 0)
	  {
		 perror("bind() error: ");
		 exit(EXIT_FAILURE);
	  }
	  cout<<"[+]Bind to the port: "<<PORT<<endl;
	  if(listen(sockfd,5)<0)
	  {
                 perror("listen() error: ");
                 exit(EXIT_FAILURE);
	  }
	 cout<<"[+]Listening to the clients....."<<endl;
}
void mysoc::serveraccept()
{
	len = sizeof(client_addr);
	while(1){
		newSockfd=accept(sockfd, (struct sockaddr*)&client_addr, &len);
		if(newSockfd<0)
	        {
		     perror("accept() error: ");

		     exit(EXIT_FAILURE);
		}
		 cout<<"[+]Accepted the client....."<<ntohs(client_addr.sin_port)<<endl;
		 if(fork()==0){
		//	 while(1){
	        	 //read/write operations
	        	 char buff[MAXBUFF] = {'\0',};
			 strcpy(buff,"\n========Welcome to the Server-Client Program========\n");
			 write(newSockfd, buff, strlen(buff));
			 memset(buff,0, sizeof(buff));
			 read(newSockfd,buff, MAXBUFF);
	        	 cout<<"Client "<<ntohs(client_addr.sin_port)<<" Sent: "<<buff<<endl;
		/*	 if(strcmp(buff,"bye")==0)
			 {
			         break;
			 }*/
		//	 }//end while /read/write
		 }//close of fork if
	  close(newSockfd);
       }//end of while loop
}
void mysoc::clientconnect()
{
	  ret = connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	  if(ret < 0)
	  {
		 perror("connect() error: ");
		 exit(EXIT_FAILURE);
          }
         cout<<"[+]Client connect to the server"<<endl;
}
void mysoc::clientreadwrite(string str)
{
	char buffer[MAXBUFF] = {'\0',};
	read(sockfd,buffer, MAXBUFF);
	cout<<buffer<<endl;
	memset(buffer,0, sizeof(buffer));
        /*cout<<"Enter a message: ";
        fgets(buffer, sizeof(buffer), stdin);
	trim(buffer);*/
	strcpy(buffer,(const char*)str.c_str());
	/*for(int i=0;i<strlen(buffer);i++)
	{
		if(int(buffer[i]) == 10 )
		buffer[i] = '\0';
	}*/
	write(sockfd, buffer, strlen(buffer));

	cout<<"Data : \'"<<buffer<<"\' sent to server"<<endl;
	close(sockfd);
	/*if(strcmp(buffer,"bye")==0)
	{
	break;
	}*/

}
mysoc::~mysoc()
{
}






