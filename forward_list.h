#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <iostream>
#include <string>

using namespace std;

struct FNode {
	string value;
	FNode* next;
	FNode(const string& v, FNode* n = nullptr) : value(v), next(n) {}
};

struct ForwardList {
	FNode* head;
	FNode* tail;
	int count;

	ForwardList();
	~ForwardList();

	void pushFront(const string& value);
	void pushBack(const string& value);
	void insertAfter(FNode* prev, const string& value);
	void insertBefore(FNode* target, const string& value);
	
	void popFront();
	void popBack();
	void removeAfter(FNode* prev);
	void removeBefore(FNode* target);

	FNode* find(const string& value);
	bool removeByValue(const string& value);
	string getByIndex(int index);

	void print() const;
	void clear();

	int getCount() const { return count; }
	FNode* getHead() const { return head; }
};

#endif
