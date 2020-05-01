/*
 * linkedList.cpp
 *
 *  Created on: Apr 28, 2020
 *      Author: yaraa
 */

#include <bits/stdc++.h>
#include "linkedList.h"
using namespace std;



/* print linked list */
void printLinkedList(node * head)
{
	node * temp = head;
	while(temp != NULL)
	{
		cout << temp->data << endl;
		temp = temp->nextNode;
	}
}

/* ===================================================================================*/

/* To create a new Node and insert it at the beginning of the linked list, where head = NULL
 * at first and will be updated with the last added node */
node * pushNode (node* head, int data)
{
	node * newNode = new node();
	newNode->nextNode = head;
	newNode->data = data;

	return newNode;
}

/* ===================================================================================*/

/* insert a node in a certain position */
/* O(position) */
node * insertNode (node * head, int position, int data)
{

	if(position == 0)
		return pushNode(head,data);

	node * newNode = new node();
	node * temp = head;

	for(int i = 0; i < position; i++)
	{
		if(i == position - 1)
		{
			/* When reaching the node just before the position */
			/* The next node should be replaced with the new node
			 * and becomes the next node of the new node */
			node * tempPtr = temp->nextNode;
			temp->nextNode = newNode;
			newNode->nextNode = tempPtr;
			newNode->data = data;
		}
		else
		{
			temp = temp->nextNode;
		}
	}

	return head;
}

/* ===================================================================================*/
/* remove a node from a certain position */
node * removeNode (node * head, int position)
{
	node * temp = head;

	if(position == 0)
	{
		/* remove the head and move it to the next node */
		head = head->nextNode;
		delete temp;
		return head;
	}

	node * previousNode;
	for(int i = 0; i < position; i++)
	{
		/* I will need to:
		 * 1 - make the previous node points to the next node
		 * 2 - remove the node at the specific position
		 */
		if(i == position - 1)
		{
			previousNode = temp;
			temp = temp->nextNode;
			previousNode->nextNode = temp->nextNode;
			delete temp;
		}
		else
		{
			temp = temp->nextNode;
		}
	}

	return head;

}

/* ===================================================================*/

/* used to detect the presence of a loop in a linked list using the runner technique
 * (fast and slow pointers) */
/* I will need to:
 * 1 - detect the existence of a loop: when the fast and slow pointers meet
 * 2 - return the node that caused the loop:
 */
node * loopDetection (node * head)
{
	node * slowPtr = head;
	node * fastPtr = head;
	bool firstTime = true;

	/* break when detecting a loop, otherwise the fast pointer will reach NULL */
	while(fastPtr != NULL && fastPtr->nextNode != NULL)
	{
		if(fastPtr == slowPtr && firstTime == false)
			break;
		slowPtr = slowPtr->nextNode;
		fastPtr = (fastPtr->nextNode)->nextNode;
		firstTime = false;
	}

	/* the fast pointer now has the value of the meeting point.
	 * We will need to set the slow pointer as the head and loop until both pointers
	 * are equal (which is the point of intersection)
	 * If no loop available, the function will return NULL. */
	if(fastPtr == NULL) return NULL;
	slowPtr = head;
	while(fastPtr != slowPtr)
	{
		slowPtr = slowPtr->nextNode;
		fastPtr = fastPtr->nextNode;
	}

	return slowPtr;
}

/* ========================================================================*/

/* used to find the intersection of two linked lists */
/* this algorithm uses a map to store the pointer of each node and to count each pointer
 * if a counter is greater than 1, then it is a point of intersection */

node * findIntersection(node * head1, node * head2)
{
	node * temp1 = head1;
	node * temp2 = head2;
	map <node*,int> nodesCount;

	while(temp1 != NULL && temp2 != NULL)
	{
		nodesCount[temp1]++;
		if(nodesCount[temp1] > 1)
			return temp1;
		nodesCount[temp2]++;
		if(nodesCount[temp2] > 1)
			return temp2;

		temp1 = temp1->nextNode;
		temp2 = temp2->nextNode;
	}

	return NULL;
}

/*=====================================================================*/
/* this algorithm is used to find the middle node of a linked list.
 * It uses the runner technique */

node * findLLMiddle(node * head)
{
	node * slowPtr = head;
	node * fastPtr = head;

	while((fastPtr != NULL) && (fastPtr->nextNode != NULL))
	{
		slowPtr = slowPtr->nextNode;
		fastPtr = (fastPtr->nextNode)->nextNode;
	}

	return slowPtr;
}

bool linkedListPalindromeCheck (node * head)
{
	// Get Length and push elements to a vector
	node * temp = head;
	vector<int> elements;
	while(temp != NULL)
	{
		elements.push_back(temp->data);
		temp = temp->nextNode;
	}

	unsigned int llSize = elements.size();
	unsigned int middle;

	if(llSize % 2 != 0)
	{
		middle = llSize/2 + 1;
	}
	else
	{
		middle = llSize/2;
	}

	for(unsigned int i = 0; i < llSize/2; i++)
	{
		if(elements[llSize/2 - 1 - i] != elements[i+middle])
			return false;
	}

	return true;
}

node * linkedListSum (node * head1, node * head2)
{
	node * headSum = new node();
	node * temp1 = head1;
	node * temp2 = head2;
	int multiplier1 = 1;
	int multiplier2 = 1;
	int number1 = 0;
	int number2 = 0;

	while(temp1->nextNode != NULL || temp2->nextNode != NULL)
	{
		if(temp1->nextNode != NULL)
		{
			number1 += (temp1->data)*multiplier1;
			multiplier1 = multiplier1*10;
			temp1 = temp1->nextNode;

			if(temp1->nextNode == NULL)
			{
				number1 += (temp1->data)*multiplier1;
			}
		}

		if(temp2->nextNode != NULL)
		{
			number2 += (temp2->data)*multiplier2;
			multiplier2 = multiplier2*10;
			temp2 = temp2->nextNode;

			if(temp2->nextNode == NULL)
			{
				number2 += (temp2->data)*multiplier1;
			}
		}
	}

	int sum = number1 + number2;
	int number = 0;
	int dividor = 10;
	temp1 = headSum;
	do
	{
		number = sum % dividor;
		sum = sum - number;
		number = number /(dividor/10);
		dividor *= 10;

		temp1->data = number;
		if(sum != 0)
		{
			temp1->nextNode = new node();
			temp1 = temp1->nextNode;
		}
		else
		{
			temp1->nextNode = NULL;
		}


	}
	while(sum > 0);

	return headSum;
}

node * linkedListPartition (node * head, int x)
{
	node * temp = head;

	node * leftHead = new node();
	node * rightHead = new node();

	node * leftTemp = leftHead;
	node * rightTemp = rightHead;

	bool firstPathL = true;
	bool firstPathR = true;


	while(temp->nextNode != NULL)
	{
		if(temp->data < x)
		{
			if(leftTemp == leftHead && firstPathL == true)
			{
				leftTemp->data = temp->data;
				leftTemp->nextNode = temp->nextNode;
				firstPathL = false;
				delete temp;
				temp = leftTemp->nextNode;
			}
			else
			{
				if(firstPathL == false)
				{
					firstPathL = true;
					leftHead->nextNode = temp;
					leftTemp = temp;
				}
				else
				{
					leftTemp->nextNode = temp;
					leftTemp = temp;
				}
				temp = temp->nextNode;
			}

		}
		else if (temp->data >= x)
		{
			if(rightTemp == rightHead && firstPathR == true)
			{
				rightTemp->data = temp->data;
				rightTemp->nextNode = temp->nextNode;
				firstPathR = false;
				delete temp;
				temp = rightTemp->nextNode;
			}
			else
			{
				if(firstPathR == false)
				{
					firstPathR = true;
					rightHead->nextNode = temp;
					rightTemp = temp;
				}
				else
				{
					rightTemp->nextNode = temp;
					rightTemp = temp;
				}

				temp = temp->nextNode;
			}
		}
	}

	if(temp->data < x)
	{
		leftTemp->nextNode = temp;
		leftTemp = temp;
	}
	else
	{
		leftTemp->nextNode = temp;
		leftTemp = temp;
	}

	leftTemp->nextNode = rightHead;
	rightTemp->nextNode = NULL;

	return leftHead;

}


int printKthToLast (node * head, unsigned int position)
{
	node * temp = head;
	if(temp->nextNode == NULL)
		return -1;
	unsigned int countingPosition = 0;

	while(temp->nextNode != NULL)
	{
		if(countingPosition >= position)
			cout << temp->data << "\t";

		temp = temp->nextNode;

		if(temp->nextNode == NULL  && countingPosition >= position)
			cout << temp->data;

		countingPosition++;
	}
	cout << endl;
	return 0;

}


void deleteDups (node * head)
{
	node * tempNode = head;
	map<int,int> dups;
	unsigned int positionCounter = 0;
	while(tempNode->nextNode != NULL)
	{
		dups[tempNode->data]++;
		if(dups[tempNode->data] != 1)
		{
			tempNode = tempNode->nextNode;
			removeNode(head,positionCounter);
			positionCounter--;
		}
		else
		{
			tempNode = tempNode->nextNode;
		}

		positionCounter++;

		if(tempNode->nextNode == NULL)
		{
			dups[tempNode->data]++;
			if(dups[tempNode->data] != 1)
			{
				removeNode(head,positionCounter);
				tempNode->nextNode = NULL;
			}
		}
	}
}


