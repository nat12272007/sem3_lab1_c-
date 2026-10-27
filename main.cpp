#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "data_structures.h"

using namespace std;

//глобальные экземпляры структур
DynamicArray arr;
ForwardList flist;
DoublyList dlist;
Stack stk;
Queue q;
CompleteBinaryTree tree;

void saveToFile(const string& path) {
	ofstream out(path);
	if (!out) return;

	out << "Массив " << arr.size << "\n";
	for (int i = 0; i < arr.size; ++i) out << arr.data[i] << " ";
	out << "\nОднСписок " << flist.count << "\n";
	for (FNode* cur = flist.head; cur; cur = cur->next) out << cur->value << " ";
	out << "\nДвСписок " << dlist.count << "\n";
	for (LNode* cur = dlist.head; cur; cur = cur->next) out << cur->value << " ";
	out << "\nСтек " << (stk.top + 1) << "\n";
	for (int i = 0; i <= stk.top; ++i) out << stk.data[i] << " ";
	out << "\nОчередь " << q.count << "\n";
	for (int i = 0; i < q.count; ++i) out << q.data[(q.frontIdx + i) % q.capacity] << " ";
	out << "\nДерево " << tree.size << "\n";
	for (int i = 1; i <= tree.size; ++i) out << tree.tree[i] << " ";
	out << "\n";
}

void loadFromFile(const string& path) {
	ifstream in(path);
	if (!in) {
		cout << "[Файл не найден, создается новый: " << path << "]\n";
		return;
	}

	string type;
	int n = 0;

	if (in >> type >> n && type == "Массив") {
        	if (n < 0 || n > 1000000) n = 0;
		arr.init(max(4, n));
		for (int i = 0; i < n; ++i) in >> arr.data[i];
		arr.size = n;
	}
    
	if (in >> type >> n && type == "ОднСписок") {
		if (n < 0 || n > 1000000) n = 0;
		for (int i = 0; i < n; ++i) { int v; in >> v; flist.pushBack(v); }
	}
    
	if (in >> type >> n && type == "ДвСписок") {
		if (n < 0 || n > 1000000) n = 0;
		for (int i = 0; i < n; ++i) { int v; in >> v; dlist.pushBack(v); }
	}
    
	if (in >> type >> n && type == "Стек") {
		if (n < 0 || n > 1000000) n = 0;
		stk.init(max(4, n));
		for (int i = 0; i < n; ++i) { int v; in >> v; stk.push(v); }
	}
    
	if (in >> type >> n && type == "Очередь") {
		if (n < 0 || n > 1000000) n = 0;
		q.init(max(4, n));
		for (int i = 0; i < n; ++i) { int v; in >> v; q.push(v); }
	}
    
	if (in >> type >> n && type == "Дерево") {
		if (n < 0 || n > 1000000) n = 0;
		tree.init(max(4, n));
		for (int i = 0; i < n; ++i) { int v; in >> v; tree.insert(v); }
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

//a.массив
	if (prefix == 'M') {
		string name;
		if (cmd == "MPUSH") { int v = 0; iss >> name >> v; arr.pushBack(v); }
		else if (cmd == "MINSERT") { int i = 0, v = 0; iss >> name >> i >> v; arr.pushAt(i, v); }
		else if (cmd == "MGET") { int i = 0; iss >> name >> i; cout << arr.get(i) << "\n"; }
		else if (cmd == "MSET") { int i = 0, v = 0; iss >> name >> i >> v; arr.set(i, v); }
		else if (cmd == "MDEL") { int i = 0; iss >> name >> i; arr.removeAt(i); }
		else if (cmd == "MLEN") { iss >> name; cout << arr.length() << "\n"; }
	}
    
//b.односвязный список
	else if (prefix == 'F') {
		string name;
		if (cmd == "FADDHEAD") { int v = 0; iss >> name >> v; flist.pushFront(v); }
		else if (cmd == "FADDTAIL") { int v = 0; iss >> name >> v; flist.pushBack(v); }
		else if (cmd == "FADDAFTER") { int t = 0, v = 0; iss >> name >> t >> v; FNode* n = flist.find(t); if (n) flist.insertAfter(n, v); }
		else if (cmd == "FADDBEFORE") { int t = 0, v = 0; iss >> name >> t >> v; FNode* n = flist.find(t); if (n) flist.insertBefore(n, v); }
		else if (cmd == "FDELHEAD") { iss >> name; flist.popFront(); }
		else if (cmd == "FDELTAIL") { iss >> name; flist.popBack(); }
		else if (cmd == "FDELAFTER") { int t = 0; iss >> name >> t; FNode* n = flist.find(t); if (n) flist.removeAfter(n); }
		else if (cmd == "FDELBEFORE") { int t = 0; iss >> name >> t; FNode* n = flist.find(t); if (n) flist.removeBefore(n); }
		else if (cmd == "FDELVAL") { int v = 0; iss >> name >> v; flist.removeByValue(v); }
		else if (cmd == "FGET") { int i = 0; iss >> name >> i; cout << flist.getByIndex(i) << "\n"; }
		else if (cmd == "FFIND") { int v = 0; iss >> name >> v; cout << (flist.find(v) ? "TRUE" : "FALSE") << "\n"; }
	}
    
//c.двусвязный список
	else if (prefix == 'L') {
		string name;
		if (cmd == "LADDHEAD") { int v = 0; iss >> name >> v; dlist.pushFront(v); }
		else if (cmd == "LADDTAIL") { int v = 0; iss >> name >> v; dlist.pushBack(v); }
		else if (cmd == "LADDAFTER") { int t = 0, v = 0; iss >> name >> t >> v; LNode* n = dlist.find(t); if (n) dlist.insertAfter(n, v); }
		else if (cmd == "LADDBEFORE") { int t = 0, v = 0; iss >> name >> t >> v; LNode* n = dlist.find(t); if (n) dlist.insertBefore(n, v); }
		else if (cmd == "LDELHEAD") { iss >> name; dlist.popFront(); }
		else if (cmd == "LDELTAIL") { iss >> name; dlist.popBack(); }
		else if (cmd == "LDELAFTER") { int t = 0; iss >> name >> t; LNode* n = dlist.find(t); if (n && n->next) dlist.removeNode(n->next); }
		else if (cmd == "LDELBEFORE") { int t = 0; iss >> name >> t; LNode* n = dlist.find(t); if (n && n->prev) dlist.removeNode(n->prev); }
		else if (cmd == "LDELVAL") { int v = 0; iss >> name >> v; dlist.removeByValue(v); }
		else if (cmd == "LGET") { int i = 0; iss >> name >> i; cout << dlist.getByIndex(i) << "\n"; }
		else if (cmd == "LFIND") { int v = 0; iss >> name >> v; cout << (dlist.find(v) ? "TRUE" : "FALSE") << "\n"; }
		else if (cmd == "LPRINTBACK") { 
			iss >> name; cout << "[";
			LNode* cur = dlist.tail; bool first = true;
			while (cur) { if (!first) cout << " <-> "; cout << cur->value; cur = cur->prev; first = false; }
			cout << "]\n"; 
		}
	}

//d.стек
	else if (prefix == 'S') {
		string name;
		if (cmd == "SPUSH") { int v = 0; iss >> name >> v; stk.push(v); }
		else if (cmd == "SPOP") { iss >> name; int v = stk.peek(); if (stk.pop()) cout << v << "\n"; }
		else if (cmd == "SPEEK") { iss >> name; cout << stk.peek() << "\n"; }
	}

//e.очередь
	else if (prefix == 'Q') {
		string name;
		if (cmd == "QPUSH") { int v = 0; iss >> name >> v; q.push(v); }
		else if (cmd == "QPOP") { iss >> name; int v = q.peek(); if (q.pop()) cout << v << "\n"; }
		else if (cmd == "QPEEK") { iss >> name; cout << q.peek() << "\n"; }
	}
    
//f.дерево
	else if (prefix == 'T') {
		string name;
		if (cmd == "TINSERT") { int v = 0; iss >> name >> v; tree.insert(v); }
		else if (cmd == "TGET") { int v = 0; iss >> name >> v; cout << (tree.search(v) != -1 ? "TRUE" : "FALSE") << "\n"; }
		else if (cmd == "TDEL") { int v = 0; iss >> name >> v; tree.remove(v); }
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
		cout << "[Файл не указан, все звпишеться в  data.txt]\n";
	}

	arr.init(); stk.init(); q.init(); tree.init();
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
