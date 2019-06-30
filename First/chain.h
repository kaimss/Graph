#pragma once
#include"chainNode.h"
#include<iostream>
using namespace std;

template<class T>
class chain
{
public:
	chain(int capacity = 10);
	chain(const chain<T>&);
	~chain();

	int size() { return listSize; }
	T& get(int theIndex);
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	T* eraseElement(int theVertex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;
	chainNode<T>* getfirstNode() { return firstNode; }

	
	// iterators to discover and end of list
	class iterator;
	iterator begin() { return iterator(firstNode); }
	iterator end() { return iterator(NULL); }

	// iterator for chain
	class iterator
	{
	public:

		// constructor
		iterator(chainNode<T>* theNode = NULL)
		{
			node = theNode;
		}

		// dereferencing operators
		T& operator*() const { return node->element; }
		T* operator->() const { return &node->element; }

		// increment
		iterator& operator++()   // preincrement
		{
			node = node->next; return *this;
		}
		iterator operator++(int) // postincrement
		{
			iterator old = *this;
			node = node->next;
			return old;
		}

		// equality testing
		bool operator!=(const iterator right) const
		{
			return node != right.node;
		}
		bool operator==(const iterator right) const
		{
			return node == right.node;
		}
	private:
		chainNode<T>* node;
	};  // end of iterator class

protected:
	void checkIndex(int theIndex);
	chainNode<T>* firstNode;
	int listSize;
};
template<class T>
chain<T>::chain(int initialCapacity)
{// Constructor.
	if (initialCapacity < 1)
	{
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw s.str();
	}
	firstNode = NULL;
	listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T>& theList)
{// Copy constructor.
	listSize = theList.listSize;

	if (listSize == 0)
	{// theList is empty
		firstNode = NULL;
		return;
	}

	// non-empty list
	chainNode<T>* sourceNode = theList.firstNode;
	// node in theList to copy from
	firstNode = new chainNode<T>(sourceNode->element);
	// copy first element of theList
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = firstNode;
	// current last node in *this
	while (sourceNode != NULL)
	{// copy remaining elements
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL; // end the chain
}

template<class T>
chain<T>::~chain()
{// Chain destructor. Delete all nodes in chain.
	while (firstNode != NULL)
	{// delete firstNode
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<class T>
void chain<T>::checkIndex(int theIndex)
{// Verify that theIndex is between 0 and listSize - 1.
	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw s.str();
	}

}

template<class T>
T& chain<T>::get(int theIndex)
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);

	// move to desired node
	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; i++)
		currentNode = currentNode->next;

	return currentNode->element;
}

template<class T>
int chain<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

 // search the chain for theElement
	chainNode<T>* currentNode = firstNode;
	int index = 0;  // index of currentNode
	while (currentNode != NULL &&
		currentNode->element != theElement)
	{
		// move to next node
		currentNode = currentNode->next;
		index++;
	}

	// make sure we found matching element
	if (currentNode == NULL)
		return -1;
	else
		return index;
}

template<class T>
void chain<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);

	// valid index, locate node with element to delete
	chainNode<T>* deleteNode;
	if (theIndex == 0)
	{// remove first node from chain
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{  // use p to get to predecessor of desired node
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		deleteNode = p->next;
		p->next = p->next->next; // remove deleteNode from chain
	}
	listSize--;
	delete deleteNode;
}
template<class T>
T* chain<T>::eraseElement(int theVertex)
{// Delete node with element == theVertex. Return pointer to
 // deleted element. Return NULL if no matching element.
	chainNode<T> *current = firstNode,
		*trail = NULL; // one behind current

					   // search for match
	while (current != NULL && current->element != theVertex)
	{
		trail = current;
		current = current->next;
	}

	if (current == NULL) // no match
		return NULL;

	// match found in node current
	T* theElement = &current->element; // save matching element

									   // remove current from chain
	if (trail != NULL)
		trail->next = current->next;
	else
		firstNode = current->next; // current is first node

	delete current;
	listSize--;
	return theElement;
}
template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > listSize)
	{// invalid index
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw s.str();
	}

	if (theIndex == 0)
		// insert at front
		firstNode = new chainNode<T>(theElement, firstNode);
	else
	{  // find predecessor of new element
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		// insert after p
		p->next = new chainNode<T>(theElement, p->next);
	}
	listSize++;
}
template<class T>
void chain<T>::output(ostream& out) const
{// Put the list into the stream out.
	for (chainNode<T>* currentNode = firstNode;
		currentNode != NULL;
		currentNode = currentNode->next)
		out << currentNode->element << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const chain<T>& x)
{
	x.output(out); return out;
}