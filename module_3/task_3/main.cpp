#include <iostream>
#include <istream>
#include <sstream>

#include <utility>
#include <vector>
#include <set>

#include <assert.h>

#define MAX_INT 2147483647

// Требуется отыскать самый выгодный маршрут между городами

struct IGraph {
    virtual ~IGraph() {}
    
    virtual void AddEdge(int from, int to, int time) = 0;
    
    virtual int VerticesCount() const = 0;
    
    virtual std::vector< std::pair<int, int> > GetNextVertices(int vertex) const = 0;
    virtual std::vector< std::pair<int, int> > GetPrevVertices(int vertex) const = 0;
};

class ListGraph: public IGraph {
public:
    ListGraph(size_t verticesCount) {
        graph.resize(verticesCount);
    }
    
    virtual ~ListGraph() {}
    
    int VerticesCount() const override {
        return graph.size();
    }
    
    void AddEdge(int from, int to, int time) override {
        assert(from < graph.size());
        assert(to < graph.size());
        assert(from >= 0);
        assert(to >= 0);
        graph[from].push_back(std::make_pair(to, time));
        graph[to].push_back(std::make_pair(from, time));
    }
    
    std::vector< std::pair<int, int> > GetNextVertices(int vertex) const override {
        std::vector<std::pair<int, int>> result;
        
        result.resize(graph[vertex].size());
        std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
        
        return result;
    }
    
    std::vector< std::pair<int, int> > GetPrevVertices(int vertex) const override {
        std::vector< std::pair<int, int> > result;
        
        for(int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                if (j == vertex) {
                    result.push_back(std::make_pair(i, graph[i][j].second));
                }
            }
        }
        
        return result;
    }
private:
    std::vector < std::vector< std::pair<int, int> > > graph;
};

int Dijkstra(const IGraph& graph, int from, int to) {
    std::vector<int> parents; parents.resize(graph.VerticesCount(), -1);
    std::vector<int> dist; dist.resize(graph.VerticesCount(), MAX_INT);
    dist[from] = 0;
    
    std::set< int > q; q.insert(from);
    
    while(!q.empty()) {
        auto u = *q.begin(); q.erase(q.begin());
        for (auto vt: graph.GetNextVertices(u)) {
            if (dist[vt.first] > dist[u] + vt.second) {
                dist[vt.first] = dist[u] + vt.second;
                parents[vt.first] = u;
                q.insert(vt.first);
            }
        }
    }
    
    return dist[to];
}

struct cmp {
    bool operator() (const std::pair<int, int> &a, const std::pair<int, int> &b) {
        return a.first == b.first && a.second < b.second;
    }
};

int run(std::istream& input, std::ostream& output);

void testLogic() {
    {
        std::stringstream sstr_input;
        sstr_input << "9" << std::endl;
        sstr_input << "16" << std::endl;
        sstr_input << "0 2 2" << std::endl;
        sstr_input << "0 3 6" << std::endl;
        sstr_input << "0 1 9" << std::endl;
        sstr_input << "1 6 4" << std::endl;
        sstr_input << "2 4 1" << std::endl;
        sstr_input << "2 3 3" << std::endl;
        sstr_input << "3 1 2" << std::endl;
        sstr_input << "3 5 9" << std::endl;
        sstr_input << "3 6 7" << std::endl;
        sstr_input << "4 3 1" << std::endl;
        sstr_input << "4 7 6" << std::endl;
        sstr_input << "5 7 5" << std::endl;
        sstr_input << "5 8 1" << std::endl;
        sstr_input << "6 5 1" << std::endl;
        sstr_input << "6 8 5" << std::endl;
        sstr_input << "7 8 5" << std::endl;

        sstr_input << "0 8" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "12");
    }
    {
        std::stringstream sstr_input;
        sstr_input << "6" << std::endl;
        sstr_input << "9" << std::endl;
        sstr_input << "0 3 1" << std::endl;
        sstr_input << "0 4 2" << std::endl;
        sstr_input << "1 2 7" << std::endl;
        sstr_input << "1 3 2" << std::endl;
        sstr_input << "1 4 3" << std::endl;
        sstr_input << "1 5 3" << std::endl;
        sstr_input << "2 5 3" << std::endl;
        sstr_input << "3 4 4" << std::endl;
        sstr_input << "3 5 6" << std::endl;
        
        sstr_input << "0 2" << std::endl;
        std::stringstream sstr_output;
        run(sstr_input, sstr_output);
        assert(sstr_output.str() == "9");
    }
    std::cout << "TEST PASSED" << std::endl;
}

int run(std::istream& input, std::ostream& output) {
    int n, m;
    input >> n >> m;
    
    ListGraph graph(n);
    
    for (int i = 0; i < m; i++) {
        int from, to, time;
        input >> from >> to >> time;
        graph.AddEdge(from, to, time);
    }
    
    int from, to;
    input >> from >> to;
    
    output << Dijkstra(graph, from, to);
    
    return 0;
}

int main(int argc, const char * argv[]) {
    testLogic();
    return run(std::cin, std::cout);
}
