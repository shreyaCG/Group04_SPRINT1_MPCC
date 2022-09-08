#include "SockServer.h"
#include "details.h"
//take command line arguments for ip and port number
int main(int argc, char *argv[])
{
	try{
		if(argc<3){
			throw("Insufficient arguments\nUsage: <IP Address> <Port Number>");
		}
		else {
			Server s1;			//class object created
			int port=atoi(argv[2]);		//port number 
			string ip =argv[1];		//ip address
			s1.create_socket();		//socket creation
			s1.bind_listen();		//bind listen to the client
			s1.serv_select(port,ip);	//check if the sockets are ready to read
			//file.close();
		}
	}
	catch(const char* str) {
		cout<<"Exception: "<<str<<endl;
	}
	return 0;
}
