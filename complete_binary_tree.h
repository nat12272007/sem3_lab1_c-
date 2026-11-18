#ifndef COMPLETE_BINARY_TREE_H
#define COMPLETE_BINARY_TREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TNode {
	int value;
	TNode* left;
	TNode* right;
	TNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

struct CompleteBinaryTree {
	TNode* root;
	int size;

	CompleteBinaryTree();
	~CompleteBinaryTree();

	bool insert(int value);
	bool search(int value) const;
	bool remove(int value);
	bool isComplete() const;

	void print() const;
	void printPre() const;
	void printIn() const;
	void printPost() const;
	void clear();

	int getSize() const { return size; }
	vector<int> getElements() const;
};

#endif
