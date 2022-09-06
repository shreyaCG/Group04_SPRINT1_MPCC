#include<iostream>
#include<fstream>
#include<ctime>
#include<cstring>
using namespace std;
int main()
{
	fstream fs;
	//time_t tym = time(0);
	//char* date = ctime(&tym);
	//cout<<date<<endl;
	
	strcat(date,".log");
        
	fs.open(date, ios::in | ios::out | ios::app);
	fs<<"helllllllo"<<endl;
	fs.close();
}	
