#include "MatrixGraph.hpp"

MatrixGraph::MatrixGraph(const IGraph& sendedGraph) {
    auto sendedGraphCount = sendedGraph.VerticesCount();
    graph.resize(sendedGraphCount);
    for (int i = 0; i < sendedGraphCount; i++) {
        graph[i].resize(sendedGraphCount, false);
    }
    
    for (int i = 0; i < sendedGraphCount; i++) {
        for (auto val: sendedGraph.GetNextVertices(i)) {
            graph[i][val] = true;
        }
    }
}

int MatrixGraph::VerticesCount() const {
    return graph.size();
}

void MatrixGraph::AddEdge(int from, int to) {
    assert(from < graph.size());
    assert(to < graph.size());
    assert(from >= 0);
    assert(to >= 0);
    graph[from][to] = true;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    
    int verticesCount = VerticesCount();
    
    for (int i = 0; i < verticesCount; i++) {
        if (graph[vertex][i]) {
            result.push_back(i);
        }
    }
    
    return result;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    
    int verticesCount = VerticesCount();
    
    for (int i = 0; i < verticesCount; i++) {
        if (graph[i][vertex]) {
            result.push_back(i);
        }
    }
    
    for (auto num: result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return result;
}
