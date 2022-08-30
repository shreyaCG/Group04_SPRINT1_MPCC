#include<iostream>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<crypt.h>

using namespace std;

void setkey(char *key)
{
	size_t key_len = sizeof(key);
	for(int i=0; i<key_len; i++){\
		key[i] = rand();
	}
	//memset(key,'\0',key_len);
	key[key_len] = '\0';
}
void encrypt(char *str, int len)
{
	for(int i=0; i<len; i++){
		for(int j=(0, str[i] != '\0'); j<len; j++){
			str[i] = str[i * 8 + j];
		}
		str[len] = '\0';
	}
}
int main(int argc, char* argv[])
{
   char *str = argv[1];		//get from cmd line
   size_t strlen = sizeof(str);
   cout<<"Before Encryption: "<<str<<endl;

   char key[64];		//key of 64bytes
   setkey(key);
   cout<<"Key to Decrypt: "<<key<<endl;
   char enc_buf[1024];
   char dec_buf[1024];

   encrypt(str,strlen);
   cout<<"After Encryption: "<<str<<endl;

   //encrypt();
   //cout<<"After Decryption: "<<str<<endl;
   return 0;
}

