#include <deque>
#include "GraphRepresentations.h"

IncidentMatrix AmToIm(const AdjacencyMatrix& graph) {
    std::vector<std::vector<int>> incident_matrix(graph.n);

    // For each pair of vertexes add a new column to incident matrix if the vertexes are adjacent.
    if (!graph.oriented) {
        // As the adjacency matrix in non-oriented graph is symmetric we can look along only a half of it.
        for (size_t i = 0; i < graph.n; ++i)
            for (size_t j = i; j < graph.n; ++j)
                if (graph.adjacency_matrix[i][j] > 0) {
                    for (size_t l = 0; l < graph.adjacency_matrix[i][j]; ++l) {
                        for (size_t k = 0; k < graph.n; ++k)
                            incident_matrix[k].push_back(k == i || k == j ? 1 : 0);
                    }
                }
    } else {
        // The adjacency matrix in oriented graph generally isn't symmetric, so we go all along the whole matrix.
        for (size_t i = 0; i < graph.n; ++i)
            for (size_t j = 0; j < graph.n; ++j) {
                if (graph.adjacency_matrix[i][j] > 0) {
                    for (size_t l = 0; l < graph.adjacency_matrix[i][j]; ++l) {
                        for (size_t k = 0; k < graph.n; ++k) {
                            // Determine which vertex is the start and which one is the end.
                            int res = 0;
                            if (k == i)
                                res = 1;
                            else if (k == j)
                                res = -1;
                            incident_matrix[k].push_back(res);
                        }
                    }
                }
            }
    }
    return {graph.oriented, incident_matrix};
}

AdjacencyMatrix ImToAm(const IncidentMatrix& graph) {
    std::vector<std::vector<int>> adjacency_matrix(graph.v_count, std::vector<int> (graph.v_count, 0));
    // Go through all the edges.
    for (size_t j = 0; j < graph.e_count; ++j) {
        // Create deque for an edge.
        std::deque<size_t> edge;

        // If it's oriented graph, start of the edge will be in the front of the deque, end - in the back.
        for (size_t i = 0; edge.size() < 2 && i < graph.v_count; ++i) {
            if (graph.incident_matrix[i][j] == 1)
                edge.push_front(i);
            if (graph.incident_matrix[i][j] == -1)
                edge.push_back(i);
        }

        // Mark the found 'cross'.
        ++adjacency_matrix[edge.front()][edge.back()];

        // If it's non-oriented graph also mark the symmetrical mirrored vertex.
        if (!graph.oriented)
            ++adjacency_matrix[edge.back()][edge.front()];
    }
    return {graph.oriented, adjacency_matrix};
}

IncidentMatrix AlToIm(const AdjacencyList& graph) {
    // For convenience, we'll convert to adjacency matrix form first then to incident matrix.
    std::vector<std::vector<int>> adjacency_matrix(graph.n, std::vector<int> (graph.n, 0));
    for (size_t i = 0; i < graph.n; ++i)
        for (auto vertex : graph.adjacency_list[i])
            ++adjacency_matrix[i][vertex - 1];
    return AmToIm(AdjacencyMatrix(graph.oriented, adjacency_matrix));
}

AdjacencyList ImToAl(const IncidentMatrix& graph) {
    // For convenience, we'll convert incident matrix form to adjacent one first.
    auto adjacency_matrix = ImToAm(graph).GetAM();
    std::vector<std::multiset<uint64_t>> adjacency_list(graph.v_count);
    for (size_t i = 0; i < graph.v_count; ++i)
        for (size_t j = 0; j < graph.v_count; ++j) {
            if (adjacency_matrix[i][j] > 0) {
                for (uint64_t k = 0; k < adjacency_matrix[i][j]; ++k)
                    adjacency_list[i].insert(j + 1);
            }
        }
    return {graph.oriented, adjacency_list};
}

IncidentMatrix ElToIm(const EdgesList& graph) {
    std::vector<std::vector<int>> incident_matrix(graph.v_count, std::vector<int>(graph.e_count, 0));
    for (size_t i = 0; i < graph.e_count; ++i) {
        incident_matrix[graph.edges_list[i].second - 1][i] = graph.oriented ? -1 : 1;
        incident_matrix[graph.edges_list[i].first - 1][i] = 1;
    }
    return {graph.oriented, incident_matrix};
}

EdgesList ImToEl(const IncidentMatrix& graph) {
    std::vector<std::pair<uint64_t, uint64_t>> edges_list(graph.e_count);
    for (size_t j = 0; j < graph.e_count; ++j) {
        std::deque<size_t> edge;
        for (size_t i = 0; edge.size() < 2 && i < graph.v_count; ++i) {
            if (graph.incident_matrix[i][j] == 1)
                edge.push_front(i);
            if (graph.incident_matrix[i][j] == -1)
                edge.push_back(i);
        }
        edges_list[j] = std::make_pair(edge[0] + 1, edge.back() + 1);
    }
    return {graph.oriented, edges_list, graph.v_count};
}

IncidentMatrix FoFiToIm(const FoFi& graph) {
    // For convenience, we'll convert to adjacency list first, then to incident matrix.
    std::vector<std::multiset<uint64_t>> adjacency_list(graph.vertexes[0]);
    size_t curr_v = 0;

    // Works until it meets that much '0' how many vertexes in that graph.
    for (size_t i = 1; curr_v < graph.vertexes[0]; ++i) {
        // If it meets '0', move to the next vertex.
        if (graph.vertexes[i] == 0) {
            ++curr_v;
            continue;
        }
        if (graph.is_FO)
            // If it's FO, elements in the given vector are numbers of vertexes
            // which the current one have an edge (arc) to.
            adjacency_list[curr_v].insert(graph.vertexes[i]);
        else
            // If it's FI, elements in the given vector are numbers of vertexes
            // which the current one have an edge (arc) from.
            adjacency_list[graph.vertexes[i] - 1].insert(curr_v + 1);
        if (graph.is_BFO)
            // If it's BFO, add an edge to the vertex adjacent with the current one.
            adjacency_list[graph.vertexes[i] - 1].insert(curr_v + 1);
    }
    return AlToIm(AdjacencyList(graph.oriented, adjacency_list));
}

FoFi ImToFoFi(const IncidentMatrix& graph, bool is_FO, bool is_BFO) {
    // For convenience, we'll convert to adjacency matrix first, then to FO/FI/BFO.
    std::vector<uint64_t> vertexes;

    // Get adjacency matrix of that graph.
    auto adjacency_matrix = ImToAm(graph).GetAM();

    // Put the count if vertexes at the start of the vector.
    vertexes.push_back(graph.v_count);

    // If it's FO, go through rows first then trough elements of the row. Otherwise, go through columns instead.
    if (is_FO) {
        for (size_t i = 0; i < graph.v_count; ++i) {
            for (size_t j = 0; j < graph.v_count; ++j) {
                for (int k = 0; k < adjacency_matrix[i][j]; ++k) {
                    if (!is_BFO || j >= i)
                        vertexes.push_back(j + 1);
                }
            }
            vertexes.push_back(0);
        }
    } else {
        for (size_t j = 0; j < graph.v_count; ++j) {
            for (size_t i = 0; i < graph.v_count; ++i) {
                for (int k = 0; k < adjacency_matrix[i][j]; ++k)
                    vertexes.push_back(i + 1);
            }
            vertexes.push_back(0);
        }
    }
    return {vertexes, graph.oriented, is_FO, is_BFO};
}

IncidentMatrix MfoMfiToIm(const MfoMfi& graph) {
    // For convenience, we'll convert to adjacency list first, then to incident matrix.
    std::vector<std::multiset<uint64_t>> adjacency_list(graph.vertexes_count);
    size_t i = 0, j = 0;
    for (auto last_adjacent : graph.mv) {
        while (j < last_adjacent) {
            if (graph.is_MFO) {
                adjacency_list[i].insert(graph.me[j]);
                if (graph.is_BMFO) {
                    adjacency_list[graph.me[j] - 1].insert(i + 1);
                }
            } else {
                adjacency_list[graph.me[j] - 1].insert(i + 1);
            }
            ++j;
        }
        ++i;
    }
    return AlToIm(AdjacencyList(graph.oriented, adjacency_list));
}

MfoMfi ImToMfoMfi(const IncidentMatrix& graph, bool is_MFO, bool is_BMFO) {
    std::vector<uint64_t> me;
    std::vector<size_t> mv;

    // For convenience, we'll convert to adjacency matrix first, then to MFO/MFI/BMFO.
    auto adjacency_matrix = ImToAm(graph).GetAM();

    // If it's FO, go through rows first then trough elements of the row. Otherwise, go through columns instead.
    if (is_MFO) {
        for (size_t i = 0; i < graph.v_count; ++i) {
            for (size_t j = 0; j < graph.v_count; ++j) {
                for (int k = 0; k < adjacency_matrix[i][j]; ++k) {
                    if (!is_BMFO || j >= i)
                        me.push_back(j + 1);
                }
            }
            mv.push_back(me.size());
        }
    } else {
        for (size_t j = 0; j < graph.v_count; ++j) {
            for (size_t i = 0; i < graph.v_count; ++i) {
                for (int k = 0; k < adjacency_matrix[i][j]; ++k)
                    me.push_back(i + 1);
            }
            mv.push_back(me.size());
        }
    }
    return {me, mv, graph.oriented, is_MFO, is_BMFO};
}
