#pragma once
#include <vector>

class DSU {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    explicit DSU(int n);

    int find(int i);
    bool unite(int i, int j);
};