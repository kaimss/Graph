#include"linkedWDigraph.h"
#include<iostream>
using namespace std;
int main()
{
	try {
		linkedWDigraph<int> a(-5);
	}
	catch (const char* str)
	{
		cout << str << endl;
	}
	



	return 0;
}