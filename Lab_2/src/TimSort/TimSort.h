#pragma once

#include <iostream>
#include <string>

class TimSort {
private:
    struct Run {
        int start;
        int length;
    };

    int* arr;
    int size;

    bool showSteps = true;

    void printStep(const std::string& message);
    void printRange(int left, int right);

    Run* runs;
    int runCount;
    int runCapacity;

    static const int MIN_MERGE = 32;
    static const int GALLOP_THRESHOLD = 7;

    void insertionSort(int left, int right);
    int getMinRun(int n);
    int findRun(int start);

    void pushRun(int start, int length);

    void mergeCollapse();
    void mergeForceCollapse();

    void mergeAt(int index);
    void merge(int left, int middle, int right);

    int gallopRight(
        int value,
        int* temp,
        int length
    );

    int gallopLeft(
        int value,
        int* temp,
        int length
    );

    void mergeWithGalloping(
        int left,
        int middle,
        int right
    );

    void extendRun(
        int start,
        int currentLength,
        int targetLength
    );

    void printArray() const;

public:
    TimSort(int* array, int n);
    ~TimSort();
        
    void sort();

    void print() const;
};
