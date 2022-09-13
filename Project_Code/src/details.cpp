#include<details.h>
/*This function is used to get the user ID and Password
 from the client for registration and login*/
void details::setdetails()
{
	cout<<"Enter UserID: ";
	cin>>uid;
	cout<<"Enter Password: ";
	cin>>password;
}
/*This function is used to store the registered users
 data into a file*/
void details::database(char* data)
{
	fstream file;
	file.open("data/registered.txt", ios::in | ios::app);
	file<<data<<endl;
	file.close();
}
