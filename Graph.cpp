#include "Converter.cpp"
#include "GraphRepresentations.h"
#include "Graph.h"
#include <iostream>
#include <stack>
#include <queue>
#include <utility>

Graph::Graph(IncidentMatrix graph_im) {
    this->graph_im = std::move(graph_im);
}

bool Graph::GetOriented() const {
    return this->graph_im.oriented;
}

void Graph::Degrees() {
    // Create vectors for indegrees and outdegrees.
    // In case the graph isn't oriented, d_plus will be used as vector of degrees and d_minus will be unused.
    std::vector<size_t> d_plus(graph_im.v_count, 0);
    std::vector<size_t> d_minus(graph_im.v_count, 0);

    // For each vertex count its degrees.
    for (size_t i = 0; i < graph_im.v_count; ++i) {
        for (size_t j = 0; j < graph_im.e_count; ++j) {
            if (graph_im.incident_matrix[i][j] == 1)
                ++d_plus[i];
            if (graph_im.incident_matrix[i][j] == -1)
                ++d_minus[i];
        }
    }

    // Print the result.
    std::cout << (graph_im.oriented ? "d+:" : "d:") << std::endl;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < graph_im.v_count; ++j) {
            if (i == 0)
                std::cout << "v" << j + 1 << "\t";
            else
                std::cout << d_plus[j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    if (graph_im.oriented) {
        std::cout << "d-:" << std::endl;
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < graph_im.v_count; ++j) {
                if (i == 0)
                    std::cout << "v" << j + 1 << "\t";
                else
                    std::cout << d_plus[j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

size_t Graph::EdgesCount() const {
    return graph_im.e_count;
}

void Graph::DFS() {
    std::cout << std::endl;
    std::vector<uint64_t> way;
    std::set<uint64_t> visited;

    // Create stack for vertexes we're going to visit.
    std::stack<uint64_t> vertexes;

    auto adjacency_list = ImToAl(graph_im).GetAl();

    // Works until there's no unvisited vertexes.
    do {
        // Add 'white' vertex to our way.
        if (visited.empty()) {
            way.push_back(0);
        } else if (!visited.contains(vertexes.top())) {
            way.push_back(vertexes.top());
        } else {
            vertexes.pop();
            continue;
        }

        // As we've visited the vertex delete it from the stack.
        if (!vertexes.empty())
            vertexes.pop();

        // Mark it 'black'.
        visited.insert(way.back());

        // We want to visit vertexes next to the current so add it to the corresponding stack in the reverse way.
        std::vector<uint64_t> adjacent_vertexes;
        reverse_copy(adjacency_list[way.back()].begin(),
                     adjacency_list[way.back()].end(),
                     back_inserter(adjacent_vertexes));
        for (auto adjacent : adjacent_vertexes)
            vertexes.push(adjacent - 1);
    } while (!vertexes.empty());

    // Print the result.
    std::cout << "DFS: ";
    for (auto vertex : way)
        std::cout << vertex + 1 << " ";
    std::cout << std::endl;
}

void Graph::DFSRecursiveInit() {
    std::cout << std::endl;
    auto adjacency_list = ImToAl(graph_im).GetAl();
    std::set<uint64_t> visited;
    std::cout << "DFS (Recursive):";

    // The first call of recursive function.
    DFSRecursive(adjacency_list, visited, 0);
    std::cout << std::endl;
}

void Graph::DFSRecursive(const std::vector<std::multiset<uint64_t>>& adjacency_list,
                         std::set<uint64_t>& visited, uint64_t curr_v) {
    // If we've already visited current vertex return.
    if (visited.contains(curr_v))
        return;

    // Print current vertex and mark it 'black'.
    if (!visited.contains(curr_v)) {
        std::cout << " " << curr_v + 1;
        visited.insert(curr_v);
    }

    // Call this function to all the adjacent vertexes with the current one.
    for (auto adjacent : adjacency_list[curr_v])
        DFSRecursive(adjacency_list, visited, adjacent - 1);
}

void Graph::BFS() {
    std::cout << std::endl;
    std::vector<uint64_t> way;
    std::set<uint64_t> visited;
    auto adjacency_list = ImToAl(graph_im).GetAl();

    // Create queue for vertexes we're going to visit.
    std::queue<uint64_t> vertexes;

    // Works until there's no unvisited vertexes.
    do {
        // Add 'white' vertex to our way.
        if (visited.empty()) {
            way.push_back(0);
        } else if (!visited.contains(vertexes.front())) {
            way.push_back(vertexes.front());
        } else {
            vertexes.pop();
            continue;
        }

        // As we've visited the vertex delete it from the queue.
        if (!vertexes.empty())
            vertexes.pop();

        // Mark current vertex 'black'.
        visited.insert(way.back());

        // We want to visit vertexes next to the current so add it to the corresponding queue in the straight way.
        for (auto adjacent : adjacency_list[way.back()])
            vertexes.push(adjacent - 1);
    } while (!vertexes.empty());

    // Print the result.
    std::cout << "BFS: ";
    for (auto vertex : way)
        std::cout << vertex + 1 << " ";
    std::cout << std::endl;
}

// Print the graph according to the chosen representation type.
void Graph::Display(std::ostream & output_stream, int representation_type) const {
    switch (representation_type) {
        case 1:
            output_stream << ImToAm(this->graph_im);
            return;
        case 2:
            output_stream << this->graph_im;
            return;
        case 3:
            output_stream << ImToAl(this->graph_im);
            return;
        case 4:
            output_stream << ImToEl(this->graph_im);
            return;
        case 5:
            output_stream << ImToFoFi(this->graph_im, true, false);
            return;
        case 6:
            output_stream << ImToMfoMfi(this->graph_im, true, false);
            return;
        case 7:
            if (this->graph_im.oriented)
                output_stream << ImToFoFi(this->graph_im, false, false);
            else
                output_stream << ImToFoFi(this->graph_im, true, true);
            return;
        case 8:
            if (this->graph_im.oriented)
                output_stream << ImToMfoMfi(this->graph_im, false, false);
            else
                output_stream << ImToMfoMfi(this->graph_im, true, true);
            return;
    }
}

// Enter the graph according to the chosen representation type.
Graph Graph::Enter(std::istream & input_stream, bool oriented, int representation_type) {
    IncidentMatrix graph_im;
    switch (representation_type) {
        case 1:
            graph_im = AmToIm(AdjacencyMatrix(input_stream, oriented));
            break;
        case 2:
            graph_im = IncidentMatrix(input_stream, oriented);
            break;
        case 3:
            graph_im = AlToIm(AdjacencyList(input_stream, oriented));
            break;
        case 4:
            graph_im = ElToIm(EdgesList(input_stream, oriented));
            break;
        case 5:
            graph_im = FoFiToIm(FoFi(input_stream, oriented, true, false));
            break;
        case 6:
            graph_im = MfoMfiToIm(MfoMfi(input_stream, oriented, true, false));
            break;
        case 7:
            if (oriented)
                graph_im = FoFiToIm(FoFi(input_stream, oriented, false, false));
            else
                graph_im = FoFiToIm(FoFi(input_stream, oriented, true, false));
            break;
        case 8:
            if (oriented)
                graph_im = MfoMfiToIm(MfoMfi(input_stream, oriented, false, false));
            else
                graph_im = MfoMfiToIm(MfoMfi(input_stream, oriented, true, true));
            break;
    }
    return Graph(graph_im);
}
