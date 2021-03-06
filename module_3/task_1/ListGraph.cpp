#include "ListGraph.hpp"

ListGraph::ListGraph(const IGraph& sendedGraph) {
    graph.resize(sendedGraph.VerticesCount());
    for (int i = 0; i < sendedGraph.VerticesCount(); i++) {
        for (auto child: sendedGraph.GetNextVertices(i)) {
            graph[i].push_back(child);
        }
    }
}

int ListGraph::VerticesCount() const {
    return graph.size();
}

void ListGraph::AddEdge(int from, int to) {
    assert(from < graph.size());
    assert(to < graph.size());
    assert(from >= 0);
    assert(to >= 0);
    graph[from].push_back(to);
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    
    result.resize(graph[vertex].size());
    std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
    
    return result;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    
    for(size_t i = 0; i < graph.size(); i++) {
        for (auto child: graph[i]) {
            if (child == vertex) {
                result.push_back(i);
                break;
            }
        }
    }
    
    return result;
}
