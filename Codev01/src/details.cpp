#include<details.h>
void* details::setdetails()
{
	cout<<"Enter UserID: "<<endl;
	cin>>uid;
	cout<<"Enter Password: "<<endl;
	cin>>password;
}
void* details::registeruser()
{
	details *d2=new details;
	d2->setdetails();
	return d2;
}
void* details::loginuser()
{
	details *d3=new details;
	d3->setdetails();
	return d3;
}
void* details:: choose(int option)
{
	void *buff;
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

