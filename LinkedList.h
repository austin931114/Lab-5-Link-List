#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "LinkedListInterface.h"
using namespace std;

template <class T>

class LinkedList: public LinkedListInterface<T> {

private:
	struct Node {
	 T data; // The data we are storing
	 Node* next; // A pointer to the next Node 
	 Node(const T& the_data, Node* next_val = NULL) :
	   data(the_data) {next = next_val;}
	};
	
	Node *mylist;
	int num_items;

public:

	LinkedList(void) {
		mylist = NULL;
		num_items = 0;
	};
	virtual ~LinkedList(void) {};

	virtual int match(T value) {
		int temp = 0;
		for(Node *ptr =mylist; ptr != NULL; ptr = ptr->next){
			if (ptr->data == value) {
				temp = 99999;
			}
		}
		return temp;
	}
	/*
	insertHead

	A node with the given value should be inserted at the beginning of the list.

	Do not allow duplicate values in the list.
	*/
	virtual void insertHead(T value) {
		int chechMatch = match(value);
		if (chechMatch == 99999) {
			return;
		}
		else if (chechMatch == 0) {
			Node *ptr = mylist;
			mylist = new Node(value);
			mylist->next = ptr;
			num_items++;
			// delete mylist;
			cout << "In insertHead" << endl;
		}
	};

	/*
	insertTail

	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	virtual void insertTail(T value){
		int chechMatch = match(value);
		if (chechMatch == 99999) {
			return;
		}
		else if (chechMatch == 0) {
			Node *ptr = mylist;
			cout << "In insertTail" << endl;
			if(mylist == NULL){
				mylist = new Node(value, NULL);
			} 
			else {
				while(ptr != NULL){
					// cout << ptr<<" data "<<ptr->data<<" next "<<ptr->next<<endl;
					if(ptr->next == NULL) {
						ptr->next = new Node(value, NULL);
						break;
					} 
					else {
						ptr = ptr->next;
					}
				}
			}
			num_items++;
		}

	};

	/*
	insertAfter

	A node with the given value should be inserted immediately after the
	node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	virtual void insertAfter(T value, T insertionNode){
		int chechMatch = match(value);
		if (chechMatch == 99999) {
			return;
		}
		else if (chechMatch == 0) {
			cout << "In insertAfter" << endl;
			Node *ptr = mylist;

			if(num_items == 0) {
				cout << "insertAfter error" << endl;
				return;
			}
			// check the 1st value
			if (ptr->data == insertionNode) {
				// cout << "test" << endl;
				Node *newNode = new Node(value,ptr->next);
				// set ptr's node to the "new" node
				ptr->next = newNode;
				num_items++;
				return;
			}
			else {
				// check if next node exist
				while(ptr->next != NULL && ptr->data != insertionNode){
					// cout << ptr<<" data "<<ptr->data<<" next "<<ptr->next<<endl;
					if (ptr->next->data == insertionNode) {
						ptr = ptr->next;
						// create a new node with "value" and point to the node next to ptr
						Node *newNode = new Node(value,ptr->next);
						// set ptr's node to the "new" node
						ptr->next = newNode;
						num_items++;
						break;
					}
					else {
						ptr = ptr->next;
					}
				}
			}
		}
	};

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	virtual void remove(T value) {
		cout << "In remove" << endl;
		Node *ptr1 = mylist;

		if (num_items == 0) {
			cout << "remove error" << endl;
			return;
		}
		if (ptr1->data == value) {
			// cout << "test " << endl;
			Node *current = mylist;
			mylist = mylist->next;
			delete current;
			num_items--;
			return;
		}

		else {
			Node *ptr = mylist;
			while(ptr->next != NULL && ptr->data != value){
				// cout <<" data  next "<<endl;
				if (ptr->next->data == value) {
					// cout << "test" << endl;
					Node *current = ptr->next;
		  		ptr->next = ptr->next->next;
		  		delete current;
					num_items--;
					return;
				}
				// if (ptr == NULL) {
				// 	cout << "doesnt exist" << endl;
				// 	throw out_of_range("remove Error");
				// 	break;
				// } 
				else {
					// cout << "test2" << endl;
					ptr = ptr->next;
				}
			}
		}
	};

	/*
	clear

	Remove all nodes from the list.
	*/
	virtual void clear(){
		if (num_items > 0) {
			do {
				Node *current = mylist;
				mylist = mylist->next;
				delete current;
				num_items--;
			}while (num_items != 0);			
		}
	};

	/*
	at

	Returns the value of the node at the given index. The list begins at
	index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	virtual T at(int index){
		if (index >= num_items || index < 0) {
			throw std::out_of_range("at Error");
		}

		T myValue;
		Node *ptr = mylist;
		while (index != -1) {
			myValue = ptr->data;
			ptr = ptr->next;
			index--;
		}
		return(myValue);
	};

	/*
	size

	Returns the number of nodes in the list.
	*/
	virtual int size(){
		return(num_items);
	};

	/*
	toString
	
	Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
	There should be no trailing space at the end of the string

	For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
	"1 2 3 4 5"
	*/
	virtual string toString(){
		// if (num_items == 0) {
		// 	throw out_of_range("toString Error");
		// }
		stringstream ss;
		for(Node *ptr =mylist; ptr != NULL; ptr = ptr->next){
			if (ptr->next == NULL) {
				ss << ptr->data;
			}
			else {
				ss << ptr->data << " ";
			}
		}
		return(ss.str());
	};

};
