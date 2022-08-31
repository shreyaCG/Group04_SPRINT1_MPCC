#include<iostream>
#include<thread>

using namespace std;

void threadFn()
{
	        cout<<"This is the first thread"<<endl;
}
int main()
{
	        thread t1(threadFn);

		t1.join();
		return 0;
}
