/*
 * linkedList.h
 *
 *  Created on: Apr 28, 2020
 *      Author: yaraa
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_


struct node
{
	int data;
	node * nextNode;
};

void printLinkedList(node * head);
node * pushNode (node* head, int data);
node * insertNode (node * head, int position, int data);
node * removeNode (node * head, int position);
node * loopDetection (node * head);


#endif /* LINKEDLIST_H_ */
