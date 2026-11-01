#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "array.h"
#include "forward_list.h"
#include "doubly_list.h"
#include "stack.h"
#include "queue.h"
#include "complete_binary_tree.h"

using namespace std;

Array arr;
ForwardList flist;
DoublyList dlist;
Stack stk;
Queue q;
CompleteBinaryTree tree;

void saveToFile(const string& path) {
	ofstream out(path);
	if (!out) return;

	out << "Массив " << arr.getSize() << "\n";
	for (int i = 0; i < arr.getSize(); ++i) out << arr.getElement(i) << " ";
    
	out << "\nОднСписок " << flist.getCount() << "\n";
	for (FNode* cur = flist.getHead(); cur; cur = cur->next) out << cur->value << " ";
    
	out << "\nДвСписок " << dlist.getCount() << "\n";
	for (LNode* cur = dlist.getHead(); cur; cur = cur->next) out << cur->value << " ";

	out << "\nСтек " << (stk.getTop() + 1) << "\n";
	for (int i = 0; i <= stk.getTop(); ++i) out << stk.getElement(i) << " ";

	out << "\nОчередь " << q.getCount() << "\n";
	for (int i = 0; i < q.getCount(); ++i) out << q.getElement(i) << " ";
    
	out << "\nДерево " << tree.getSize() << "\n";
	for (int i = 1; i <= tree.getSize(); ++i) out << tree.getElement(i) << " ";
	out << "\n";
}

void loadFromFile(const string& path) {
	ifstream in(path);
	if (!in) {
		cout << "[Файл не найден, создадим новый: " << path << "]\n";
		return;
	}

	string type;
	int n = 0;

	if (in >> type >> n && type == "Массив") {
		if (n < 0 || n > 1000000) n = 0;
		for (int i = 0; i < n; ++i) { string v; in >> v; arr.pushBack(v); }
	}
	if (in >> type >> n && type == "ОднСписок") {
		if (n < 0 || n > 1000000) n = 0;
		for (int i = 0; i < n; ++i) { string v; in >> v; flist.pushBack(v); }
	}
	if (in >> type >> n && type == "ДвСписок") {
		if (n < 0 || n > 1000000) n = 0;
		for (int i = 0; i < n; ++i) { string v; in >> v; dlist.pushBack(v); }
	}
	if (in >> type >> n && type == "Стек") {
		if (n < 0 || n > 1000000) n = 0;
		for (int i = 0; i < n; ++i) { string v; in >> v; stk.push(v); }
	}
	if (in >> type >> n && type == "Очередь") {
		if (n < 0 || n > 1000000) n = 0;
		for (int i = 0; i < n; ++i) { string v; in >> v; q.push(v); }
	}
	if (in >> type >> n && type == "Дерево") {
		if (n < 0 || n > 1000000) n = 0;
		for (int i = 0; i < n; ++i) { string v; in >> v; tree.insert(v); }
	}
}

void processCommand(const string& query) {
	istringstream iss(query);
	string cmd;
	iss >> cmd;

	if (cmd == "PRINT") {
		string target; iss >> target;
		if (target == "myarr") arr.print();
		else if (target == "mylist") flist.print();
		else if (target == "mydlist") dlist.print();
		else if (target == "mystack") stk.print();
		else if (target == "myqueue") q.print();
		else if (target == "mytree") tree.print();
		return;
	}

	char prefix = cmd[0];

	if (prefix == 'M') {
		string name, v; int i;
		if (cmd == "MPUSH") { iss >> name >> v; arr.pushBack(v); }
		else if (cmd == "MINSERT") { iss >> name >> i >> v; arr.pushAt(i, v); }
		else if (cmd == "MGET") { iss >> name >> i; cout << arr.get(i) << "\n"; }
		else if (cmd == "MSET") { iss >> name >> i >> v; arr.set(i, v); }
		else if (cmd == "MDEL") { iss >> name >> i; arr.removeAt(i); }
		else if (cmd == "MLEN") { iss >> name; cout << arr.length() << "\n"; }
	}
	else if (prefix == 'F') {
		string name, t, v;
		if (cmd == "FADDHEAD") { iss >> name >> v; flist.pushFront(v); }
		else if (cmd == "FADDTAIL") { iss >> name >> v; flist.pushBack(v); }
		else if (cmd == "FADDAFTER") { iss >> name >> t >> v; FNode* n = flist.find(t); if (n) flist.insertAfter(n, v); }
		else if (cmd == "FADDBEFORE") { iss >> name >> t >> v; FNode* n = flist.find(t); if (n) flist.insertBefore(n, v); }
		else if (cmd == "FDELHEAD") { iss >> name; flist.popFront(); }
		else if (cmd == "FDELTAIL") { iss >> name; flist.popBack(); }
		else if (cmd == "FDELAFTER") { iss >> name >> t; FNode* n = flist.find(t); if (n) flist.removeAfter(n); }
		else if (cmd == "FDELBEFORE") { iss >> name >> t; FNode* n = flist.find(t); if (n) flist.removeBefore(n); }
		else if (cmd == "FDELVAL") { iss >> name >> v; flist.removeByValue(v); }
		else if (cmd == "FGET") { int i; iss >> name >> i; cout << flist.getByIndex(i) << "\n"; }
		else if (cmd == "FFIND") { iss >> name >> v; cout << (flist.find(v) ? "TRUE" : "FALSE") << "\n"; }
	}
	else if (prefix == 'L') {
		string name, t, v;
		if (cmd == "LADDHEAD") { iss >> name >> v; dlist.pushFront(v); }
		else if (cmd == "LADDTAIL") { iss >> name >> v; dlist.pushBack(v); }
		else if (cmd == "LADDAFTER") { iss >> name >> t >> v; LNode* n = dlist.find(t); if (n) dlist.insertAfter(n, v); }
		else if (cmd == "LADDBEFORE") { iss >> name >> t >> v; LNode* n = dlist.find(t); if (n) dlist.insertBefore(n, v); }
		else if (cmd == "LDELHEAD") { iss >> name; dlist.popFront(); }
		else if (cmd == "LDELTAIL") { iss >> name; dlist.popBack(); }
		else if (cmd == "LDELAFTER") { iss >> name >> t; LNode* n = dlist.find(t); if (n && n->next) dlist.removeNode(n->next); }
		else if (cmd == "LDELBEFORE") { iss >> name >> t; LNode* n = dlist.find(t); if (n && n->prev) dlist.removeNode(n->prev); }
		else if (cmd == "LDELVAL") { iss >> name >> v; dlist.removeByValue(v); }
		else if (cmd == "LGET") { int i; iss >> name >> i; cout << dlist.getByIndex(i) << "\n"; }
		else if (cmd == "LFIND") { iss >> name >> v; cout << (dlist.find(v) ? "TRUE" : "FALSE") << "\n"; }
		else if (cmd == "LPRINTBACK") { iss >> name; dlist.printBack(); }
	}
	else if (prefix == 'S') {
		string name, v;
		if (cmd == "SPUSH") { iss >> name >> v; stk.push(v); }
		else if (cmd == "SPOP") { iss >> name; string val = stk.peek(); if (stk.pop()) cout << val << "\n"; }
		else if (cmd == "SPEEK") { iss >> name; cout << stk.peek() << "\n"; }
	}
	else if (prefix == 'Q') {
		string name, v;
		if (cmd == "QPUSH") { iss >> name >> v; q.push(v); }
		else if (cmd == "QPOP") { iss >> name; string val = q.peek(); if (q.pop()) cout << val << "\n"; }
		else if (cmd == "QPEEK") { iss >> name; cout << q.peek() << "\n"; }
	}
	else if (prefix == 'T') {
		string name, v;
		if (cmd == "TINSERT") { iss >> name >> v; tree.insert(v); }
		else if (cmd == "TGET") { iss >> name >> v; cout << (tree.search(v) != -1 ? "TRUE" : "FALSE") << "\n"; }
		else if (cmd == "TDEL") { iss >> name >> v; tree.remove(v); }
		else if (cmd == "TCHECK") { iss >> name; cout << (tree.isComplete() ? "TRUE" : "FALSE") << "\n"; }
		else if (cmd == "TPRE") { iss >> name; tree.printPre(); }
		else if (cmd == "TIN") { iss >> name; tree.printIn(); }
		else if (cmd == "TPOST") { iss >> name; tree.printPost(); }
	}
}

int main(int argc, char* argv[]) {
	string filePath;
	vector<string> queries;
	bool replMode = false;

	for (int i = 1; i < argc; ++i) {
		string arg = argv[i];
		if (arg == "--file" && i + 1 < argc) filePath = argv[++i];
		else if (arg == "--query" && i + 1 < argc) queries.push_back(argv[++i]);
		else if (arg == "--repl") replMode = true;
	}

	if (filePath.empty()) {
		filePath = "data.txt";
		cout << "[файл не указан, зпись рповедется сюда: data.txt]\n";
	}

	loadFromFile(filePath);

	if (!queries.empty()) {
		for (auto& qr : queries) processCommand(qr);
		saveToFile(filePath);
	} else if (replMode) {
		string line;
		while (getline(cin, line)) {
			if (line == "EXIT" || line == "exit") break;
			if (!line.empty()) processCommand(line);
		}
		saveToFile(filePath);
	}

	cout << "\n[Программа завершена. Нажмите Enter для выхода.]";
	cin.get();

	return 0;
}
