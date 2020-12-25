#include <iostream>

// Необходимо написать несколько реализаций интерфейса:
// - ListGraph, хранящий граф в виде массива списков смежности,
// - MatrixGraph, хранящий граф в виде матрицы смежности,
// - SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
// - ArcGraph, хранящий граф в виде одного массива пар {from, to}.
// Также необходимо реализовать конструктор, принимающий const IGraph&.
// Такой конструктор должен скопировать переданный граф в создаваемый объект.
// Для каждого класса создавайте отдельные h и cpp файлы.
// Число вершин графа задается в конструкторе каждой реализации.

// Создаем ListGraph
// Из ListGraph создаем MatrixGraph
// Из MatrixGraph создаем SetGraph
// Из SetGraph создаем ArcGraph
// На каждом этапе проверять, что список детей совпадает

#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"
#include "ArcGraph.hpp"

// Depth First Search
void dfs_aux(const IGraph& graph, int vertex, std::vector<bool>& visited, void (*callback)(int v));

void dfs(const IGraph& graph, void (*callback)(int v)) {
    std::vector<bool> visited;
    visited.resize(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i]) {
            dfs_aux(graph, i, visited, callback);
        }
    }
}

void dfs_aux(const IGraph& graph, int vertex, std::vector<bool>& visited, void (*callback)(int v)) {
    visited[vertex] = true;
    callback(vertex);
    
    for (auto child: graph.GetNextVertices(vertex)) {
        if (!visited[child]) {
            dfs_aux(graph, child, visited, callback);
        }
    }
}

// Breadth First Search
void bfs(const IGraph& graph, void (*callback)(int v)) {
    std::vector<bool> visited;
    std::queue<int> queue;
    visited.resize(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i]) {
            queue.push(i);
            visited[i] = true;
            while (!queue.empty()) {
                int vertex = queue.front();
                queue.pop();
                callback(vertex);
                for (auto child: graph.GetNextVertices(vertex)) {
                    if (!visited[child]) {
                        queue.push(child);
                        visited[child] = true;
                    }
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    ListGraph listGraph(6);

    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(2, 3);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(4, 1);

    bfs(listGraph, [](int v) {
        std::cout << v << std::endl;
    });

    std::cout << "------------" << std::endl;

    MatrixGraph mtrxGraph(listGraph);

    bfs(mtrxGraph, [](int v) {
        std::cout << v << std::endl;
    });
    
    std::cout << "------------" << std::endl;

    SetGraph setGraph(mtrxGraph);

    bfs(setGraph, [](int v) {
        std::cout << v << std::endl;
    });
    
    std::cout << "------------" << std::endl;

    ArcGraph arcGraph(setGraph);

    bfs(arcGraph, [](int v) {
        std::cout << v << std::endl;
    });
    
    return 0;
}
