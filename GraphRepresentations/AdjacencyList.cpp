#include "../GraphRepresentations.h"
#include <iostream>
#include <vector>
#include <set>
#include <sstream>

void AdjacencyList::PrintInstruction() {
    std::cout << "1. Write the count of vertexes as a single number on the line." << std::endl;
    std::cout << "2. For each vertex write the numbers of all the adjacent ones with that vertex "
                 "\n   separated by a single or multiple space or tab characters on a single line." << std::endl;
    std::cout << "Tips: 1. For each vertex use its own line." << std::endl;
    std::cout << "      2. If any vertex doesn't have the adjacent ones, leave the line empty "
                 "(Press \"Enter\")." << std::endl;
    std::cout << "      3. Vertex numbering starts from 1." << std::endl;
    std::cout << "For example, these numbers:" << std::endl << "4" << std::endl;
    std::cout << "2 4" << std::endl << "3   4" << std::endl << "2" << std::endl << "1  3" << std::endl;
    std::cout << "will be interpreted as: " << std::endl;
    std::cout << "v1 :    v2      v4" << std::endl << "v2 :    v3      v4" << std::endl;
    std::cout << "v3 :    v2" << std::endl << "v4 :    v1      v3" << std::endl;
}

AdjacencyList::AdjacencyList(std::istream& input_stream, bool oriented) {
    this->oriented = oriented;
    input_stream >> n >> std::ws;
    adjacency_list = std::vector<std::multiset<uint64_t>>(n);
    std::string input;
    for (size_t i = 0; i < n; ++i) {
        getline(input_stream, input);
        std::istringstream iss(input);
        uint64_t vertex;
        while (iss >> vertex)
            adjacency_list[i].insert(vertex);
    }
}

AdjacencyList::AdjacencyList(bool oriented, const std::vector<std::multiset<uint64_t>>& adjacency_list) {
    this->oriented = oriented;
    this->n = adjacency_list.size();
    this->adjacency_list = adjacency_list;
}

std::vector<std::multiset<uint64_t>> AdjacencyList::GetAl() const {
    return adjacency_list;
}

std::ostream& operator <<(std::ostream& output_stream, const AdjacencyList& graph) {
    for (size_t i = 0; i < graph.n; ++i) {
        output_stream << "v" << i + 1 << " :";
        for (auto vertex : graph.adjacency_list[i])
            output_stream << "\tv" << vertex;
        output_stream << std::endl;
    }
    return output_stream;
}

