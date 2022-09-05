#include<details.h>
void* details::setdetails()
{
	cout<<"Enter UserID: ";
	cin>>uid;
	cout<<"Enter Password: ";
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
			buff=registeruser();													      break;
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
/*char* details::validate(details *d1)
{
	int flag=0;
//	int res=toupper((unsigned char)(d1->getUID()));
	if(isdigit(res)==0)
	{
		flag=1;
	}
		if(flag==1)
		{
			cout<<"validation"<<endl;
			cout<<d1->getUID();
		}
		else
		{
			cout<<"invalid"<<endl;
		}
}*/

















