#include"linkedWDigraph.h"
#include<iostream>
#include<vector>
using namespace std;
#define v 6
int main()
{
	/*try {
		
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
			cout << "�ڵ�" << i << "\n" << tmp[i] << endl;
		}
	}
	catch (const char* str)
	{
		cout << str << endl;
	}*/
	
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

		cout << "Number of Vertices = " << g.numberOfVertices() << endl;
		cout << endl;
		cout << "before:\n" << g << endl;

		vector<vertex> tmp(v + 1);
		g.dfs2(1, tmp);

		cout << "after:\n" << g << endl;
		for (int i = 1; i <= v; i++)
		{
			cout << "�ڵ�" << i << "\n" << tmp[i] << endl;
		}
	}
	catch (const char* str)
	{
		cout << str << endl;
	}


	return 0;
}