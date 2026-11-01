#include "stack.h"

Stack::Stack(int cap) {
	capacity = cap;
	top = -1;
	data = new string[capacity];
}

Stack::~Stack() { delete[] data; }

void Stack::push(const string& value) {
	if (top + 1 >= capacity) {
		capacity *= 2;
		string* nd = new string[capacity];
		for (int i = 0; i <= top; ++i) nd[i] = data[i];
		delete[] data; 
		data = nd;
	}
	data[++top] = value;
}

bool Stack::pop() {
	if (top < 0) return false;
	--top; 
	return true;
}

string Stack::peek() const { 
	return (top >= 0) ? data[top] : "ERROR"; 
}

void Stack::print() const {
	cout << "Стек(верхушка->конец): [";
	for (int i = top; i >= 0; --i) {
		if (i != top) cout << ", ";
		cout << data[i];
	}
	cout << "]\n";
}

void Stack::clear() { top = -1; }
