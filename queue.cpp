#include "queue.h"

Queue::Queue(int cap) {
	capacity = cap;
	data = new string[capacity];
	frontIdx = 0; backIdx = 0; count = 0;
}

Queue::~Queue() { delete[] data; }

void Queue::push(const string& value) {
	if (count == capacity) {
		int newCap = capacity * 2;
		string* nd = new string[newCap];
		for (int i = 0; i < count; ++i) nd[i] = data[(frontIdx + i) % capacity];
		delete[] data; 
		data = nd; 
		capacity = newCap; 
		frontIdx = 0; 
		backIdx = count;
	}
	data[backIdx] = value;
	backIdx = (backIdx + 1) % capacity;
	++count;
}

bool Queue::pop() {
	if (count == 0) return false;
	frontIdx = (frontIdx + 1) % capacity;
	--count; 
	return true;
}

string Queue::peek() const { 
	return (count > 0) ? data[frontIdx] : "ERROR"; 
}

void Queue::print() const {
	cout << "Очередь(начало->конец): [";
	for (int i = 0; i < count; ++i) {
		if (i) cout << ", ";
		cout << data[(frontIdx + i) % capacity];
	}
	cout << "]\n";
}

void Queue::clear() { frontIdx = backIdx = count = 0; }
