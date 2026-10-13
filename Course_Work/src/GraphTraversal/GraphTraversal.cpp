#include "GraphTraversal.h"
#include <iostream>
#include <queue>

void DFS(
    const std::vector<std::string>& vertex_names,
    const std::vector<Edge>& edges,
    int start
) {
    int n = static_cast<int>(vertex_names.size());

    if (start < 0 || start >= n) {
        return;
    }

    std::vector<std::vector<int>> adjacency(n);

    for (const auto& edge : edges) {
        adjacency[edge.u].push_back(edge.v);
        adjacency[edge.v].push_back(edge.u);
    }

    std::vector<bool> visited(n, false);

    auto dfs = [&](auto&& self, int vertex) -> void {
        visited[vertex] = true;
        std::cout << vertex_names[vertex] << ' ';

        for (int neighbor : adjacency[vertex]) {
            if (!visited[neighbor]) {
                self(self, neighbor);
            }
        }
        };

    dfs(dfs, start);
    std::cout << '\n';
}

void BFS(
    const std::vector<std::string>& vertex_names,
    const std::vector<Edge>& edges,
    int start
) {
    int n = static_cast<int>(vertex_names.size());

    if (start < 0 || start >= n) {
        return;
    }

    std::vector<std::vector<int>> adjacency(n);

    for (const auto& edge : edges) {
        adjacency[edge.u].push_back(edge.v);
        adjacency[edge.v].push_back(edge.u);
    }

    std::vector<bool> visited(n, false);
    std::queue<int> queue;

    visited[start] = true;
    queue.push(start);

    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();

        std::cout << vertex_names[vertex] << ' ';

        for (int neighbor : adjacency[vertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }

    std::cout << '\n';
}