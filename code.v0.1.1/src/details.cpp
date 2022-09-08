#include<details.h>
void userdata::setData()
{
	cout<<"Enter User-ID: ";
	cin>>uid;
	cout<<"Enter Password: ";
	cin.getline(pwd,20);
}
void* details::registeruser()
{
	details *d2=new details;
	d2->setData();
	return d2;
}
void* details::loginuser()
{
	details *d3=new details;
	d3->setData();
	return d3;
}
void details:: choose(int option)
{
	switch(option)
	{
		case 1:
			cout<<"Enter credentials to register"<<endl;
			buff=registeruser();		
			break;
		case 2:
			cout<<"Enter the login credentials"<<endl;
			buff=loginuser();										
	}
	return buff;

}
void details::database(details *d1)
{
	fstream fs;
	fs.open("registered.txt",ios::in | ios::app);
	size_t size=sizeof(details);
	fs.write(reinterpret_cast<const char*>(d1),size);
	fs.close();
}

