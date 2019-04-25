#include<iostream>
using namespace std;
int main()
{
	int a = 4, b = 0;

	try //try里面是可能引发异常代码块
	{
		if (b == 0)
			throw b; //引发异常
		cout << " a / b = " << a/b << "\n";
	}
	catch (int e)
	{
		cout << "e = " << e << endl;
		cerr << "除数为0\n"; //cerr不会到输出缓冲中 这样在紧急情况下也可以使用
	}
	catch (const char *str)  
	{
		cout << str;
		cerr << "除数为0\n"; //cerr不会到输出缓冲中 这样在紧急情况下也可以使用
	}


	return 0;
}