#pragma once
#include<iostream>
#include<cstring>
#include<string.h>
#include<string>
#include<ctype.h>
//#include<cstring>
#include<bits/stdc++.h>
using namespace std;
class details
{
	private:
		char uid[20];
		char password[20];
	public:
		void* setdetails();
		char* getUID(){ return uid;}
		char* getPassword(){ return password;}
		void getdetails(){
			cout<<uid<<endl;
			cout<<password<<endl;}
		char* validate(details *d);
		void* choose(int);
		void* registeruser();
		void* loginuser();
		void database(details *);
		std::string tostring() {
			ostringstream ss;
			ss << this->getUID()<<"|"<< this->getPassword();
			return ss.str();
		}
};
