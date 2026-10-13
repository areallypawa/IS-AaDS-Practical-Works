#include "QuickSort.h"
#include <utility>

int partitionEdges(std::vector<Edge>& edges, int low, int high) {
    int pivot = edges[high].weight;
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (edges[j].weight <= pivot) {
            ++i;
            std::swap(edges[i], edges[j]);
        }
    }

    std::swap(edges[i + 1], edges[high]);
    return i + 1;
}

void quickSortEdges(std::vector<Edge>& edges, int low, int high) {
    if (low >= high) {
        return;
    }

    int pi = partitionEdges(edges, low, high);

    quickSortEdges(edges, low, pi - 1);
    quickSortEdges(edges, pi + 1, high);
}

bool compareEdgesByName(const Edge& a, const Edge& b) {
    if (a.u_name != b.u_name) {
        return a.u_name < b.u_name;
    }

    return a.v_name < b.v_name;
}

int partitionByName(std::vector<Edge>& edges, int low, int high) {
    Edge pivot = edges[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (compareEdgesByName(edges[j], pivot)) {
            ++i;
            std::swap(edges[i], edges[j]);
        }
    }

    std::swap(edges[i + 1], edges[high]);
    return i + 1;
}

void quickSortByName(std::vector<Edge>& edges, int low, int high) {
    if (low >= high) {
        return;
    }

    int pi = partitionByName(edges, low, high);

    quickSortByName(edges, low, pi - 1);
    quickSortByName(edges, pi + 1, high);
}