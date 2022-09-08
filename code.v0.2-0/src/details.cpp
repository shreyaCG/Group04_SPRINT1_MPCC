#include<details.h>
void details::setdetails()
{
	cout<<"Enter UserID: ";
	cin>>uid;
	cout<<"Enter Password: ";
	cin>>password;
}
/*void details::registeruser()
{
	setdetails();
}
void details::loginuser()
{
	setdetails();
}
void details:: choose(int option)
{
	switch(option)
	{
		case 1:
			cout<<"Enter credentials to register"<<endl;
			registeruser();		
			break;
		case 2:
			cout<<"Enter the login credentials"<<endl;
			loginuser();
			break;
		default:
			cout<<"Exiting the Session"<<endl;
			exit(0);
	}

}*/
void details::tokenid(string data)
{
	string middle;
	stringstream check(data);
	while(getline(check,middle,'|'))
	{
		vstring.push_back(middle);
	}
	for(int i=0;i<vstring.size();i++)
	{
		cout<<vstring[i];
	}
}
void details::database(char* data)
{
	fstream file;
	file.open("data/registered.txt", ios::in | ios::app);
	file<<data<<endl;
	file.close();
}
