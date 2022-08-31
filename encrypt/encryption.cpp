#include <bits/stdc++.h>
using namespace std;
string encryption(string s)
{
	int l = s.length();
	int b = ceil(sqrt(l));
        int a = floor(sqrt(l));
        string encrypted;
	if (b * a < l) {
	if (min(b, a) == b) {
		b = b + 1;
	}
	else {
		a = a + 1;
       	}
	}
	 char arr[a][b];
	 memset(arr, ' ', sizeof(arr));
	 int k = 0;
	 for (int j = 0; j < a; j++) {
		 for (int i = 0; i < b; i++) {
			 if (k < l){
				 arr[j][i] = s[k];
		          }
			  k++;
		 }
	 }
	 for (int j = 0; j < b; j++) {
		for (int i = 0; i < a; i++) {
	           encrypted = encrypted +
		          arr[i][j];
		 }
	 }
	 return encrypted;
}

string decryption(string s){
	int l = s.length();
	int b = ceil(sqrt(l));
	int a = floor(sqrt(l));
	string decrypted;

	char arr[a][b];
	memset(arr, ' ', sizeof(arr));
	int k = 0;
	for (int j = 0; j < b; j++) {
		for (int i = 0; i < a; i++) {
		    if (k < l){
			arr[j][i] = s[k];
		    }
			k++;
			}
	}
	for (int j = 0; j < a; j++) {
	     for (int i = 0; i < b; i++) {
		   decrypted = decrypted +
		          arr[i][j];
		     }
	     }
		return decrypted;
}

int main(int argc, char *argv[])
{
	    string s = argv[1];
	    string encrypted;
            string decrypted;
	    encrypted = encryption(s);
	    cout <<"Encrypted message"<< encrypted << endl;
	    decrypted = decryption(encrypted);
	    cout << "decrypted"<<decrypted;
	    return 0;
}

