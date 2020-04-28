//============================================================================
// Name        : CCI_Cpp.cpp
// Author      : Yara AMRALLAH
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#include <iostream>
#include "linkedList.h"
using namespace std;

int main() {
	node * head = NULL;
	node * node1 = pushNode(head, (int)4);
	node * node2 = pushNode(node1, (int)5);

	cout << "original linked list:\n";
	printLinkedList(node2);

	/*============================================================*/
	node * node1_2 = insertNode(node2, 1, 1);

	cout << "linked list after insertion of 1 in first position:\n";
	printLinkedList(node2);

	/*============================================================*/
	node2 = removeNode(node2, 1);

	cout << "linked list after removal of 1 in first position:\n";
	printLinkedList(node2);

	return 0;
}
