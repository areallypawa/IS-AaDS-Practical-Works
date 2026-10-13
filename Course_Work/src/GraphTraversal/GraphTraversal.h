#pragma once

#include <string>
#include <vector>
#include "../Edge/Edge.h"

void DFS(
    const std::vector<std::string>& vertex_names,
    const std::vector<Edge>& edges,
    int start
);

void BFS(
    const std::vector<std::string>& vertex_names,
    const std::vector<Edge>& edges,
    int start
);