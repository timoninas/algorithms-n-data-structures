#include <iostream>

#include <vector>
#include <queue>

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

void bfs(const IGraph& graph, int from, int to) {
    std::queue<int> queue;
    
    std::vector<bool> visited;
    visited.resize(graph.VerticesCount(), false);
    
    std::vector<int> routes;
    routes.resize(graph.VerticesCount(), 0);
    
    std::vector<int> min_routes;
    min_routes.resize(graph.VerticesCount(), 0);
    
    queue.push(from);
    visited[from] = true;
    routes[from] = 1;
    min_routes[from] = 1;
    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        std::cout << vertex << std::endl;
        for (auto child: graph.GetNextVertices(vertex)) {
            if (min_routes[child] == 0) {
                min_routes[child] = min_routes[vertex];
                routes[child] += routes[vertex];
            } else if (min_routes[vertex] > min_routes[child]) {
                min_routes[child] = min_routes[vertex];
                routes[child] = routes[vertex];
            } else if (min_routes[vertex] == min_routes[child]) {
                routes[child] += routes[vertex];
                std::cout << ">" << routes[vertex] << std::endl;
            }
//            routes[child] += routes[vertex];
            if (!visited[child]) {
                queue.push(child);
                visited[child] = true;
            }
        }
    }
    
    for (int i = 0; i < graph.VerticesCount(); i++) {
        std::cout << i << " - " << routes[i] << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    ListGraph graph(7);
    
//    graph.AddEdge(0, 1);
//    graph.AddEdge(0, 2);
//    graph.AddEdge(1, 3);
//    graph.AddEdge(2, 3);
//    graph.AddEdge(3, 4);
//    graph.AddEdge(3, 5);
//    graph.AddEdge(4, 6);
//    graph.AddEdge(5, 6);
    
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 3);
    
    bfs(graph, 0, 3);
    
    return 0;
}
