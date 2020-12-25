#ifndef ArcGraph_hpp
#define ArcGraph_hpp

#include "IGraph.hpp"

class ArcGraph: public IGraph {
public:
    ArcGraph(size_t verticesCount): verticesCount(verticesCount) {}
    
    ArcGraph(const IGraph&);
    
    virtual ~ArcGraph() {}
    
    int VerticesCount() const override;
    
    void AddEdge(int from, int to) override;
    
    std::vector<int> GetNextVertices(int vertex) const override;
    
    std::vector<int> GetPrevVertices(int vertex) const override;
    
private:
    std::vector < std::pair<int, int> > graph;
    size_t verticesCount;
};


#endif /* ArcGraph_hpp */
