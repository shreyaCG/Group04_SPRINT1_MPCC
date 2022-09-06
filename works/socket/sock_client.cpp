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
void myClient::client_login()
{
	cout<<"[+] REGISTER TO THE SERVER"<<endl;
	
	string str_user;
	cout<<"[+] ENTER USERNAME: ";
	getline(cin,str_user);

	char send_user[BSIZE];
	strcpy(send_username,str.c_str());
	send(sockfd, send_user, BSIZE,0);
	
	string str_pass;
	cout<<"[+] ENTER PASSWORD: ";
	getline(cin,str_pass);

	char send_pass[BSIZE];
	strcpy(send_pass,str.c_str());
	send(sockfd, send_pass, BSIZE,0);
	

	//char buf[BSIZE];
	//read(sockfd, buf, BSIZE);
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
	//while(1){
		client_login();
	//}
}
myClient::~myClient()
{
}
