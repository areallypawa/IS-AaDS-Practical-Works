#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class DynamicArray {
private:

    T* data;
    size_t capacity;
    size_t count;

    void resize(size_t newCapacity);

public:
    DynamicArray();
    ~DynamicArray();

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
DynamicArray<T>::DynamicArray() {
    capacity = 4;
    count = 0;
    data = new T[capacity];
}


template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}


template <typename T>
void DynamicArray<T>::resize(size_t newCapacity) {

    T* newData = new T[newCapacity];

    for (size_t i = 0; i < count; i++) {
        newData[i] = data[i];
    }

    delete[] data;

    data = newData;
    capacity = newCapacity;
}


template <typename T>
void DynamicArray<T>::print() {

    for (size_t i = 0; i < count; i++) {
        std::cout << data[i] << ' ';
    }

    std::cout << '\n';
}


template <typename T>
void DynamicArray<T>::push_back(const T& value) {

    if (count == capacity) {
        resize(capacity * 2);
    }

    data[count] = value;
    count++;
}


template <typename T>
void DynamicArray<T>::push_front(const T& value) {

    if (count == capacity) {
        resize(capacity * 2);
    }

    for (size_t i = count; i > 0; i--) {
        data[i] = data[i - 1];
    }

    data[0] = value;
    count++;
}


template <typename T>
void DynamicArray<T>::pop_back() {

    if (empty()) {
        return;
    }

    count--;
}


template <typename T>
void DynamicArray<T>::pop_front() {

    if (empty()) {
        return;
    }

    for (size_t i = 0; i < count - 1; i++) {
        data[i] = data[i + 1];
    }

    count--;
}


template <typename T>
bool DynamicArray<T>::empty() {
    return count == 0;
}


template <typename T>
size_t DynamicArray<T>::size() {
    return count;
}


template <typename T>
void DynamicArray<T>::insert(size_t index, const T& value) {

    if (index > count) {
        throw std::out_of_range("Index out of range");
    }

    if (count == capacity) {
        resize(capacity * 2);
    }

    for (size_t i = count; i > index; i--) {
        data[i] = data[i - 1];
    }

    data[index] = value;
    count++;
}


template <typename T>
void DynamicArray<T>::erase(size_t index) {

    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }

    for (size_t i = index; i < count - 1; i++) {
        data[i] = data[i + 1];
    }

    count--;
}


template <typename T>
T& DynamicArray<T>::at(size_t index) {

    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }

    return data[index];
}


template <typename T>
int DynamicArray<T>::find(const T& value) {

    for (size_t i = 0; i < count; i++) {

        if (data[i] == value) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

template <typename T>
void DynamicArray<T>::clear() {
    count = 0;
}