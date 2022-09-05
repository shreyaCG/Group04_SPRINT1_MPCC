#include "sock_client.h"

myClient::myClient()
{
}
void myClient::create_socket(string ip_addr, int port_no)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0){
		perror("[-] SOCKET ERROR");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] CLIENT SOCKET IS CREATED"<<endl;
	
	server_length = sizeof (server_addr);
	memset(&server_addr, '\0', server_length);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_no);
	server_addr.sin_addr.s_addr = inet_addr((const char*)ip_addr.c_str());
}
void myClient::connect_client()
{
	server_length = sizeof(server_addr);
	client_connect = connect(sockfd, (struct sockaddr*)&server_addr, server_length);
	if(client_connect<0){
		perror("[-] CONNECT ERROR");
		exit(EXIT_FAILURE);
	}
	cout<<"[+] CLIENT CONNECTED TO THE SERVER"<<endl;
}    
void myClient::send_message()
{	
		while(1){

		char buf[BSIZE] = {'\0',};
		read(sockfd, buf, BSIZE);
		cout<<buf<<endl;


	memset(buf, 0 , sizeof(buf));
	cout<<"Enter a message: ";
	fgets(buf, sizeof(buf),stdin);
	write(sockfd, buf, strlen(buf));
	cout<<"Data sent "<<buf<<endl;
		}
	close(sockfd);
}
/*	strcpy(client_buf, "Hello");
	write(sockfd, client_buf, sizeof(client_buf));
	cout<<"From server: ";
	read(sockfd, client_buf, sizeof(client_buf));
	cout<<client_buf;
	
	//recv(sockfd,client_buf, sizeof(client_addr),0 );
	//	cout<<client_buf<<endl;
}*/
myClient::~myClient()
{
}
