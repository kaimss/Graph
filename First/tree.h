#pragma once
#define max_children 10
template<class T>
struct treeNode
{
	T ele;
	treeNode* parent;
	treeNode* children[max_children];
	int child;

	treeNode<T>(T ele, treeNode* parent) { this->ele = ele; this->parent = parent; }
};
template<class T>
class tree
{
private:
	treeNode<T>* root;
public:
	tree() { root = NULL; }
	~tree(){}
	void insert(treeNode<T>* t, T p, T c)
	{
		if (t->ele == p)
		{
			t->children[child] = new treeNode<T>(tp, c);
			t->child++;
		}
		for (int i = 0; i < t->child; i++)
		{
			insert(t->children[i], p, c);
		}
	}




};