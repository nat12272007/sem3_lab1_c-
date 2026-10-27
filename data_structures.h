#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <iostream>
#include <algorithm>

using namespace std;

//a.массив
struct DynamicArray {
	int* data = nullptr;
	int size = 0;
	int capacity = 0;

	void init(int cap = 4) {
		capacity = cap;
		data = new int[capacity];
	}

	void ensureCapacity(int needed) {
		if (needed <= capacity) return;
		while (capacity < needed) capacity *= 2;
		int* newData = new int[capacity];
		for (int i = 0; i < size; ++i) newData[i] = data[i];
		delete[] data;
		data = newData;
	}

	void pushBack(int value) {
		ensureCapacity(size + 1);
		data[size++] = value;
	}

	void pushAt(int index, int value) {
		if (index < 0 || index > size) return;
		ensureCapacity(size + 1);
		for (int i = size; i > index; --i) data[i] = data[i - 1];
		data[index] = value;
        ++size;
	}
    
	int get(int index) const {
		return (index >= 0 && index < size) ? data[index] : -1;
	}
    
	void removeAt(int index) {
		if (index < 0 || index >= size) return;
		for (int i = index; i < size - 1; ++i) data[i] = data[i + 1];
		--size;
	}
    
	void set(int index, int value) {
		if (index >= 0 && index < size) data[index] = value;
	}
    
	int length() const { return size; }

	void print() const {
		cout << "[";
		for (int i = 0; i < size; ++i) {
			if (i) cout << ", ";
			cout << data[i];
		}
		cout << "]\n";
	}
    
	void clear() { delete[] data; data = nullptr; size = 0; capacity = 0; }
};

//b.односвязный список
struct FNode {
	int value;
	FNode* next;
};

struct ForwardList {
	FNode* head = nullptr;
	FNode* tail = nullptr;
	int count = 0;

	void pushFront(int value) {
		FNode* node = new FNode{value, head};
		head = node;
		if (!tail) tail = node;
		++count;
	}
    
	void pushBack(int value) {
		FNode* node = new FNode{value, nullptr};
		if (tail) tail->next = node;
		else head = node;
		tail = node;
		++count;
	}
    
	void insertAfter(FNode* prev, int value) {
		if (!prev) return;
		FNode* node = new FNode{value, prev->next};
		prev->next = node;
		if (prev == tail) tail = node;
		++count;
	}
    
	void insertBefore(FNode* target, int value) {
		if (head == target) { pushFront(value); return; }
		FNode* prev = head;
		while (prev && prev->next != target) prev = prev->next;
		if (prev) insertAfter(prev, value);
	}
    
	void popFront() {
		if (!head) return;
		FNode* tmp = head;
		head = head->next;
		if (!head) tail = nullptr;
		delete tmp;
		--count;
	}
    
	void popBack() {
		if (!head) return;
		if (head == tail) { delete head; head = tail = nullptr; --count; return; }
		FNode* prev = head;
		while (prev->next != tail) prev = prev->next;
		delete tail;
		tail = prev;
		tail->next = nullptr;
		--count;
	}
    
	void removeAfter(FNode* prev) {
		if (!prev || !prev->next) return;
		FNode* toDelete = prev->next;
		prev->next = toDelete->next;
		if (toDelete == tail) tail = prev;
		delete toDelete;
		--count;
	}
    
	void removeBefore(FNode* target) {
		if (!head || head == target) return;
		if (head->next == target) { popFront(); return; }
		FNode* prev = head;
		while (prev->next && prev->next->next != target) prev = prev->next;
		if (prev->next) removeAfter(prev);
	}
    
	FNode* find(int value) {
		for (FNode* cur = head; cur; cur = cur->next)
			if (cur->value == value) return cur;
		return nullptr;
	}
    
	bool removeByValue(int value) {
		if (!head) return false;
		if (head->value == value) { popFront(); return true; }
		FNode* prev = head;
		while (prev->next && prev->next->value != value) prev = prev->next;
		if (prev->next) { removeAfter(prev); return true; }
		return false;
	}
    
	int getByIndex(int index) {
		if (index < 0) return -1;
		FNode* cur = head;
		for (int i = 0; cur && i < index; ++i) cur = cur->next;
		return cur ? cur->value : -1;
	}
    
	void print() const {
		cout << "[";
		FNode* cur = head;
		bool first = true;
		while (cur) {
			if (!first) cout << " -> ";
			cout << cur->value;
			cur = cur->next;
			first = false;
		}
		cout << "]\n";
	}
	
	void clear() { while(head) popFront(); }
};

//c.двусвязный список
struct LNode {
	int value;
	LNode* prev;
	LNode* next;
};

struct DoublyList {
	LNode* head = nullptr;
	LNode* tail = nullptr;
	int count = 0;

	void pushFront(int value) {
		LNode* node = new LNode{value, nullptr, head};
		if (head) head->prev = node;
		else tail = node;
		head = node;
		++count;
	}
    
	void pushBack(int value) {
		LNode* node = new LNode{value, tail, nullptr};
		if (tail) tail->next = node;
		else head = node;
		tail = node;
		++count;
	}
    
	void insertAfter(LNode* pos, int value) {
		if (!pos) return;
		LNode* node = new LNode{value, pos, pos->next};
		if (pos->next) pos->next->prev = node;
		else tail = node;
		pos->next = node;
		++count;
	}
    
	void insertBefore(LNode* pos, int value) {
		if (!pos) return;
		LNode* node = new LNode{value, pos->prev, pos};
		if (pos->prev) pos->prev->next = node;
		else head = node;
		pos->prev = node;
		++count;
	}
    
	void popFront() {
		if (!head) return;
		LNode* tmp = head;
		head = head->next;
		if (head) head->prev = nullptr;
		else tail = nullptr;
		delete tmp;
		--count;
	}
    
	void popBack() {
		if (!tail) return;
		LNode* tmp = tail;
		tail = tail->prev;
		if (tail) tail->next = nullptr;
		else head = nullptr;
		delete tmp;
		--count;
	}
    
	void removeNode(LNode* node) {
		if (!node) return;
		if (node->prev) node->prev->next = node->next;
		else head = node->next;
		if (node->next) node->next->prev = node->prev;
		else tail = node->prev;
		delete node;
		--count;
	}
    
	LNode* find(int value) {
		for (LNode* cur = head; cur; cur = cur->next)
			if (cur->value == value) return cur;
		return nullptr;
	}
    
	bool removeByValue(int value) {
		LNode* node = find(value);
		if (node) { removeNode(node); return true; }
		return false;
	}
    
	int getByIndex(int index) {
		if (index < 0) return -1;
		LNode* cur = head;
		for (int i = 0; cur && i < index; ++i) cur = cur->next;
		return cur ? cur->value : -1;
	}
    
	void print() const {
		cout << "[";
		LNode* cur = head;
		bool first = true;
		while (cur) {
			if (!first) cout << " <-> ";
			cout << cur->value;
			cur = cur->next;
			first = false;
		}
		cout << "]\n";
	}
    
	void clear() { while(head) popFront(); }
};

//d.стек
struct Stack {
	int* data = nullptr;
	int top = -1;
	int capacity = 0;

	void init(int cap = 4) { capacity = cap; data = new int[capacity]; }
    
	void push(int value) {
		if (top + 1 >= capacity) {
			capacity *= 2;
			int* nd = new int[capacity];
			for (int i = 0; i <= top; ++i) nd[i] = data[i];
			delete[] data; data = nd;
		}
		data[++top] = value;
	}
    
	bool pop() {
		if (top < 0) return false;
		--top; 
		return true;
	}

	int peek() const { return (top >= 0) ? data[top] : -1; }
    
	void print() const {
		cout << "Стек(верхушка->низ): [";
		for (int i = top; i >= 0; --i) {
			if (i != top) cout << ", ";
			cout << data[i];
		}
		cout << "]\n";
	}
    
	void clear() { delete[] data; data = nullptr; top = -1; capacity = 0; }
};

//e.очередь
struct Queue {
	int* data = nullptr;
	int frontIdx = 0, backIdx = 0, count = 0, capacity = 0;

	void init(int cap = 4) { capacity = cap; data = new int[capacity]; }
    
	void push(int value) {
		if (count == capacity) {
			int newCap = capacity * 2;
			int* nd = new int[newCap];
			for (int i = 0; i < count; ++i) nd[i] = data[(frontIdx + i) % capacity];
			delete[] data; data = nd; capacity = newCap; frontIdx = 0; backIdx = count;
		}
		data[backIdx] = value;
		backIdx = (backIdx + 1) % capacity;
		++count;
	}
    
	bool pop() {
		if (count == 0) return false;
		frontIdx = (frontIdx + 1) % capacity;
		--count; 
		return true;
	}

	int peek() const { return (count > 0) ? data[frontIdx] : -1; }
    
	void print() const {
		cout << "Очередь(начало->конец): [";
		for (int i = 0; i < count; ++i) {
			if (i) cout << ", ";
			cout << data[(frontIdx + i) % capacity];
		}
		cout << "]\n";
	}
    
	void clear() { delete[] data; data = nullptr; frontIdx = backIdx = count = capacity = 0; }
};

//f.дерево
struct CompleteBinaryTree {
	int* tree = nullptr;
	int size = 0, capacity = 0;

	void init(int cap = 4) { capacity = cap; tree = new int[capacity + 1]; }
    

	void ensureCapacity(int needed) {
		if (needed <= capacity) return;
		while (capacity < needed) capacity *= 2;
		int* nt = new int[capacity + 1];
		for (int i = 1; i <= size; ++i) nt[i] = tree[i];
		delete[] tree; tree = nt;
	}
    
	void insert(int value) { ensureCapacity(size + 1); tree[++size] = value; }
    
	int search(int value) const {
		for (int i = 1; i <= size; ++i) if (tree[i] == value) return i;
		return -1;
	}
    
	bool remove(int value) {
		int pos = search(value);
		if (pos == -1) return false;
		tree[pos] = tree[size];
		--size;
		return true;
	}
    
	bool isComplete() const {
		for (int i = 1; i <= size; ++i) {
			if (2 * i <= size && tree[2 * i] == 0) return false;
			if (2 * i + 1 <= size && tree[2 * i + 1] == 0) return false;
		}
		return true;
	}
    
	void print() const {
		cout << "Дерево(обход по уровням): [";
		for (int i = 1; i <= size; ++i) {
			if (i > 1) cout << ", ";
			cout << tree[i];
		}
		cout << "]\n";
	}
    
	void printPreOrder(int index) const {
		if (index > size) return;
		cout << tree[index] << " ";
		printPreOrder(2 * index);
		printPreOrder(2 * index + 1);
	}
    
	void printInOrder(int index) const {
		if (index > size) return;
		printInOrder(2 * index);
		cout << tree[index] << " ";
		printInOrder(2 * index + 1);
	}
    
	void printPostOrder(int index) const {
		if (index > size) return;
		printPostOrder(2 * index);
		printPostOrder(2 * index + 1);
		cout << tree[index] << " ";
	}
    
	void printPre() const  { cout << "Дерево(прямой обход): [ ";  printPreOrder(1);  cout << "]\n"; }
    
	void printIn() const   { cout << "Дерево(центрированный обход): [ ";   printInOrder(1);   cout << "]\n"; }
    
	void printPost() const { cout << "Дерево(обратный обход): [ "; printPostOrder(1); cout << "]\n"; }

	void clear() { delete[] tree; tree = nullptr; size = 0; capacity = 0; }
};

#endif
