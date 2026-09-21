#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class Stack {
private:

    struct Node {
        T value;
        Node* next;

    };

    Node* head;
    size_t count;

public:
    Stack();
    ~Stack();

    void print();
    void push(const T& value);
    void pop();

    T& top();
    bool empty();
    size_t size();
    void clear();
};


template <typename T>
Stack<T>::Stack() {
    head = nullptr;
    count = 0;
}


template <typename T>
Stack<T>::~Stack() {
    clear();
}


template <typename T>
void Stack<T>::print() {

    Node* current = head;

    while (current != nullptr) {
        std::cout << current->value << ' ';
        current = current->next;
    }

    std::cout << '\n';
}


template <typename T>
void Stack<T>::push(const T& value) {

    Node* newNode = new Node(value);

    newNode->next = head;
    head = newNode;

    count++;
}


template <typename T>
void Stack<T>::pop() {

    if (empty()) {
        return;
    }

    Node* current = head;

    head = head->next;

    delete current;

    count--;
}


template <typename T>
T& Stack<T>::top() {

    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }

    return head->value;
}


template <typename T>
bool Stack<T>::empty() {
    return head == nullptr;
}


template <typename T>
size_t Stack<T>::size() {
    return count;
}


template <typename T>
void Stack<T>::clear() {

    while (head != nullptr) {

        Node* current = head;

        head = head->next;

        delete current;
    }

    count = 0;
}