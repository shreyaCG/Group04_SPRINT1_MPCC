#include"Serv_Client.h"

int main(int argc, char* argv[])
{
	 mysoc s1;
	 string IP=argv[1];
	 int port=atoi(argv[2]);
	 s1.createsocket(port,IP);
	 cout<<"[+] Server socket created successfully"<<endl;
	 s1.server();
	 s1.serveraccept();
	 return 0;
}

