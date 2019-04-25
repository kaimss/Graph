#pragma once
#include"chain.h"
#include"edge.h"
#include"arrayQueue.h"
#include"arrayStack.h"
#include <sstream>
#include<iostream>
using namespace std;

template <class T>
struct wEdge
{// vertex and weight pair
	int vertex;
	T weight;
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

	int degree(int theVertex) const
	{
		throw "degree() undefined";
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
	class myIterator;
	//myIterator begin() { return myIterator(firstNode); }
	//myIterator end() { return myIterator(NULL); }
	class myIterator 
	{
	public:
		myIterator(chainNode<wEdge<T> > *theNode)
		{
			currentNode = theNode;
		}

		~myIterator() {}

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

	protected:
		chainNode<wEdge<T> > *currentNode;
	};

	myIterator* iterator(int theVertex)
	{// Return iterator for vertex theVertex.
		checkVertex(theVertex);
		return new myIterator(aList[theVertex].getfirstNode()); 
		//return new myIterator(aList[theVertex].firstNode);
		
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


			//myIterator i = iterator(w);
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

};

// overload <<
template <class T>
ostream& operator<<(ostream& out, const linkedWDigraph<T>& x)
{
	x.output(out); return out;
}