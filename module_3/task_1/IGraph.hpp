//
//  IGraph.hpp
//  task_1
//
//  Created by Антон Тимонин on 22.12.2020.
//

#ifndef IGraph_hpp
#define IGraph_hpp

#include <stdio.h>
#include <vector>
#include <queue>

struct IGraph {
    virtual ~IGraph() {}
    
    virtual void AddEdge(int from, int to) = 0;
    
    virtual int VerticesCount() const = 0;
    
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif /* IGraph_hpp */
