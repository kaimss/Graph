#include"linkedWDigraph.h"
#include<iostream>
#include<vector>
using namespace std;
#define v 6
template<class T>
int com(T a, vector<T> b)
{
	for (int i = 0; i < b.size(); i++)
	{
		if (b[i] == a)
			return i;
	}
	return -1;
}
int main()
{
	/*//实验一
	try {
		
		linkedWDigraph<int> g(v);
		g.insertEdge(new edge<int>(1, 2, 1));
		g.insertEdge(new edge<int>(2, 6, 1));
		g.insertEdge(new edge<int>(6, 1, 1));
		g.insertEdge(new edge<int>(3, 2, 1));
		g.insertEdge(new edge<int>(3, 4, 1));
		g.insertEdge(new edge<int>(4, 5, 1));
		g.insertEdge(new edge<int>(5, 6, 1));
		g.insertEdge(new edge<int>(5, 3, 1));
		cout << "Number of Vertices = " << g.numberOfVertices() << endl;
		cout << endl;
		cout <<"before:\n" << g << endl;

		vector<vertex> tmp(v + 1);
		for (int i = 1; i <= v; i++)
		{
			g.dfs1(i, tmp);
		}
		cout << "after:\n" << g << endl;
		for (int i = 1; i <= v; i++)
		{
			cout << "节点" << i << "\n" << tmp[i] << endl;
		}
	}
	catch (const char* str)
	{
		cout << str << endl;
	}*/
	
	//实验二
	try {

		linkedWDigraph<int> g(v);
		g.insertEdge(new edge<int>(1, 2, 1));
		g.insertEdge(new edge<int>(1, 4, 1));
		g.insertEdge(new edge<int>(2, 4, 1));
		g.insertEdge(new edge<int>(2, 3, 1));
		g.insertEdge(new edge<int>(3, 5, 1));
		g.insertEdge(new edge<int>(5, 6, 1));

		g.insertEdge(new edge<int>(2, 1, 1));
		g.insertEdge(new edge<int>(4, 1, 1));
		g.insertEdge(new edge<int>(4, 2, 1));
		g.insertEdge(new edge<int>(3, 2, 1));
		g.insertEdge(new edge<int>(5, 3, 1));
		g.insertEdge(new edge<int>(6, 5, 1));

		//cout << "Number of Vertices = " << g.numberOfVertices() << endl;
		//cout << endl;
		cout << "图的邻接链表表示:\n" << g << endl;

		vector<vertex> tmp(v + 1);
		g.dfs2(1, tmp);
		cout << endl;

		//cout << "after:\n" << g << endl;
		/*for (int i = 1; i <= v; i++)
		{
			cout << "节点" << i << "\n" << tmp[i] << endl;
		}*/
	}
	catch (const char* str)
	{
		cout << str << endl;
	}

	//实验三
	//try {

	//	linkedWDigraph<int> g(v);
	//	g.insertEdge(new edge<int>(1, 2, 1));
	//	g.insertEdge(new edge<int>(1, 4, 5));
	//	g.insertEdge(new edge<int>(1, 5, 3));
	//	g.insertEdge(new edge<int>(2, 3, 2));
	//	g.insertEdge(new edge<int>(3, 5, 4));
	//	g.insertEdge(new edge<int>(3, 6, 5));
	//	g.insertEdge(new edge<int>(4, 5, 1));
	//	g.insertEdge(new edge<int>(5, 6, 7));

	//	g.insertEdge(new edge<int>(2, 1, 1));
	//	g.insertEdge(new edge<int>(4, 1, 5));
	//	g.insertEdge(new edge<int>(5, 1, 3));
	//	g.insertEdge(new edge<int>(3, 2, 2));
	//	g.insertEdge(new edge<int>(5, 3, 4));
	//	g.insertEdge(new edge<int>(6, 3, 5));
	//	g.insertEdge(new edge<int>(5, 4, 1));
	//	g.insertEdge(new edge<int>(6, 5, 7));

	//	cout << "Number of Vertices = " << g.numberOfVertices() << endl;
	//	cout << endl;
	//	cout << "before:\n" << g << endl;

	//	linkedWDigraph<int> result(v);

	//	g.particalExchange(result);
	//	
	//	cout << "after:\n" << result << endl;
	//	
	//}
	//catch (const char* str)
	//{
	//	cout << str << endl;
	//}


	//实验四
	//try {

	//	linkedWDigraph<int> g(v);
	//	//g.insertEdge(new edge<int>(1, 4, 4));
	//	//g.insertEdge(new edge<int>(2, 5, 4));
	//	//g.insertEdge(new edge<int>(2, 3, 2));
	//	//g.insertEdge(new edge<int>(3, 6, 3));
	//	//g.insertEdge(new edge<int>(4, 5, 2));
	//	//g.insertEdge(new edge<int>(5, 6, 5));
	//	//g.insertEdge(new edge<int>(6, 2, -9));
	//	g.insertEdge(new edge<int>(1, 2, 5));
	//	g.insertEdge(new edge<int>(2, 4, 4));
	//	g.insertEdge(new edge<int>(1, 6, -7));
	//	g.insertEdge(new edge<int>(3, 5, 2));
	//	g.insertEdge(new edge<int>(5, 1, 2));
	//	g.insertEdge(new edge<int>(6, 3, 2));
	//	g.insertEdge(new edge<int>(6, 5, 5));
	//	cout << "Number of Vertices = " << g.numberOfVertices() << endl;
	//	cout << endl;
	//	cout << "before:\n" << g << endl;

	//	g.negCircle();		


	//}
	//catch (const char* str)
	//{
	//	cout << str << endl;
	//}


	//实验五
	//try {
	//	//v=5
	//	linkedWDigraph<int> g(v);

	//	g.insertEdge(new edge<int>(1, 2, 2)); g.insertEdge(new edge<int>(1, 3, 5)); g.insertEdge(new edge<int>(1, 4, 2));
	//	g.insertEdge(new edge<int>(1, 5, 5)); 
	//	g.insertEdge(new edge<int>(2, 3, 4)); g.insertEdge(new edge<int>(2, 4, 5)); g.insertEdge(new edge<int>(2, 5, 1));
	//	g.insertEdge(new edge<int>(3, 4, 1)); g.insertEdge(new edge<int>(3, 5, 2)); 
	//	g.insertEdge(new edge<int>(4, 5, 5));


	//	g.insertEdge(new edge<int>(2, 1, 2)); g.insertEdge(new edge<int>(3, 1, 5)); g.insertEdge(new edge<int>(4, 1, 2));
	//	g.insertEdge(new edge<int>(5, 1, 5));
	//	g.insertEdge(new edge<int>(3, 2, 4)); g.insertEdge(new edge<int>(4, 2, 5)); g.insertEdge(new edge<int>(5, 2, 1));
	//	g.insertEdge(new edge<int>(4, 3, 1)); g.insertEdge(new edge<int>(5, 3, 2));
	//	g.insertEdge(new edge<int>(5, 4, 5));

	//	cout << "Number of Vertices = " << g.numberOfVertices() << endl;
	//	cout << endl;
	//	cout << "before:\n" << g << endl;

	//	int arr[5] = { 1, 2, 3, 4, 5 };
	//	vector<int> vec(arr + 1, arr + 5);      //将arr数组的元素用于初始化vec向量
	//	vector<int> path(5, 0);
	//	cout <<"\n最终，长度为" << g.dynamic_TPS(1, 1, vec, path) << endl;
	//	cout << "路径为";
	//	
	//	for (int i = 0; i < path.size(); i++)
	//	{
	//		cout << path[i];
	//		if (i != path.size())
	//			cout << ",";
	//	}
	//	cout << endl;

	//}
	//catch (const char* str)
	//{
	//	cout << str << endl;
	//}
	return 0;
}