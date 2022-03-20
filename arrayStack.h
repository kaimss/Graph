#pragma once
#include <sstream>
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0)
		throw "new length must be >= 0";

	T* temp = new T[newLength];              // new array
	int number = oldLength > newLength ? newLength : oldLength;
		//min(oldLength, newLength);  // number to copy
	copy(a, a + number, temp);
	delete[] a;                             // deallocate old memory
	a = temp;
}


template<class T>
class arrayStack 
{
public:
	arrayStack(int initialCapacity = 10);
	~arrayStack() { delete[] stack; }
	bool empty() const { return stackTop == -1; }
	int size() const
	{
		return stackTop + 1;
	}
	T& top()
	{
		if (stackTop == -1)
			throw "stackEmpty";
		return stack[stackTop];
	}
	void pop()
	{
		if (stackTop == -1)
			throw "stackEmpty";
		stack[stackTop--].~T();  // destructor for T
	}
	void push(const T& theElement);
private:
	int stackTop;         // current top of stack
	int arrayLength;      // stack capacity
	T *stack;           // element array
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{// Constructor.
	if (initialCapacity < 1)
	{
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw s.str();
	}
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stackTop = -1;
}

template<class T>
void arrayStack<T>::push(const T& theElement)
{// Add theElement to stack.
	if (stackTop == arrayLength - 1)
	{// no space, double capacity
		changeLength1D(stack, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	// add at stack top
	stack[++stackTop] = theElement;
}