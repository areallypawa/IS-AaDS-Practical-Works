#pragma once
#include <vector>
#include "../Edge/Edge.h"

int partitionEdges(std::vector<Edge>& edges, int low, int high);
void quickSortEdges(std::vector<Edge>& edges, int low, int high);

bool compareEdgesByName(const Edge& a, const Edge& b);

int partitionByName(std::vector<Edge>& edges, int low, int high);
void quickSortByName(std::vector<Edge>& edges, int low, int high);