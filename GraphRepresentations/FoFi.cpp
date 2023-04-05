#include "../GraphRepresentations.h"
#include <iostream>
#include <vector>

void FoFi::PrintInstruction() {
    std::cout << "Write all the elements of FO/FI/BFO array separated by a single or multiple " << std::endl;
    std::cout << "space (' '), tab ('\\t') or line break ('\\n') characters." << std::endl;
    std::cout << "Tips: 1. Vertex numbering starts from 1." << std::endl;
    std::cout << "      2. The separator is '0'." << std::endl;
    std::cout << "For example, you can import FO graph like that: " << std::endl;
    std::cout << "5 2 5     0 1 3 4 5 0\n2  4   0 3 2 5 0 1 2 4 0" << std::endl;
}

FoFi::FoFi(std::istream& input_stream, bool oriented, bool is_FO, bool is_BFO) {
    this->oriented = oriented;
    this->is_FO = is_FO;
    this->is_BFO = is_BFO;
    input_stream >> vertexes_count;
    vertexes.push_back(vertexes_count);
    uint64_t vertex;
    for (size_t i = 0; i < vertexes_count; ++i) {
        do {
            input_stream >> vertex;
            vertexes.push_back(vertex);
        } while (vertex != 0);
    }
}

FoFi::FoFi(const std::vector<uint64_t>& vertexes, bool oriented, bool is_FO, bool is_BFO) {
    this->oriented = oriented;
    this->is_FO = is_FO;
    this->is_BFO = is_BFO;
    this->vertexes = vertexes;
    this->vertexes_count = vertexes[0];
}

std::ostream& operator <<(std::ostream& output_stream, const FoFi& graph) {
    for (uint64_t vertex : graph.vertexes)
        output_stream << vertex << " ";
    std::cout << std::endl;
    return output_stream;
}
