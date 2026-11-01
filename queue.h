#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

using namespace std;

struct Queue {
	string* data;
	int frontIdx, backIdx, count, capacity;

	Queue(int cap = 4);
	~Queue();

	void push(const string& value);
	bool pop();
	string peek() const;
	void print() const;
	void clear();

	int getCount() const { return count; }
	string getElement(int i) const { return data[(frontIdx + i) % capacity]; }
};

#endif
