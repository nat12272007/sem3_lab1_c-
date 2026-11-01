#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>

using namespace std;

struct Array {
	string* data;
	int size;
	int capacity;

	Array(int cap = 4);
	~Array();

	void ensureCapacity(int needed);
	void pushBack(const string& value);
	void pushAt(int index, const string& value);
	string get(int index) const;
	void removeAt(int index);
	void set(int index, const string& value);
	int length() const;
	void print() const;
	void clear();

	int getSize() const { return size; }
	string getElement(int index) const { return data[index]; }
};

#endif
