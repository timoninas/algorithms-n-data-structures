#include <iostream>
#include <istream>
#include <sstream>

#include <vector>
#include <queue>

#include <assert.h>

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
    
    int VerticesCount() const override {
        return graph.size();
    }
    
    void AddEdge(int from, int to) override {
        assert(from < graph.size());
        assert(to < graph.size());
        assert(from >= 0);
        assert(to >= 0);
        graph[from].push_back(to);
        graph[to].push_back(from);
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

int bfs(const IGraph& graph, int from, int to) {
    std::queue<int> queue;
    
    std::vector<bool> visited;
    visited.resize(graph.VerticesCount(), false);
    
    std::vector<int> routes;
    routes.resize(graph.VerticesCount(), graph.VerticesCount());
    
    std::vector<int> min_path_count;
    min_path_count.resize(graph.VerticesCount(), 0);
    
    queue.push(from);
    visited[from] = true;
    routes[from] = 0;
    min_path_count[from] = 1;
    
    while (!queue.empty()) {
        int vertex = queue.front(); queue.pop();
        
        for (auto child: graph.GetNextVertices(vertex)) {
            if (routes[child] > routes[vertex] + 1) {
                min_path_count[child] = min_path_count[vertex];
                routes[child] = routes[vertex] + 1;
            } else if (routes[child] == routes[vertex] + 1) {
                min_path_count[child] += min_path_count[vertex];
            }
            
            if (!visited[child]) {
                visited[child] = true;
                queue.push(child);
            }
        }
    }
    
    return min_path_count[to];
}

int run(std::istream& input, std::ostream& output);

void testLogic() {
    {
        std::stringstream sstr_input;
        sstr_input << "4" << std::endl;
        sstr_input << "5" << std::endl;
        sstr_input << "0 1" << std::endl;
        sstr_input << "0 2" << std::endl;
        sstr_input << "1 2" << std::endl;
        sstr_input << "1 3" << std::endl;
        sstr_input << "2 3" << std::endl;
        
        sstr_input << "0 3" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "2");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "4" << std::endl;
        sstr_input << "5" << std::endl;
        sstr_input << "0 1" << std::endl;
        sstr_input << "0 2" << std::endl;
        sstr_input << "1 2" << std::endl;
        sstr_input << "1 3" << std::endl;
        sstr_input << "2 3" << std::endl;
        
        sstr_input << "0 2" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "1");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "2" << std::endl;
        sstr_input << "0" << std::endl;
        
        sstr_input << "0 1" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "0");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "7" << std::endl;
        sstr_input << "8" << std::endl;
        sstr_input << "0 1" << std::endl;
        sstr_input << "0 2" << std::endl;
        sstr_input << "1 3" << std::endl;
        sstr_input << "2 3" << std::endl;
        sstr_input << "3 4" << std::endl;
        sstr_input << "3 5" << std::endl;
        sstr_input << "4 6" << std::endl;
        sstr_input << "5 6" << std::endl;
        
        sstr_input << "0 6" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "4");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "7" << std::endl;
        sstr_input << "11" << std::endl;
        sstr_input << "0 1" << std::endl;
        sstr_input << "0 2" << std::endl;
        sstr_input << "0 3" << std::endl;
        sstr_input << "1 2" << std::endl;
        sstr_input << "2 3" << std::endl;
        sstr_input << "1 4" << std::endl;
        sstr_input << "2 4" << std::endl;
        sstr_input << "2 5" << std::endl;
        sstr_input << "3 5" << std::endl;
        sstr_input << "4 6" << std::endl;
        sstr_input << "5 6" << std::endl;
        
        sstr_input << "0 6" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "4");
    }
}

int run(std::istream& input, std::ostream& output) {
    int v, n;
    input >> v >> n;
    
    assert(v <= 50000);
    assert(n <= 200000);
    
    ListGraph graph(v);
    
    for (int i = 0; i < n; i++) {
        int v1, v2;
        input >> v1 >> v2;
        graph.AddEdge(v1, v2);
    }
    
    int from, to;
    input >> from >> to;
    
    output << bfs(graph, from, to);
    
    return 0;
}

int main(int argc, const char * argv[]) {
//    testLogic();
//    std::cout << "TEST PASSED" << std::endl;
//    return 0;
    
    return run(std::cin, std::cout);
}
