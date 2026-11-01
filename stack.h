#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

using namespace std;

struct Stack {
	string* data;
	int top;
	int capacity;

	Stack(int cap = 4);
	~Stack();

	void push(const string& value);
	bool pop();
	string peek() const;
	void print() const;
	void clear();

	int getTop() const { return top; }
	string getElement(int index) const { return data[index]; }
};

#endif
