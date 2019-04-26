#include"linkedWDigraph.h"
#include<iostream>
#include<vector>
using namespace std;
#define v 6
int main()
{
	try {
		
		//linkedWDigraph<int> a(-5);
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



		linkedWDigraph<int> gt(v);
		int d[v + 1] = { 0 };
		int pi[v + 1] = { 0 };

		vector<vertex> tmp(v + 1);
		for (int i = 1; i <= v; i++)
		{
			g.dfs(i, tmp, 1);
		}
		cout << "after:\n" << g << endl;
		//int gross = 0;
		//while (gross < v)
		//{
		//	//寻找出度最大的点
		//	int vv = 1;
		//	int max = g.outDegree(vv);
		//	for (int i = 1; i <= v; i++)
		//	{
		//		if (d[i] == 0)
		//		{
		//			int tm = g.outDegree(i);
		//			if (tm > max)
		//			{
		//				vv = i;
		//				max = tm;
		//			}
		//		}

		//	}

		//	gross++;
		//	//对出度最大的点进行操作
		//	g.bfs(vv, d, pi, 1);
		//	for (int m = 1; m <= v; m++)
		//	{
		//		if (pi[m] != 0)
		//		{
		//			gt.insertEdge(new edge<int>(pi[m], m, 1));
		//			gross++;
		//		}
		//	}
		//	for (int n = 1; n <= v; n++)
		//		pi[n] = 0;
		//}
		//cout << "after:\n" << gt << endl;





	}
	catch (const char* str)
	{
		cout << str << endl;
	}
	



	return 0;
}