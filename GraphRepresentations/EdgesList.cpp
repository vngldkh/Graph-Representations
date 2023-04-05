#include "../GraphRepresentations.h"
#include <iostream>
#include <vector>

void EdgesList::PrintInstruction() {
    std::cout << "1. Write the count of vertexes (n)." << std::endl;
    std::cout << "2. Write the count of edges (m)." << std::endl;
    std::cout << "3. Write 2*m elements of edges list (vertexes) separated by a single or multiple"
                 "\n   space (' '), tab ('\\t') or line break ('\\n') characters." << std::endl;
    std::cout << "The matrix will be filled row by row." << std::endl;
    std::cout << "The first pair of values will be interpreted as the first edge (arc), "
                 "the next one as the second edge (arc) and so on." << std::endl;
    std::cout << "Tip: vertex numbering starts from 1." << std::endl;
    std::cout << "For example, these numbers:" << std::endl;
    std::cout << "4 7" << std::endl;
    std::cout << "1     2 1 4   2" << std::endl;
    std::cout << "3\n2  4" << std::endl;
    std::cout << "3 2" << std::endl << "4 1" << std::endl << "4 3" << std::endl;
    std::cout << "will be interpreted as:" << std::endl;
    std::cout << "e1 :    v1      v2" << std::endl;
    std::cout << "e2 :    v1      v4" << std::endl;
    std::cout << "e3 :    v2      v3" << std::endl;
    std::cout << "e4 :    v2      v4" << std::endl;
    std::cout << "e5 :    v3      v2" << std::endl;
    std::cout << "e6 :    v4      v1" << std::endl;
    std::cout << "e7 :    v4      v3" << std::endl;
}

EdgesList::EdgesList(std::istream& input_stream, bool oriented) {
    this->oriented = oriented;
    input_stream >> v_count >> e_count;
    edges_list = std::vector<std::pair<uint64_t, uint64_t>>(e_count, std::make_pair(0, 0));
    for (size_t i = 0; i < e_count; ++i)
        input_stream >> edges_list[i].first >> edges_list[i].second;
}

EdgesList::EdgesList(bool oriented, const std::vector<std::pair<uint64_t, uint64_t>>& edges_list, size_t v_count) {
    this->oriented = oriented;
    this->v_count = v_count;
    this->e_count = edges_list.size();
    this->edges_list = edges_list;
}

std::ostream& operator <<(std::ostream& output_stream, const EdgesList& graph) {
    for (size_t i = 0; i < graph.e_count; ++i) {
        output_stream << "e" << i + 1 << " :\tv";
        output_stream << graph.edges_list[i].first << "\tv" << graph.edges_list[i].second << std::endl;
    }
    return output_stream;
}
