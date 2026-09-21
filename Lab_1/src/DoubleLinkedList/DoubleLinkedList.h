#pragma once
#include <iostream>
#include <stdexcept>

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
	void print();
	void push_back(const T& value);
	void push_front(const T& value);
	void pop_back();
	void pop_front();

	bool empty();
	size_t size();
	void insert(size_t index, const T& value);
	void erase(size_t index);
	T& at(size_t index);
	int find(const T& value);
	void clear();
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
void DoubleLinkedList<T>::push_back(const T& value) {
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
void DoubleLinkedList<T>::print() {
	Node* curr = head;
	while (curr != nullptr) {
		std::cout << curr->value << ' ';
		curr = curr->next;
	}
}


template <typename T>
void DoubleLinkedList<T>::push_front(const T& value) {
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

template <typename T>
bool DoubleLinkedList<T>::empty() {
	return head == nullptr;
}

template <typename T>
size_t DoubleLinkedList<T>::size() {
	size_t count = 0;
	Node* curr = head;
	while (curr) {
		count++;
		curr = curr->next;
	}
	return count;
}


template <typename T>
void DoubleLinkedList<T>::insert(size_t index, const T& value) {
	if (index == 0) {
		push_front(value);
		return;
	}
	Node* newNode = new Node;
	newNode->value = value;
	Node* curr = head;
	for (size_t i = 0; i < index - 1 && curr != nullptr; ++i) {
		curr = curr->next;
	}
	if (curr == nullptr) {
		delete newNode; 
		return;
	}
	newNode->next = curr->next;
	newNode->back = curr;
	if (curr->next != nullptr) {
		curr->next->back = newNode;
	}
	curr->next = newNode;
}

template <typename T>	
void DoubleLinkedList<T>::erase(size_t index) {
	if (index == 0) {
		pop_front();
		return;
	}
	Node* curr = head;
	for (size_t i = 0; i < index && curr != nullptr; ++i) {
		curr = curr->next;
	}
	if (curr == nullptr) {
		return;
	}
	if (curr->back != nullptr) {
		curr->back->next = curr->next;
	}
	if (curr->next != nullptr) {
		curr->next->back = curr->back;
	}
	delete curr;
}

template <typename T>
T& DoubleLinkedList<T>::at(size_t index) {
	Node* curr = head;
	for (size_t i = 0; i < index && curr != nullptr; ++i) {
		curr = curr->next;
	}
	if (curr == nullptr) {
		throw std::out_of_range("Index out of range");
	}
	return curr->value;
}

template <typename T>
int DoubleLinkedList<T>::find(const T& value) {
	Node* curr = head;
	int index = 0;
	while (curr != nullptr) {
		if (curr->value == value) {
			return index;
		}
		curr = curr->next;
		index++;
	}
	return -1; 
}

template <typename T>
void DoubleLinkedList<T>::clear() {
	Node* curr = head;
	while (curr != nullptr) {
		Node* next = curr->next;
		delete curr;
		curr = next;
	}
	head = nullptr;
}
