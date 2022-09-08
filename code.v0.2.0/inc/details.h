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
		vector<string> vstring;
		ostringstream ss;
	public:
		//details(char* usr_id, char* pass_word) { strcpy(uid, usr_id), strcpy(password, pass_word); }
		void setdetails();
		//void registeruser();
		//void loginuser();
		//void choose(int);
		void tokenid(string);
		void database();
		char* getUID(){ return uid;}
		char* getPassword(){ return password;}
		void getdetails() { cout<<uid<<'\n'<<password<<endl; }	
		string toString(){ 
			ss<<this->getUID()<<"|"<<this->getPassword();	//<<"|";
			return ss.str();
		}
};
