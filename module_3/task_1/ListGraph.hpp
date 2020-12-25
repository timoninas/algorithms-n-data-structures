#ifndef ListGraph_hpp
#define ListGraph_hpp

#include "IGraph.hpp"

class ListGraph: public IGraph {
public:
    ListGraph(size_t verticesCount) {
        graph.resize(verticesCount);
    }
    
    ListGraph(const IGraph&);
    
    virtual ~ListGraph() {}
    
    int VerticesCount() const override;
    
    void AddEdge(int from, int to) override;
    
    std::vector<int> GetNextVertices(int vertex) const override;
    
    std::vector<int> GetPrevVertices(int vertex) const override;
    
private:
    std::vector < std::vector<int> > graph;
};

#endif /* ListGraph_hpp */
