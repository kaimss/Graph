#include"linkedWDigraph.h"
#include<iostream>
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


		//寻找出度最大的点
		int vv = 1;
		int max = g.outDegree(vv);
		for (int i = 1; i <= v; i++)
		{
			int tm = g.outDegree(i);
			if (tm > max)
			{
				vv = i;
				max = tm;
			}
		}


		linkedWDigraph<int> gt(v);
		int d[v + 1] = { 0 };
		int pi[v + 1] = { 0 };

		//找到出度最大的点
		g.bfs(vv, d, pi, 1);
		for (int m = 1; m <= v; m++)
		{
			if (pi[m] != 0)
			{
				gt.insertEdge(new edge<int>(pi[m], m, 1));
			}
		}
		for (int n = 1; n <= v; n++)
			pi[n] = 0;

		//操作剩余未到达的点
		for (int i = 1; i <= v; i++)
		{
			g.bfs(i, d, pi, 1);
			for (int m = 1; m <= v; m++)
			{
				if (pi[m] != 0)
				{
					gt.insertEdge(new edge<int>(pi[m], m, 1));
				}
			}
			for (int n = 1; n <= v; n++)
				pi[n] = 0;
			
		}
		cout << "after:\n" << gt << endl;


	}
	catch (const char* str)
	{
		cout << str << endl;
	}
	



	return 0;
}