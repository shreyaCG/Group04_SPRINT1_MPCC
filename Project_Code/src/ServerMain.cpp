#include <Sock_Server.h>
#include<details.h>
//take command line arguments for ip and port number
int main(int argc, char *argv[])
{
	try{
		if(argc<3){
			throw("Insufficient arguments\nUsage: <IP Address> <Port Number>");
		}
		else {
			
			Server *s1=new Server(atoi(argv[2]),argv[1]);
			s1->create_socket();		//socket creation
			s1->bind_listen();		//bind listen to the client
			s1->serv_select();	//check if the sockets are ready to read
		}
	}
	catch(const char* str) {
		cout<<"Exception: "<<str<<endl;
	}
	return 0;
}
