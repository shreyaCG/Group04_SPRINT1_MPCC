#pragma once
#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<ctype.h>
#include<bits/stdc++.h>

using namespace std;

class details
{
	private:
		char uid[20];
		char password[20];
	public:
		void setdetails();
		void database(char*);
		void setUID(char* s){ strcpy(uid,s); }
		void setPassword(char* s) { strcpy(password,s); }
		char* getUID(){ return uid;}
		char* getPassword(){ return password;}
		void getdetails() { cout<<uid<<'\n'<<password<<endl; }	
		string toString(){
		        ostringstream ss;	
			ss<<this->getUID()<<"|"<<this->getPassword();
			return ss.str();
		}
};
