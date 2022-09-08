#pragma once
#include<iostream>
#include<cstring>
#include<string.h>
#include<string>
#include<ctype.h>
#include<bits/stdc++.h>
using namespace std;
class details
{
	private:
		char uid[20];
		char password[20];
	public:
		//details(char* usr_id, char* pass_word) { 
		//	strcpy(uid, usr_id), strcpy(password, pass_word); }
		void setdetails();
		void* registeruser();
		void* loginuser();
		char* getUID(){ return uid;}
		char* getPassword(){ return password;}
		void getdetails(){ cout<<uid<<'\n'<<password<<endl;}
		//char* validate(details *d);
		void* choose(int);
		void database(details *);
		string toString() {
			ostringstream ss;
			ss<<this->getUID()<<"|"<<this->getPassword();
                        return ss.str();
		}
};
