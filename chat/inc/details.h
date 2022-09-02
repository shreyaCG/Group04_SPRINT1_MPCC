#pragma once
#include<iostream>
#include<cstring>
#include<map>
#include<list>
#include<fstream>
using namespace std;
class details
{
	private:
		char uid[20];
		char password[20];
		map<string,string>map1;
		list<string>list1;
	public:
		void setdetails();
		char* getUID(){ return uid;}
		char* getPassword(){ return password;}
		void getdetails(){
		       	cout<<uid<<endl;
			cout<<password<<endl;}
		void handleusers(details &);
		void displaymap();
		void setpass();
		void validate(details &);		
};

