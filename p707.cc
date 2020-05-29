#include "common.h"
class MyLinkedList {
public:
	/** Initialize your data structure here. */
	MyLinkedList() {
		size = 0;
		head = tail = nullptr;
	}

	/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
	// index-th is 0-based index
	int get(int index) {
		if (index < 0 || index >= size) {
			return -1;
		}
		if (index < size - 1 - index) {
			MyListNode* Prev = tail;
			while (index > 0) {
				Prev = Prev->next;
				--index;
			}
			return Prev->next->val;
		}
		else {
			index = size - 1 - index;
			MyListNode* Next = head;
			while (index > 0) {
				Next = Next->prev;
				--index;
			}
			return Next->prev->val;
		}
	}

	/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
	void addAtHead(int val) {
		if (size == 0) {
			tail = head = new MyListNode(val);
			tail->next = head;
			head->prev = tail;
		}
		else {
			MyListNode* node = new MyListNode(val);
			// tail<->node<->head->...
			node->next = head;
			head->prev = node;
			tail->next = node;
			node->prev = tail;
			head = node;
		}
		size++;
	}

	/** Append a node of value val to the last element of the linked list. */
	void addAtTail(int val) {
		if (size == 0) {
			tail = head = new MyListNode(val);
			tail->next = head;
			head->prev = tail;
		}
		else {
			MyListNode* node = new MyListNode(val);
			// tail<->node<->head->...
			node->next = head;
			head->prev = node;
			tail->next = node;
			node->prev = tail;
			tail = node;
		}
		size++;
	}

	/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
	void addAtIndex(int index, int val) {
		if (index < 0 || index > size) { // fuck it
			return;
		}
		if (index == size) {
			addAtTail(val);
		}
		else {
			MyListNode* node = new MyListNode(val);
		if (index < size - 1 - index) {
				MyListNode* Prev = tail;
				while (index > 0) {
					Prev = Prev->next;
					--index;
				}
				// Prev<->node<->xx
				MyListNode* Next = Prev->next;
				node->next = Next;
				node->prev = Prev;
				Prev->next = node;
				Next->prev = node;
			} else {
				index = size - 1 - index;
				MyListNode* Next = head;
				while (index > 0) {
					Next = Next->prev;
					--index;
				}
				Next = Next->prev; // ith Node
				MyListNode* Prev = Next->prev;
				node->next = Next;
				node->prev = Prev;
				Prev->next = node;
				Next->prev = node;
			}
			// tail is not changed;
			head = tail->next; // for index == 0
			size++;
		}
	}

	/** Delete the index-th node in the linked list, if the index is valid. */
	void deleteAtIndex(int index) {
		if (index < 0 || index >= size) {
			return;
		}
		if (size == 1) {
			delete head;
			head = tail = nullptr;
			size = 0;
			return;
		} else {
			int loc = index;

			if (index < size - 1 - index) {
				MyListNode* Prev = tail;
				while (index > 0) {
					Prev = Prev->next;
					index--;
				}
				MyListNode* node = Prev->next;
				MyListNode* Next = node->next;
				Next->prev = Prev;
				Prev->next = Next;
				delete node;
			}
			else {
				index = size - 1 - index;
				MyListNode* Next = head;
				while (index > 0) {
					Next = Next->prev;
					index--;
				}
				// Next is at ith->next
				MyListNode* node = Next->prev;
				node->prev->next = Next;
				Next->prev = node->prev;
				delete node;
			}
			if (loc == 0) {
				head = tail->next;
			}
			else if (loc == size - 1) {
				tail = head->prev;
			}
			else {
				// no change
			}
			size--;
		}
	}
	void print()
	{
		if (head) {
			int len = size;
			MyListNode* c = head;
			while (len-- > 0) {
				cout << c->val << " ";
				c = c->next;
			}
			cout << endl;
		}
	}

private:
	struct MyListNode {
		int val;
		MyListNode* next;
		MyListNode* prev;
		MyListNode(int v) : val(v), next(nullptr), prev(nullptr)
		{
		}
	};
	int size;
	MyListNode* head;
	MyListNode* tail;
};


int main() {


	return 0;
}
