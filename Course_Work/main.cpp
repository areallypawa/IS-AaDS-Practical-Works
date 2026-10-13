#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <filesystem>
#include <limits>
#include <windows.h>

#include "src/menu/menu.h"
#include "src/Edge/Edge.h"
#include "src/DSU/DSU.h"
#include "src/QuickSort/QuickSort.h"
#include "src/GraphTraversal/GraphTraversal.h"

const std::string DEFAULT_FILENAME =
R"(C:\Users\neiln\source\repos\areallypawa\IS-AaDS-Practical-Works\Course_Work\src\input\input.txt)";

std::string filename = DEFAULT_FILENAME;

std::vector<std::string> vertex_names;
std::vector<Edge> edges;

bool graph_loaded = false;


// ============================================================
//                    ЗАГРУЗКА ГРАФА
// ============================================================

void load_graph() {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл: "
            << filename << '\n';

        std::cerr << "Рабочая директория: "
            << std::filesystem::current_path().string()
            << '\n';

        graph_loaded = false;
        return;
    }

    std::string header_line;

    while (std::getline(file, header_line)) {
        if (!header_line.empty()) {
            break;
        }
    }

    if (!file && header_line.empty()) {
        std::cerr << "Ошибка: файл пуст или заголовок отсутствует.\n";
        graph_loaded = false;
        return;
    }

    std::stringstream ss(header_line);
    std::vector<std::string> new_vertex_names;
    std::string vertex_name;

    while (ss >> vertex_name) {
        new_vertex_names.push_back(vertex_name);
    }

    int n = static_cast<int>(new_vertex_names.size());

    if (n == 0) {
        std::cerr << "Ошибка: вершины не найдены.\n";
        graph_loaded = false;
        return;
    }

    std::vector<Edge> new_edges;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int weight;

            if (!(file >> weight)) {
                std::cerr
                    << "Ошибка: некорректная матрица смежности.\n";

                graph_loaded = false;
                return;
            }

            if (i < j && weight > 0) {
                std::string u_name = new_vertex_names[i];
                std::string v_name = new_vertex_names[j];

                if (u_name > v_name) {
                    std::swap(u_name, v_name);
                }

                new_edges.push_back({
                    i, j, weight, u_name, v_name
                    });
            }
        }
    }

    vertex_names = std::move(new_vertex_names);
    edges = std::move(new_edges);

    graph_loaded = true;

    std::cout << "Граф успешно загружен!\n";
    std::cout << "Количество вершин: " << n << '\n';
    std::cout << "Количество рёбер: " << edges.size() << '\n';
}


// ============================================================
//                    ПРОСМОТР ГРАФА
// ============================================================

void show_graph() {
    if (!graph_loaded) {
        std::cout << "Сначала загрузите граф!\n";
        return;
    }

    std::cout << "ВЕРШИНЫ:\n";

    for (int i = 0; i < static_cast<int>(vertex_names.size()); ++i) {
        std::cout << i << " - " << vertex_names[i] << '\n';
    }

    std::cout << "\nРЁБРА:\n";

    for (const auto& edge : edges) {
        std::cout << edge.u_name << ' '
            << edge.v_name
            << " (вес: " << edge.weight << ")\n";
    }
}


// ============================================================
//                    ВЫБОР СТАРТОВОЙ ВЕРШИНЫ
// ============================================================

int choose_start_vertex() {
    for (int i = 0; i < static_cast<int>(vertex_names.size()); ++i) {
        std::cout << i << " - " << vertex_names[i] << '\n';
    }

    std::cout << "\nВведите индекс стартовой вершины: ";

    int start;

    if (!(std::cin >> start)) {
        std::cin.clear();
        std::cin.ignore(
            10000000, '\n'
        );

        std::cout << "Ошибка: необходимо ввести число.\n";
        return -1;
    }

    std::cin.ignore(
        10000000,'\n'
    );

    if (start < 0 ||
        start >= static_cast<int>(vertex_names.size())) {
        std::cout << "Ошибка: такой вершины нет.\n";
        return -1;
    }

    return start;
}


// ============================================================
//                    ОБХОД В ГЛУБИНУ
// ============================================================

void run_dfs() {
    if (!graph_loaded) {
        std::cout << "Сначала загрузите граф!\n";
        return;
    }

    int start = choose_start_vertex();

    if (start == -1) {
        return;
    }

    std::cout << "\nОбход в глубину (DFS):\n";
    DFS(vertex_names, edges, start);
}


// ============================================================
//                    ОБХОД В ШИРИНУ
// ============================================================

void run_bfs() {
    if (!graph_loaded) {
        std::cout << "Сначала загрузите граф!\n";
        return;
    }

    int start = choose_start_vertex();

    if (start == -1) {
        return;
    }

    std::cout << "\nОбход в ширину (BFS):\n";
    BFS(vertex_names, edges, start);
}


// ============================================================
//                МИНИМАЛЬНОЕ ОСТОВНОЕ ДЕРЕВО
// ============================================================

void build_mst() {
    if (!graph_loaded) {
        std::cout << "Сначала загрузите граф!\n";
        return;
    }

    int n = static_cast<int>(vertex_names.size());

    std::vector<Edge> sorted_edges = edges;

    if (!sorted_edges.empty()) {
        quickSortEdges(
            sorted_edges,
            0,
            static_cast<int>(sorted_edges.size()) - 1
        );
    }

    DSU dsu(n);
    std::vector<Edge> mst_edges;
    long long total_weight = 0;

    for (const auto& edge : sorted_edges) {
        if (dsu.unite(edge.u, edge.v)) {
            mst_edges.push_back(edge);
            total_weight += edge.weight;

            if (static_cast<int>(mst_edges.size()) == n - 1) {
                break;
            }
        }
    }

    if (static_cast<int>(mst_edges.size()) != n - 1) {
        std::cout << "Ошибка: граф несвязный, "
            << "остовное дерево не существует.\n";
        return;
    }

    if (!mst_edges.empty()) {
        quickSortByName(
            mst_edges,
            0,
            static_cast<int>(mst_edges.size()) - 1
        );
    }

    std::cout << "Минимальное остовное дерево:\n\n";

    for (const auto& edge : mst_edges) {
        std::cout << edge.u_name << ' '
            << edge.v_name << '\n';
    }

    std::cout << "\nОбщий вес: " << total_weight << '\n';
}


// ============================================================
//                           MAIN
// ============================================================

int main(int argc, char* argv[]) {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    if (argc > 1) {
        filename = argv[1];
    }

    load_graph();

    const int countItems = 6;

    std::string items[countItems] = {
        "Загрузить граф из файла",
        "Просмотреть граф",
        "Обход в глубину (DFS)",
        "Обход в ширину (BFS)",
        "Минимальное остовное дерево (Краскал)",
        "Выход"
    };

    while (true) {
        int choice = run_menu(
            items,
            countItems,
            "КУРСОВАЯ РАБОТА ПО ТЕОРИИ ГРАФОВ"
        );

        clear();
        showCursor();

        if (choice == 0) {
            std::cout << "Текущий путь к файлу:\n"
                << filename << "\n\n";

            std::cout << "Введите новый путь или Enter "
                << "для текущего:\n";

            std::string new_filename;
            std::getline(std::cin, new_filename);

            if (!new_filename.empty()) {
                filename = new_filename;
            }

            load_graph();
        }
        else if (choice == 1) {
            show_graph();
        }
        else if (choice == 2) {
            run_dfs();
        }
        else if (choice == 3) {
            run_bfs();
        }
        else if (choice == 4) {
            build_mst();
        }
        else {
            break;
        }

        pause();
    }

    showCursor();
    clear();

    std::cout << "Программа завершена.\n";

    return 0;
}
