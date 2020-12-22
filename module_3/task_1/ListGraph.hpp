//
//  ListGraph.hpp
//  task_1
//
//  Created by Антон Тимонин on 22.12.2020.
//

#ifndef ListGraph_hpp
#define ListGraph_hpp

#include "IGraph.hpp"

class ListGraph: public IGraph {
public:
    ListGraph(size_t verticesCount) {
        graph.resize(verticesCount);
    }
    
    ListGraph(const IGraph&) { }
    
    virtual ~ListGraph() {}
    
    int VerticesCount() const override { return graph.size(); }
    
    void AddEdge(int from, int to) override {
        graph[from].push_back(to);
    }
    
    std::vector<int> GetNextVertices(int vertex) const override {
        std::vector<int> result;
        
        result.resize(graph[vertex].size());
        std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
        
        return result;
    }
    
    std::vector<int> GetPrevVertices(int vertex) const override {
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
    
private:
    std::vector < std::vector<int> > graph;
};

#endif /* ListGraph_hpp */
