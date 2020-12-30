#include <iostream>
#include <istream>
#include <sstream>

#include <vector>
#include <queue>

#include <assert.h>

// Написать функцию, проверяющую, является ли граф Эйлеровым

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


bool is_eulerian_graph(const IGraph& graph) {
    int count;
    for (int i = 0; i < graph.VerticesCount(); i++) {
        for (count = 0; count < graph.GetNextVertices(i).size(); count++);
        if (count % 2 == 1) {
            return false;
        }
    }
    return true;
}

int run(std::istream& input, std::ostream& output) {
    int v, n;
    input >> v >> n;
    
    ListGraph graph(v);
    
    for (int i = 0; i < n; i++) {
        int v1, v2;
        input >> v1 >> v2;
        graph.AddEdge(v1, v2);
    }
    
    output << is_eulerian_graph(graph) << "\n";
    
    return 0;
}

void testLogic() {
    {
        std::stringstream sstr_input;
        sstr_input << "5" << std::endl;
        sstr_input << "10" << std::endl;
        sstr_input << "0 1" << std::endl;
        sstr_input << "0 3" << std::endl;
        sstr_input << "1 2" << std::endl;
        sstr_input << "1 4" << std::endl;
        sstr_input << "2 0" << std::endl;
        sstr_input << "2 4" << std::endl;
        sstr_input << "3 1" << std::endl;
        sstr_input << "3 2" << std::endl;
        sstr_input << "4 0" << std::endl;
        sstr_input << "4 3" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "1\n");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "3" << std::endl;
        sstr_input << "3" << std::endl;
        sstr_input << "0 1" << std::endl;
        sstr_input << "1 2" << std::endl;
        sstr_input << "2 0" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "1\n");
    }
    std::cout << "TEST PASSED" << std::endl;
}

int main(int argc, const char * argv[]) {
    testLogic();
    
    return run(std::cin, std::cout);
}
