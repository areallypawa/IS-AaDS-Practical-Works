#pragma once
#include <iostream>

template <typename T>
class DoubleLinkedList {
private:

	struct Node
	{
		T value;
		Node* next;
		Node* back;

	};

	Node* head;

public:
	DoubleLinkedList();
	~DoubleLinkedList();
	void push_back(T value);
	void print_list();
	void push_front(T value);
	void pop_front();
	void pop_back();

};

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() {
	head = nullptr;
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

template <typename T>
void DoubleLinkedList<T>::push_back(T value) {
	Node* newNode = new Node;
	newNode->value = value;
	Node* curr = head;

	if (!curr) {
		head = newNode;
	}
	else {
		while (curr->next) {
			curr = curr->next;
		}
		curr->next = newNode;


	}
	newNode->next = nullptr;
	newNode->back = curr;
}

template <typename T>
void DoubleLinkedList<T>::print_list() {
	Node* curr = head;
	while (curr != nullptr) {
		std::cout << curr->value << ' ';
		curr = curr->next;
	}
}


template <typename T>
void DoubleLinkedList<T>::push_front(T value) {
	Node* newNode = new Node;
	newNode->value = value;

	if (head) { head->back = newNode; }
	newNode->back = nullptr;
	newNode->next = head;
	
	head = newNode;

}


template <typename T>
void DoubleLinkedList<T>::pop_front() {
	if (!head) return;
	Node* curr = head;
	head = head->next;

	if (head) { head->back = nullptr; }

	delete curr;
}

template <typename T>
void DoubleLinkedList<T>::pop_back() {
	if (!head) return;
	if (!head->next) { pop_front(); return; }
	Node* curr = head;
	while (curr->next->next) {
		curr = curr->next;
	}
	Node* p = curr->next;
	curr->next = nullptr;
	delete p;

}
