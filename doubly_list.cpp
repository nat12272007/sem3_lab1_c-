#include "doubly_list.h"

DoublyList::DoublyList() : head(nullptr), tail(nullptr), count(0) {}
DoublyList::~DoublyList() { clear(); }

void DoublyList::pushFront(const string& value) {
	LNode* node = new LNode(value, nullptr, head);
	if (head) head->prev = node;
	else tail = node;
	head = node;
	++count;
}

void DoublyList::pushBack(const string& value) {
	LNode* node = new LNode(value, tail, nullptr);
	if (tail) tail->next = node;
	else head = node;
	tail = node;
	++count;
}

void DoublyList::insertAfter(LNode* pos, const string& value) {
	if (!pos) return;
	LNode* node = new LNode(value, pos, pos->next);
	if (pos->next) pos->next->prev = node;
	else tail = node;
	pos->next = node;
	++count;
}

void DoublyList::insertBefore(LNode* pos, const string& value) {
	if (!pos) return;
	LNode* node = new LNode(value, pos->prev, pos);
	if (pos->prev) pos->prev->next = node;
	else head = node;
	pos->prev = node;
	++count;
}

void DoublyList::popFront() {
	if (!head) return;
	LNode* tmp = head;
	head = head->next;
	if (head) head->prev = nullptr;
	else tail = nullptr;
	delete tmp;
	--count;
}

void DoublyList::popBack() {
	if (!tail) return;
	LNode* tmp = tail;
	tail = tail->prev;
	if (tail) tail->next = nullptr;
	else head = nullptr;
	delete tmp;
	--count;
}

void DoublyList::removeNode(LNode* node) {
	if (!node) return;
	if (node->prev) node->prev->next = node->next;
	else head = node->next;
	if (node->next) node->next->prev = node->prev;
	else tail = node->prev;
	delete node;
	--count;
}

LNode* DoublyList::find(const string& value) {
	for (LNode* cur = head; cur; cur = cur->next)
		if (cur->value == value) return cur;
	return nullptr;
}

bool DoublyList::removeByValue(const string& value) {
	LNode* node = find(value);
	if (node) { removeNode(node); return true; }
	return false;
}

string DoublyList::getByIndex(int index) {
	if (index < 0) return "ERROR";
	LNode* cur = head;
	for (int i = 0; cur && i < index; ++i) cur = cur->next;
	return cur ? cur->value : "ERROR";
}

void DoublyList::print() const {
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

void DoublyList::printBack() const {
	cout << "[";
	LNode* cur = tail;
	bool first = true;
	while (cur) {
		if (!first) cout << " <-> ";
		cout << cur->value;
		cur = cur->prev;
		first = false;
	}
	cout << "]\n";
}

void DoublyList::clear() { 
	while(head) popFront(); 
}
