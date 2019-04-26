#pragma once
#include"chain.h"
#include"edge.h"
#include"arrayQueue.h"
#include"arrayStack.h"
#include<vector>
#include <sstream>
#include<iostream>
using namespace std;
struct vertex
{
	int label = 0;
	int color = 0;//0白色，1灰色，2黑色
	int pi = 0;
	int start = 0;
	int finish = 0;
	vertex(){}
	//vertex(int pi, int color) { this->pi = pi; this->color = color; }
};
template <class T>
struct wEdge
{// vertex and weight pair
	int vertex;
	T weight;
	int category;//0树边，1前向边，2后向边，3横向边

	wEdge(int theVertex = 0, T theWeight = 0)
	{
		vertex = theVertex; weight = theWeight;
	}
	operator int() const { return vertex; }

};
// overload <<
template <class T>
ostream& operator<<(ostream& out, const wEdge<T>& x)
{
	out << "(" << x.vertex << " " << x.weight << ") "; return out;
}
template <class T>
class linkedWDigraph
{
private:
	int n;                         // number of vertices
	int e;                         // number of edges
	chain<wEdge<T> > *aList;  // adjacency lists


	vector<vertex> temp;
	int label;
	int t = 1;
	void rDfs(int v)
	{// Recursive dfs method.
		//reach[v] = label;
		//temp[v].label = label;
		temp[v].color = 1;//置为灰色
		temp[v].start = t;
		myIterator *iv = iterator(v);
		int u;
		while ((u = iv->next()) != 0)
		{
			// visit an adjacent vertex of v
			if (temp[u].color == 0)//树边
			{
				cout << "(" << v << "," << u << ")是一条树边\n";
				//iv->set(u, 0);
				
				temp[u].label = 1;
				t++;
				rDfs(u);  // u is an unreached vertex
			}
			else if (temp[u].color == 1)//后向边
			{
				cout << "(" << v << "," << u << ")是一条后向边\n";
				//iv->set(u, 2);
				this->eraseEdge(v, u);
			}
			else if (temp[u].color == 2)//
			{
				if (temp[v].start > temp[u].start)//横向边
				{
					cout << "(" << v << "," << u << ")是一条横向边\n";
					//iv->set(u, 3);
				}
				else if (temp[v].start < temp[u].start)//前向边
				{
					cout << "(" << v << "," << u << ")是一条前向边\n";
					//iv->set(u, 2);
					
				}
			}
		}

				
		delete iv;
		temp[v].finish = t;
		temp[v].color = 2;//置为黑色
	}
public:
	linkedWDigraph(int numberOfVertices = 0)
	{// Constructor.
		if (numberOfVertices < 0)
			throw "number of vertices must be >= 0";
		n = numberOfVertices;
		e = 0;
		aList = new chain<wEdge<T> >[n + 1];
	}

	~linkedWDigraph() { delete[] aList; }
	int numberOfVertices() const { return n; }
	int numberOfEdges() const { return e; }
	

	bool existsEdge(int i, int j) const
	{// Return true iff (i,j) is an edge.
		if (i < 1 || j < 1 || i > n || j > n
			|| aList[i].indexOf(wEdge<T>(j)) == -1)
			return false;
		else
			return true;
	}

	void insertEdge(edge<T> *theEdge)
	{// Insert an edge.
		int v1 = theEdge->vertex1();
		int v2 = theEdge->vertex2();
		if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
		{
			ostringstream s;
			s << "(" << v1 << "," << v2
				<< ") is not a permissible edge";
			throw s.str();
		}

		if (aList[v1].indexOf(wEdge<T>(v2)) == -1)
		{// new edge
			aList[v1].insert(0, wEdge<T>(v2, theEdge->weight()));
			e++;
		}
	}

	void insertEdgeNoCheck(edge<T> *theEdge)
	{// Insert an edge. No validation checks performed.
		aList[theEdge->vertex1()].insert(0,
			wEdge<T>(theEdge->vertex2(), theEdge->weight()));
		e++;
	}


	void eraseEdge(int i, int j)
	{
		if (i >= 1 && j >= 1 && i <= n && j <= n)
		{
			wEdge<T> *v = aList[i].eraseElement(j);
			if (v != NULL)  // edge (i,j) did exist
				e--;
		}
	}

	void checkVertex(int theVertex) const
	{// Verify that i is a valid vertex.
		if (theVertex < 1 || theVertex > n)
		{
			ostringstream s;
			s << "no vertex " << theVertex;
			throw s.str();
		}
	}



	int outDegree(int theVertex) const
	{// Return out-degree of vertex theVertex.
		checkVertex(theVertex);
		return aList[theVertex].size();
	}

	int inDegree(int theVertex) const
	{
		checkVertex(theVertex);

		// count in-edges at vertex theVertex
		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (aList[j].indexOf(wEdge<T>(theVertex)) != -1)
				sum++;

		return sum;
	}




	// iterators to start and end of list
	class myIterator 
	{
	public:
		myIterator(chainNode<wEdge<T> > *theNode)
		{
			currentNode = theNode;
			firstNode = theNode;
		}

		~myIterator() {}

		void set(int u, int categroy)
		{
			chainNode<wEdge<T> > *cNode = firstNode;
			if (cNode == NULL)
				return;
			while (cNode->element.vertex != u)
			{
				cNode = cNode->next;
			}
			//cNode->element->category = category;

			
		}

		int next()
		{// Return next vertex if any. Return 0 if no next vertex.
		 // find next adjacent vertex
			if (currentNode == NULL)
				return 0;
			int nextVertex = currentNode->element.vertex;
			currentNode = currentNode->next;
			return nextVertex;
		}

		int next(T& theWeight)
		{// Return next vertex if any. Return 0 if no next vertex.
		 // Set theWeight = edge weight.
		 // find next adjacent vertex
			if (currentNode == NULL)
				return 0;
			int nextVertex = currentNode->element.vertex;
			theWeight = currentNode->element.weight;
			currentNode = currentNode->next;
			return nextVertex;
		}

	private:
		chainNode<wEdge<T> > *firstNode;
		chainNode<wEdge<T> > *currentNode;
	};

	myIterator* iterator(int theVertex)
	{// Return iterator for vertex theVertex.
		checkVertex(theVertex);
		return new myIterator(aList[theVertex].getfirstNode()); 
		
	}


	void output(ostream& out) const
	{// Output the adjacency matrix.
		for (int i = 1; i <= n; i++)
			out << i << ": " << aList[i] << endl;
	}

	// 广度优先搜索 
	void bfs(int v, int reach[], int processor[], int label)
	{// Breadth-first search. reach[i] is set to label for
	 // all vertices reachable from vertex v.
		arrayQueue<int> q(10);
		reach[v] = label;
		q.push(v);
		while (!q.empty())
		{
			// remove a labeled vertex from the queue
			int w = q.front();
			q.pop();


			
			// mark all unreached vertices adjacent from w
			myIterator *iw = iterator(w);
			//vertexIterator<T> *iw = iterator(w);
			int u;
			while ((u = iw->next()) != 0)
				// visit an adjacent vertex of w
				if (reach[u] == 0)
				{// u is an unreached vertex
					q.push(u);
					reach[u] = label; // mark reached
					processor[u] = w;
				}
			delete iw;
		}
	}
	//拓扑排序 
	bool topologicalOrder(int *theOrder)
	{// 返回false当且仅当有向图没有拓扑序列 
	 // 如果存在一个拓扑序列，将其赋给theOrder[0:n-1]
	 // such an order exists. 
	 // 确保这是一个有向图 

		int n = numberOfVertices();

		// 计算入度 
		int *inDegree = new int[n + 1];
		fill(inDegree + 1, inDegree + n + 1, 0);
		for (int i = 1; i <= n; i++)
		{// 顶点i的出边 
			myIterator *ii = iterator(i);
			//vertexIterator<T> *ii = iterator(i);
			int u;
			while ((u = ii->next()) != 0)
				// 访问顶点i的一个邻接点 
				inDegree[u]++;
		}

		// 把入度为0的顶点加入栈 
		arrayStack<int> stack;
		for (int i = 1; i <= n; i++)
			if (inDegree[i] == 0)
				stack.push(i);

		// 生成拓扑序列 
		int j = 0;  // 数组theOrder的索引 
		while (!stack.empty())
		{// 从栈中提取顶点 
			int nextVertex = stack.top();
			stack.pop();
			theOrder[j++] = nextVertex;
			// 更新入度
			myIterator  *iNextVertex = iterator(nextVertex);
			//vertexIterator<T> *iNextVertex = iterator(nextVertex);
			int u;
			while ((u = iNextVertex->next()) != 0)
			{// 访问顶点nextVertex的下一个邻接顶点 
				inDegree[u]--;
				if (inDegree[u] == 0)
					stack.push(u);
			}
		}
		return (j == n);
	}
	//深度优先搜索 
	void dfs(int v, vector<vertex> &temp, int label)
	{// Depth-first search. reach[i] is set to label for all
	 // vertices reachable from vertex v
		cout << "从顶点" << v << "开始深度优先搜索\n";
		this->temp = temp;
		//this->label = label;
		this->t = 1;
		rDfs(v);
		temp = this->temp;
	}
	//寻找一条路径
	//int* findPath(int theSource, int theDestination)
	//{//  寻找一条从顶点theSource到顶点theDestination的路径 
	// // 返回一个数组path，从索引1开始表示路径。path[0]表示路径长度 
	// // 如果路径不存在，返回NULL 
	// // 为寻找路径的递归算法初始化 
	//	int n = numberOfVertices();
	//	path = new int[n + 1];
	//	path[1] = theSource;      // 第一个顶点
	//	length = 1;               // 当前路径长度+1 
	//	destination = theDestination;
	//	reach = new int[n + 1];
	//	for (int i = 1; i <= n; i++)
	//		reach[i] = 0;

	//	// 搜索路径 
	//	if (theSource == theDestination || rFindPath(theSource))//rFindPath是寻找路径的实际算法 
	//															// 找到一条路径 
	//		path[0] = length - 1;
	//	else
	//	{
	//		delete[] path;
	//		path = NULL;
	//	}

	//	delete[] reach;
	//	return path;
	//}
};

// overload <<
template <class T>
ostream& operator<<(ostream& out, const linkedWDigraph<T>& x)
{
	x.output(out); return out;
}