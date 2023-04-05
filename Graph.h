#include "GraphRepresentations.h"
#include <set>
#ifndef MAIN_CPP_GRAPH_H
#define MAIN_CPP_GRAPH_H

// Graph wrapper represented as incident matrix.
class Graph {
    IncidentMatrix graph_im;

public:
    // Wrap the given matrix.
    explicit Graph(IncidentMatrix);

    // Has a value of 'true', if the graph is oriented.
    bool GetOriented() const;

    // Print the vertexes' degrees.
    void Degrees();

    // Returns the count of edges.
    size_t EdgesCount() const;

    // Non-recursive realization of Depth-First Search.
    void DFS();

    // Initialization of recursive DFS.
    void DFSRecursiveInit();

    // Recursive realization of Depth-First Search.
    void DFSRecursive(const std::vector<std::multiset<uint64_t>>&, std::set<uint64_t>&, uint64_t);

    // Breadth-First Search.
    void BFS();

    // Output the graph.
    void Display(std::ostream&, int) const;

    // Input the graph.
    static Graph Enter(std::istream&, bool, int);
};

#endif //MAIN_CPP_GRAPH_H
