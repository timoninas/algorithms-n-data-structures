#include "ArcGraph.hpp"
#include <iostream>

ArcGraph::ArcGraph(const IGraph& sendedGraph): verticesCount(sendedGraph.VerticesCount()) {
    for (int i = 0; i < sendedGraph.VerticesCount(); i++) {
        for (auto val: sendedGraph.GetNextVertices(i)) {
            graph.push_back(std::make_pair(i, val));
        }
    }
}

int ArcGraph::VerticesCount() const {
    return verticesCount;
}

void ArcGraph::AddEdge(int from, int to) {
    assert(from < VerticesCount());
    assert(to < VerticesCount());
    assert(from >= 0);
    assert(to >= 0);
    graph.push_back(std::make_pair(from, to));
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    
    for (auto val: graph) {
        if (val.first == vertex) {
            result.push_back(val.second);
        }
    }
    
    return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    
    for (auto val: graph) {
        if (val.second == vertex) {
            result.push_back(val.first);
        }
    }
    
    return result;
}
