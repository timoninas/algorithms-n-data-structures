#ifndef MatrixGraph_hpp
#define MatrixGraph_hpp

#include "IGraph.hpp"

#include <iostream>

class MatrixGraph: public IGraph {
public:
    MatrixGraph(size_t verticesCount) {
        graph.resize(verticesCount);
        for (int i = 0; i < graph.size(); i++) {
            graph[i].resize(verticesCount, false);
        }
    }
    
    MatrixGraph(const IGraph&);
    
    virtual ~MatrixGraph() {}
    
    int VerticesCount() const override;
    
    void AddEdge(int from, int to) override;
    
    std::vector<int> GetNextVertices(int vertex) const override;
    
    std::vector<int> GetPrevVertices(int vertex) const override;
    
    void print() {
        for (int i = 0; i < graph.size(); i++) {
            for (auto child: graph[i]) {
                std::cout << child << " ";
            }
            std::cout << std::endl;
        }
    }
    
private:
    std::vector < std::vector<bool> > graph;
};

#endif /* MatrixGraph_hpp */
