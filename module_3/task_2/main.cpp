#include <iostream>

#include <vector>

// Дан невзвешенный неориентированный граф. В графе может быть несколько
// кратчайших путей между какими-то вершинами. Найдите количество
// различных кратчайших путей между заданными вершинами
// Требования: сложность O(V+E)

struct IGraph {
    virtual ~IGraph() {}
    
    virtual void AddEdge(int from, int to) = 0;
    
    virtual int VerticesCount() const = 0;
    
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph: public IGraph {
public:
    ListGraph(size_t verticesCount) {
        graph.resize(verticesCount);
    }
    
    ListGraph(const IGraph& sendedGraph) {
        graph.resize(sendedGraph.VerticesCount());
        for (int i = 0; i < sendedGraph.VerticesCount(); i++) {
            for (auto child: sendedGraph.GetNextVertices(i)) {
                graph[i].push_back(child);
            }
        }
    }
    
    virtual ~ListGraph() {}
    
    int VerticesCount() const {
        return graph.size();
    }
    
    void AddEdge(int from, int to) {
        assert(from < graph.size());
        assert(to < graph.size());
        assert(from >= 0);
        assert(to >= 0);
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

int main(int argc, const char * argv[]) {
    ListGraph listGraph(6);

    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(2, 3);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(4, 1);

    for (auto val: listGraph.GetNextVertices(0)) {
        std::cout << val << std::endl;
    }
    return 0;
}
