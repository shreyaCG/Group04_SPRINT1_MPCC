#include "sock_client.h"

int main(int argc, char *argv[])
{
	if(argc==1){
		cout<<"[-] ERROR: NO INPUT"<<endl;
		exit(EXIT_FAILURE);
	}
	if(argv[1] == NULL){
		cout<<"[-] ERROR: PROVIDE IP ADDRESS"<<endl;
		exit(EXIT_FAILURE);
	}
	if(argv[2] == NULL){
		cout<<"[-] ERROR: PROVIDE PORT NUMBER"<<endl;
		exit(EXIT_FAILURE);
	}
	myClient mc;
	string ip = argv[1];
	int port = atoi(argv[2]);

	mc.create_socket(ip,port);
	mc.connect_client();
	return 0;
}
