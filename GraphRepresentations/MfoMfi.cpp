#include "../GraphRepresentations.h"
#include <iostream>
#include <sstream>
#include <vector>

void MfoMfi::PrintInstruction() {
    std::cout << "1. Write the count of vertexes as a single number on the line." << std::endl;
    std::cout << "2. On a single line write all the elements of ME array." << std::endl;
    std::cout << "3. On a single line write all the elements of MV array." << std::endl;
    std::cout << "Tips: 1. Elements inside the single line could be separated by" << std::endl;
    std::cout << "         a single or multiple space or tab characters" << std::endl;
    std::cout << "      2. Vertex numbering starts from 1." << std::endl << "5" << std::endl;
    std::cout << "2  5 1    3 4 5 4 2 3  2   5 1 2 4" << std::endl;
    std::cout << "2   6 8    11 14" << std::endl;
    std::cout << "will be interpreted as:" << std::endl;
    std::cout << "P  : 5" << std::endl;
    std::cout << "ME : 2 5 1 3 4 5 2 4 2 3 5 1 2 4" << std::endl;
    std::cout << "MV : 2 6 8 11 14" << std::endl;
}

MfoMfi::MfoMfi(std::istream& input_stream, bool oriented, bool is_MFO, bool is_BMFO) {
    this->oriented = oriented;
    this->is_MFO = is_MFO;
    this->is_BMFO = is_BMFO;
    input_stream >> vertexes_count >> std::ws;
    uint64_t input_value;
    std::string input;
    getline(input_stream, input);
    std::istringstream iss(input);
    while (iss >> input_value)
        me.push_back(input_value);
    getline(input_stream, input);
    iss = std::istringstream(input);
    while (iss >> input_value)
        mv.push_back(input_value);
}

MfoMfi::MfoMfi(const std::vector<uint64_t>& me, const std::vector<size_t>& mv, bool oriented, bool is_MFO, bool is_BMFO) {
    this->me = me;
    this->mv = mv;
    this->vertexes_count = mv.size();
    this->oriented = oriented;
    this->is_MFO = is_MFO;
    this->is_BMFO = is_BMFO;
}

std::ostream& operator <<(std::ostream& output_stream, const MfoMfi& graph) {
    output_stream << "P  : " << graph.vertexes_count << std::endl << "ME :";
    for (auto x : graph.me)
        output_stream << " " << x;
    output_stream << std::endl << "MV :";
    for (auto x : graph.mv)
        output_stream << " " << x;
    std::cout << std::endl;
    return output_stream;
}
