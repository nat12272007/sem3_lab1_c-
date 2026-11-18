#include "complete_binary_tree.h"
#include <queue>

CompleteBinaryTree::CompleteBinaryTree() {
	root = nullptr;
	size = 0;
}

CompleteBinaryTree::~CompleteBinaryTree() {
	clear();
}

static void destroyTree(TNode* node) {
	if (!node) return;
	destroyTree(node->left);
	destroyTree(node->right);
	delete node;
}

void CompleteBinaryTree::clear() {
	destroyTree(root);
	root = nullptr;
	size = 0;
}

static TNode* insertNode(TNode* node, int value, bool& added) {
	if (!node) {
		added = true;
		return new TNode(value);
	}
	if (value < node->value) {
		node->left = insertNode(node->left, value, added);
	} else if (value > node->value) {
		node->right = insertNode(node->right, value, added);
	}
	return node;
}

bool CompleteBinaryTree::insert(int value) {
	bool added = false;
	root = insertNode(root, value, added);
	if (added) size++;
	return added;
}

bool CompleteBinaryTree::search(int value) const {
	TNode* cur = root;
	while (cur) {
		if (value == cur->value) return true;
		cur = (value < cur->value) ? cur->left : cur->right;
	}
	return false;
}

static TNode* findMin(TNode* node) {
	while (node && node->left) node = node->left;
	return node;
}

static TNode* removeNode(TNode* node, int value, bool& removed) {
	if (!node) return nullptr;
	if (value < node->value) {
		node->left = removeNode(node->left, value, removed);
	} else if (value > node->value) {
		node->right = removeNode(node->right, value, removed);
	} else {
		removed = true;
		if (!node->left) {
			TNode* right = node->right;
			delete node;
			return right;
		}
		if (!node->right) {
			TNode* left = node->left;
			delete node;
			return left;
		}
		TNode* minNode = findMin(node->right);
		node->value = minNode->value;
		bool tmp = false;
		node->right = removeNode(node->right, minNode->value, tmp);
	}
	return node;
}

bool CompleteBinaryTree::remove(int value) {
	bool removed = false;
	root = removeNode(root, value, removed);
	if (removed) size--;
	return removed;
}

bool CompleteBinaryTree::isComplete() const {
	if (!root) return true;
    
	queue<TNode*> q;
	q.push(root);
	bool seenGap = false;
    
	while (!q.empty()) {
		TNode* n = q.front();
		q.pop();
        
		if (n->left) {
			if (seenGap) return false;
			q.push(n->left);
		} else {
			seenGap = true;
		}
        
		if (n->right) {
			if (seenGap) return false;
			q.push(n->right);
		} else {
			seenGap = true;
		}
	}
	return true;
}

void CompleteBinaryTree::print() const {
	cout << "Дерево(по уровням): [";
	if (root) {
		queue<TNode*> q;
		q.push(root);
		bool first = true;
		while (!q.empty()) {
			TNode* n = q.front();
			q.pop();
			if (!first) cout << ", ";
			cout << n->value;
			first = false;
			if (n->left) q.push(n->left);
			if (n->right) q.push(n->right);
		}
	}
	cout << "]\n";
}

static void printPreOrder(TNode* node) {
	if (!node) return;
	cout << node->value << " ";
	printPreOrder(node->left);
	printPreOrder(node->right);
}

static void printInOrder(TNode* node) {
	if (!node) return;
	printInOrder(node->left);
	cout << node->value << " ";
	printInOrder(node->right);
}

static void printPostOrder(TNode* node) {
	if (!node) return;
	printPostOrder(node->left);
	printPostOrder(node->right);
	cout << node->value << " ";
}

void CompleteBinaryTree::printPre() const {
	cout << "Pre-order: [ ";
	printPreOrder(root);
	cout << "]\n";
}

void CompleteBinaryTree::printIn() const {
	cout << "In-order: [ ";
	printInOrder(root);
	cout << "]\n";
}

void CompleteBinaryTree::printPost() const {
	cout << "Post-order: [ ";
	printPostOrder(root);
	cout << "]\n";
}

static void collectPreOrder(TNode* node, vector<int>& out) {
	if (!node) return;
	out.push_back(node->value);
	collectPreOrder(node->left, out);
	collectPreOrder(node->right, out);
}

vector<int> CompleteBinaryTree::getElements() const {
	vector<int> out;
	collectPreOrder(root, out);
	return out;
}
