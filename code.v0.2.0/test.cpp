#include<iostream>
#include<sstream>
#include<fstream>
#include<cstring>
using namespace std;
class AB
{
	private:
		int id;
		char name[20];
		ostringstream ss;
	public:
		void setDetails();
		int getID() { return id; }
		char* getName(){ return name; }
		string toString(){
			ss<<getID()<<"|"<<getName();
			return ss.str();
		}
};

void AB::setDetails()
{	
	cout<<"Enter ID: ";
	cin>>id;
	cout<<"Enter Name: ";
	cin>>name;
}
/*int getID()
{
	return id;
}
char* getName()
{
	return name;
}*/
/*string toString()
{
	ss<<getID()<<"|"<<getName();
	//ss<<id<<"|"<<name;
	return ss.str();
}*/
int main()
{
	AB ab;
	ab.setDetails();

	string str = ab.toString();
	cout<<str<<endl;
	/*ofstream file;
	file.open("file.txt", ios::in | ios::app);
	file<<ss.str();*/
	return 0;
}

