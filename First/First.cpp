#include<iostream>
using namespace std;
int main()
{
	int a = 4, b = 0;

	try //try�����ǿ��������쳣�����
	{
		if (b == 0)
			throw b; //�����쳣
		cout << " a / b = " << a/b << "\n";
	}
	catch (int e)
	{
		cout << "e = " << e << endl;
		cerr << "����Ϊ0\n"; //cerr���ᵽ��������� �����ڽ��������Ҳ����ʹ��
	}
	catch (const char *str)  
	{
		cout << str;
		cerr << "����Ϊ0\n"; //cerr���ᵽ��������� �����ڽ��������Ҳ����ʹ��
	}


	return 0;
}