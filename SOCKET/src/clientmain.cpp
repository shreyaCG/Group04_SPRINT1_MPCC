#include"Serv_Client.h"

int main(int argc, char *argv[])
{
	mysoc s;
	string IP=argv[1];
	int port=atoi(argv[2]);
	string str=argv[3];
	s.createsocket(port,IP);
	cout<<"[+]Client socket created successfully"<<endl;
	s.clientconnect();
	s.clientreadwrite(str);
}
