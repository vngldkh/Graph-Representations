#include "../GraphRepresentations.h"
#include <iostream>
#include <vector>

void AdjacencyMatrix::PrintInstruction() {
    std::cout << "1. Write the count of vertexes (n)." << std::endl;
    std::cout << "2. Write n*n elements of adjacency matrix separated by a single or multiple"
                 "\n   space (' '), tab ('\\t') or line break ('\\n') characters." << std::endl;
    std::cout << "The matrix will be filled row by row." << std::endl;
    std::cout << "The first row will be filled with the first n values, "
                 "the second one with the next n values and so on." << std::endl;
    std::cout << "For example, these numbers:" << std::endl;
    std::cout << "4" << std::endl << "0 1 \t0 1  0" << std::endl << "0 1 \t 1" << std::endl;
    std::cout << "0 1 0 0\n" << std::endl << "1 0  1  0" << std::endl;
    std::cout << "will be interpreted as:" << std::endl;
    std::cout << "        v1      v2      v3      v4" << std::endl;
    std::cout << "v1      0       1       0       1" << std::endl;
    std::cout << "v2      0       0       1       1" << std::endl;
    std::cout << "v3      0       1       0       0" << std::endl;
    std::cout << "v4      1       0       1       0" << std::endl;
}

AdjacencyMatrix::AdjacencyMatrix(std::istream& input_stream, bool oriented) {
    this->oriented = oriented;
    input_stream >> n;
    adjacency_matrix = std::vector<std::vector<int>>(n, std::vector<int>(n));
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            input_stream >> adjacency_matrix[i][j];
}

AdjacencyMatrix::AdjacencyMatrix(bool oriented, std::vector<std::vector<int>>& adjacency_matrix) {
    this->oriented = oriented;
    this->n = adjacency_matrix.size();
    this->adjacency_matrix = adjacency_matrix;
}

std::vector<std::vector<int>> AdjacencyMatrix::GetAM() const {
    return adjacency_matrix;
}

std::ostream& operator <<(std::ostream& output_stream, const AdjacencyMatrix& graph) {
    for (size_t i = 0; i <= graph.n; ++i) {
        for (size_t j = 0; j <= graph.n; ++j) {
            if (i == 0 && j == 0) {
                output_stream << '\t';
                continue;
            }
            if (i == 0) {
                output_stream << "v" << j << '\t';
                continue;
            }
            if (j == 0) {
                output_stream << "v" << i << '\t';
                continue;
            }
            output_stream << graph.adjacency_matrix[i - 1][j - 1] << '\t';
        }
        output_stream << std::endl;
    }
    return output_stream;
}
