#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <iostream>
#include <string>

using namespace std;

struct LNode {
	string value;
	LNode* prev;
	LNode* next;
	LNode(const string& v, LNode* p = nullptr, LNode* n = nullptr) : value(v), prev(p), next(n) {}
};

struct DoublyList {
	LNode* head;
	LNode* tail;
	int count;

	DoublyList();
	~DoublyList();

	void pushFront(const string& value);
	void pushBack(const string& value);
	void insertAfter(LNode* pos, const string& value);
	void insertBefore(LNode* pos, const string& value);

	void popFront();
	void popBack();
	void removeNode(LNode* node);

	LNode* find(const string& value);
	bool removeByValue(const string& value);
	string getByIndex(int index);

	void print() const;
	void printBack() const;
	void clear();

	int getCount() const { return count; }
	LNode* getHead() const { return head; }
};

#endif
