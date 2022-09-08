#pragma once

#include<iostream>
#include<cstring>
#include<ctype.h>
#include<bits/stdc++.h>

using namespace std;

class details
{
	private:
		int user_id;
		char password[20];
	public:
		details(int uid, char* pwd){ user_id = uid; strcpy(password,pwd); }
		void setData();
		int getUID(){ return user_id; }
		char* getPassword(){ return password; }
		void getdetails(){ cout<<user_id<<'\n'<<password<<endl; }
		void* choose(int);
		void* registeruser();
		void* loginuser();
		void database();


		string toString() {
			ostringstream ss;
			ss<<this->getUID()<<':'<<this->getPassword();
			return ss.str();
		}
};
