#include "SetGraph.hpp"

SetGraph::SetGraph(const IGraph& sendedGraph) {
    graph.resize(sendedGraph.VerticesCount());
    for (int i = 0; i < sendedGraph.VerticesCount(); i++) {
        for (auto child: sendedGraph.GetNextVertices(i)) {
            graph[i].insert(child);
        }
    }
}

int SetGraph::VerticesCount() const {
    return graph.size();
}

void SetGraph::AddEdge(int from, int to) {
    assert(from < graph.size());
    assert(to < graph.size());
    assert(from >= 0);
    assert(to >= 0);
    graph[from].insert(to);
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    
    for (auto val: graph[vertex]) {
        result.push_back(val);
    }
    
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
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
