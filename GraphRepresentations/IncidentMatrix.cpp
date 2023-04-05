#include "../GraphRepresentations.h"
#include <iostream>
#include <vector>

void IncidentMatrix::PrintInstruction() {
    std::cout << "1. Write the count of vertexes (n)." << std::endl;
    std::cout << "2. Write the count of edges (m)." << std::endl;
    std::cout << "3. Write n*m elements of incident matrix separated by a single or multiple"
                 "\n   space (' '), tab ('\\t') or line break ('\\n') characters." << std::endl;
    std::cout << "The matrix will be filled row by row." << std::endl;
    std::cout << "The first row will be filled with the first m values, "
                 "the second one with the next m values and so on." << std::endl;
    std::cout << "For example, these numbers:" << std::endl;
    std::cout << "4 7" << std::endl;
    std::cout << "1     1 0 0  0 -1     0 -1" << std::endl;
    std::cout << "0 1 1\n-1 0 0" << std::endl;
    std::cout << "0 0 -1 0 1 0 -1" << std::endl;
    std::cout << "0     -1 0 -1  0 1 1" << std::endl;
    std::cout << "will be interpreted as:" << std::endl;
    std::cout << "        e1      e2      e3      e4      e5      e6      e7" << std::endl;
    std::cout << "v1      1       1       0       0       0       -1      0" << std::endl;
    std::cout << "v2      -1      0       1       1       -1      0       0" << std::endl;
    std::cout << "v3      0       0       -1      0       1       0       -1" << std::endl;
    std::cout << "v4      0       -1      0       -1      0       1       1" << std::endl;
}

IncidentMatrix::IncidentMatrix() { }

IncidentMatrix::IncidentMatrix(std::istream& input_stream, bool oriented) {
    this->oriented = oriented;
    input_stream >> v_count >> e_count;
    incident_matrix = std::vector<std::vector<int>>(v_count, std::vector<int>(e_count));
    for (size_t i = 0; i < v_count; ++i)
        for (size_t j = 0; j < e_count; ++j)
            input_stream >> incident_matrix[i][j];
}

IncidentMatrix::IncidentMatrix(bool oriented, const std::vector<std::vector<int>>& incident_matrix) {
    this->oriented = oriented;
    v_count = incident_matrix.size();
    e_count = incident_matrix[0].size();
    this->incident_matrix = incident_matrix;
}

std::ostream& operator <<(std::ostream& output_stream, const IncidentMatrix& graph) {
    for (size_t i = 0; i <= graph.v_count; ++i) {
        for (size_t j = 0; j <= graph.e_count; ++j) {
            if (i == 0 && j == 0) {
                output_stream << '\t';
                continue;
            }
            if (i == 0) {
                output_stream << "e" << j << '\t';
                continue;
            }
            if (j == 0) {
                output_stream << "v" << i << '\t';
                continue;
            }
            output_stream << graph.incident_matrix[i - 1][j - 1] << '\t';
        }
        output_stream << std::endl;
    }
    return output_stream;
}
