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
	int color = 0;//0白色，1灰色，2黑色
	int pi = 0;//初始前驱不存在
	int discover = 0;//初始发现时间
	int finish = 0;//初始结束时间
	int low;//
	int child = 0;//初始孩子数目
	bool root = false;//是否为根节点
	int distance = 1000;//初始距离正无穷
	vertex(){}
	//vertex(int pi, int color) { this->pi = pi; this->color = color; }
};
// overload <<
ostream& operator<<(ostream& out, const vertex& x)
{
	out << "color: " << x.color << "\tpi: " << x.pi << "\tdiscover: " << x.discover << "\tfinish: " << x.finish << "\tlow: " << x.low;
	return out;
}
template <class T>
struct wEdge
{// vertex and weight pair
	int vertex;
	T weight;
	//int category;//0树边，1前向边，2后向边，3横向边

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
	int t = 1;

	void rDfs1(int v)
	{// Recursive dfs method.
		temp[v].color = 1;//置为灰色
		temp[v].discover = t;
		myIterator *iv = iterator(v);
		int u;
		while ((u = iv->next()) != 0)
		{
			// visit an adjacent vertex of v
			if (temp[u].color == 0)//树边
			{
				cout << "(" << v << "," << u << ")是一条树边\n";
				temp[u].pi = v;
				t++;
				rDfs1(u);  // u is an unreached vertex
			}
			else if (temp[u].color == 1)//后向边
			{
				cout << "(" << v << "," << u << ")是一条后向边\n";
				this->eraseEdge(v, u);
			}
			else if (temp[u].color == 2)//
			{
				if (temp[v].discover > temp[u].discover)//横向边
				{
					cout << "(" << v << "," << u << ")是一条横向边\n";
				}
				else if (temp[v].discover < temp[u].discover)//前向边
				{
					cout << "(" << v << "," << u << ")是一条前向边\n";
					
				}
			}
		}

				
		delete iv;
		temp[v].finish = t;
		temp[v].color = 2;//置为黑色
	}
	void rDfs2(int v)
	{// Recursive dfs method.
		temp[v].color = 1;//置为灰色
		temp[v].discover = t;
		temp[v].low = t;
		myIterator *iv = iterator(v);
		int u;
		while ((u = iv->next()) != 0)
		{
			if (temp[u].color == 0)//树边
			{

				temp[v].child++;
				temp[u].pi = v;
				t++;
				rDfs2(u);  // u is an unreached vertex
				if (temp[u].low < temp[v].low)
					temp[v].low = temp[u].low;

				if (!temp[v].root && temp[u].low >= temp[v].discover)
					cout << "结点 " << v << " 是割点\n";
				else if (temp[v].root && temp[v].child >= 2)
					cout << "结点 " << v << " 是割点\n";
			}
			else if (temp[v].pi != u && temp[u].color == 1)//后向边
			{
				temp[v].low = temp[u].discover;
			}
		}


		delete iv;
		temp[v].finish = t;
		temp[v].color = 2;//置为黑色
	}
	int rDfs3(int v)
	{// Recursive dfs method.
		temp[v].color = 1;//置为灰色
		temp[v].discover = t;
		temp[v].low = t;
		myIterator *iv = iterator(v);
		int u;
		while ((u = iv->next()) != 0)
		{
			// visit an adjacent vertex of v
			if (temp[u].color == 0)//树边
			{
				cout << "(" << v << "," << u << ")是一条树边\n";

				temp[v].child++;
				temp[u].pi = v;
				t++;
				int t = rDfs3(u);
				if (t != 0)
					return t; 
			}
			else if (temp[v].pi != u && temp[u].color == 1)//后向边
			{
				cout << "(" << v << "," << u << ")是一条后向边\n";
				temp[u].pi = v;
				return u;
			}
		}


		delete iv;
		temp[v].finish = t;
		temp[v].color = 2;//置为黑色
		return 0;
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
	edge<T> getEdge(int i, int j)
	{
		if (existsEdge(i, j))
		{
			int index = aList[i].indexOf(wEdge<T>(j));
			wEdge<T> element = aList[i].get(index);
			edge<T> temp(i, j, element.weight);
			return temp;
		}
		else
		{
			edge<T> temp(0, 0, 0);
			return temp;
		}
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




	// iterators to discover and end of list
	class myIterator 
	{
	public:
		myIterator(chainNode<wEdge<T> > *theNode)
		{
			currentNode = theNode;
			firstNode = theNode;
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

	//局部替换最小生成树算法
	void particalExchange(linkedWDigraph<T>& tar)
	{
		int tarn = tar.numberOfVertices();
		for (int v = 1; v <= tarn; v++)
		{
			cout << "\n扫描" << v << "的邻接链表\n";
			myIterator *iv = iterator(v);
			int u;
			while ((u = iv->next()) != 0)
			{
				//int index = aList[v].indexOf(wEdge<T>(u));
				//wEdge<T> element = aList[v].get(index);
				////cout << element;
				//edge<T> temp(v, u, element.weight);
				if (u > v)
				{
					edge<T> temp = getEdge(v, u);
					edge<T> temp2 = getEdge(u, v);
					cout << "尝试添加边" << temp << endl;
					tar.insertEdge(&temp);
					tar.insertEdge(&temp2);
					tar.exchange(temp.vertex1());
					cout << "当前图：\n" << tar;
				}
				
			}


			delete iv;
			cout << "\n";
		}
		
	}

	void exchange(int vo)
	{
		vector<vertex> temp(n + 1);
		int tu = dfs3(vo, temp);
		if (tu != 0)
		{

			int v = temp[tu].pi;
			int u = tu;

			edge<T> tedge = getEdge(v, u);
			int weight = tedge.weight();

			cout << u ;
			int maxv = v, maxu = u;
			while (v != tu)
			{
				u = v;
				v = temp[u].pi;
				tedge = getEdge(v, u);
				if (tedge.weight() > weight)
				{
					weight = tedge.weight();
					maxv = v;
					maxu = u;
				}
				cout <<  " ---> " << u  ;

			}
			cout << " ---> " << tu <<" 形成环\n";
			eraseEdge(maxu, maxv);
			eraseEdge(maxv, maxu);
			
			cout << "(" << maxv << "," << maxu << ")" << "需要删去\n";
		}
		else
		{
			cout << "成功添加边\n";
		}
		
		
	}


	//Bellman-Ford算法
	int bellmanFord(int s, vector<vertex> &temp)
	{
		//初始化
		for (int i = 1; i <= n; i++)
		{
			temp[i].distance = 1000;
			temp[i].pi = 0;
		}
		temp[s].distance = 0;

		//v-1次松弛操作
		for (int i = 1; i < n; i++)
		{

			for (int v = 1; v <= n; v++)
			{
				chainNode<wEdge<T> > *firstNode = aList[v].getfirstNode();
				chainNode<wEdge<T> > *currentNode = firstNode;
				while (currentNode != NULL)
				{
					int u = currentNode->element.vertex;
					int w = currentNode->element.weight;
					cout <<"操作边 " << v << "," << u << "    " ;

					if (temp[v].distance != 1000 && temp[u].distance > temp[v].distance + w)
					{
						cout << temp[u].distance <<" --->" << temp[v].distance + w;
						temp[u].distance = temp[v].distance + w;
						temp[u].pi = v;
						cout << "  前驱结点  " << v << endl;
					}
					else
					{
						cout << "不需要更新\n";
					}
					
					currentNode = currentNode->next;
				}
			}
			cout << endl;

		}

		//对每个边进行松弛，如果可以松弛则有负环
		for (int v = 1; v <= n; v++)
		{
			chainNode<wEdge<T> > *firstNode = aList[v].getfirstNode();
			chainNode<wEdge<T> > *currentNode = firstNode;
			while (currentNode != NULL)
			{
				int u = currentNode->element.vertex;
				int w = currentNode->element.weight;

				if (temp[u].distance > temp[v].distance + w)
				{
					return u;
				}

				currentNode = currentNode->next;
			}
		}
		return 0;



	}

	//通过Bellman-Ford算法找负环
	void negCircle()
	{
		vector<vertex> tmp(n + 1);
		vector<int> que;
		int flag = bellmanFord(1, tmp);
		if (flag == 0)
			cout << "success\n";
		else
		{
			int index = -1;
			do
			{
				que.push_back(flag);
				cout << flag << "\t";
				flag = tmp[flag].pi;
				if ((index = com(flag, que)) != -1)
				{
					que.push_back(flag);
					break;
				}
			} while (1);


			cout << "\npath  ";
			for (int i = que.size() - 1; i >= index; i--)
			{
				cout << que[i] << "  ";
			}

		}

		cout << endl;
	}

	//动态规划解数据量小的TPS问题
	T dynamic_TPS(int source, int v, vector<int> S, vector<int> &path)
	{
		cout << "从点" << v << "开始，从集合{";
		for (int i = 0; i < S.size(); i++)
		{
			cout << S[i];
			if (i != S.size() - 1)
			{
				cout << ",";
			}
		}
		cout << "}开始扫描\n";

		if (S.size() == 1)
		{
			//path.insert(path.begin(), S[0]);
			path.push_back(S[0]);
			path.push_back(source);
			cout << "从点" << v << "开始，从集合{"<<S[0]<<"}扫描结束  ";
			cout << "最短路径为" << v << "," << S[0] << "," << source << "  ";
			cout << "  长度为" << getEdge(v, S[0]).weight() + getEdge(S[0], source) << endl;
			return getEdge(v, S[0]).weight() + getEdge(S[0], source);
		}
		vector<vector<int> > tpath(S.size());
		vector<int> St = S;
		St.erase(St.begin() + 0);
		T min = getEdge(v, S[0]).weight() + dynamic_TPS(source, S[0], St, tpath[0]);
		St = S;
		int minindex = 0;
		for (int i = 1; i < S.size(); i++)
		{
			St.erase(St.begin() + i);
			T temp = getEdge(v, S[i]).weight() + dynamic_TPS(source, S[i], St, tpath[i]);
			St = S;
			if (temp < min)
			{
				minindex = i;
				min = temp;
			}
		}

		tpath[minindex].insert(tpath[minindex].begin(), S[minindex]);

		cout << "从点" << v << "开始，从集合{";
		for (int i = 0; i < S.size(); i++)
		{
			cout << S[i];
			if (i != S.size() - 1)
			{
				cout << ",";
			}
		}
		cout << "}扫描结束  ";
		cout << "最短路径为" << v << ",";
		for (int i = 0; i < tpath[minindex].size(); i++)
		{
			cout << tpath[minindex][i];
			if (i != tpath[minindex].size() - 1)
			{
				cout << ",";
			}
		}
		cout << "  长度为" << min << endl;
		if (v == source)
		{
			tpath[minindex].insert(tpath[minindex].begin(), source);
		}
		path = tpath[minindex];
		return min;

	}

	// 广度优先搜索 
	void bfs(int v, vector<vertex> &temp)
	{// Breadth-first search. reach[i] is set to label for
	 // all vertices reachable from vertex v.
		arrayQueue<int> q(10);
		t = 1;
		temp[v].color = 2;
		temp[v].discover = temp[v].finish = t;
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
				if (temp[u].color == 0)
				{// u is an unreached vertex
					t++;
					q.push(u);
					temp[u].color = 2; // mark reached
					temp[u].pi = w;
					temp[u].discover = temp[u].finish = t;
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
	void dfs1(int v, vector<vertex> &temp)
	{// Depth-first search. reach[i] is set to label for all
	 // vertices reachable from vertex v
		cout << "从顶点" << v << "开始深度优先搜索\n";
		this->temp = temp;
		this->t = 1;
		this->temp[v].root = true;
		rDfs1(v);
		temp = this->temp;
	}
	//深度优先搜索 
	void dfs2(int v, vector<vertex> &temp)
	{
		this->temp = temp;
		this->t = 1;
		this->temp[v].root = true;
		rDfs2(v);
		temp = this->temp;
	}
	//深度优先搜索 
	int dfs3(int v, vector<vertex> &temp)
	{// Depth-first search. reach[i] is set to label for all
	 // vertices reachable from vertex v
		cout << "从顶点" << v << "开始深度优先搜索\n";
		this->temp = temp;
		this->t = 1;
		this->temp[v].root = true;
		int h = rDfs3(v);
		temp = this->temp;
		return h;
	}

};

// overload <<
template <class T>
ostream& operator<<(ostream& out, const linkedWDigraph<T>& x)
{
	x.output(out); return out;
}