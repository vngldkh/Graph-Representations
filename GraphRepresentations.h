#include <iostream>
#include <set>
#include <vector>

#ifndef MAIN_CPP_GRAPHREPRESENTATIONS_H
#define MAIN_CPP_GRAPHREPRESENTATIONS_H

// Incident matrix form of graph representation.
struct IncidentMatrix {
    bool oriented;
    size_t v_count, e_count;
    std::vector<std::vector<int>> incident_matrix;

    IncidentMatrix();

    // Constructor providing input of incident matrix.
    IncidentMatrix(std::istream&, bool);

    // Constructor for convenient conversion.
    IncidentMatrix(bool, const std::vector<std::vector<int>>&);

    // Output of graph in form of incident matrix.
    friend std::ostream& operator <<(std::ostream&, const IncidentMatrix&);

    // Print the input instruction.
    static void PrintInstruction();
};

// Adjacency matrix form of graph representation.
class AdjacencyMatrix {
    bool oriented;
    size_t n;
    std::vector<std::vector<int>> adjacency_matrix;

public:
    // Constructor providing input of adjacency matrix.
    AdjacencyMatrix(std::istream&, bool);

    // Constructor for convenient conversion.
    AdjacencyMatrix(bool, std::vector<std::vector<int>>&);

    // Returns adjacency matrix.
    std::vector<std::vector<int>> GetAM() const;

    // Output of graph in form of adjacency matrix.
    friend std::ostream& operator <<(std::ostream&, const AdjacencyMatrix&);

    // Converts from adjacency matrix form to incident matrix form.
    friend IncidentMatrix AmToIm(const AdjacencyMatrix&);

    // Convert from incident matrix form to adjacency matrix form.
    friend AdjacencyMatrix ImToAm(const IncidentMatrix&);

    // Print the input instruction.
    static void PrintInstruction();
};

// Adjacency list form of graph representation.
class AdjacencyList {
    bool oriented;
    size_t n;
    std::vector<std::multiset<uint64_t>> adjacency_list;

public:
    // Constructor providing input of adjacency list.
    AdjacencyList(std::istream&, bool);

    // Constructor for convenient conversion.
    AdjacencyList(bool, const std::vector<std::multiset<uint64_t>>&);

    // Return adjacency list.
    std::vector<std::multiset<uint64_t>> GetAl() const;

    // Output of graph in form of adjacency list.
    friend std::ostream& operator <<(std::ostream&, const AdjacencyList&);

    // Convert from adjacency list form to incident matrix form.
    friend IncidentMatrix AlToIm(const AdjacencyList&);

    // Convert from incident matrix form to adjacency list form.
    friend AdjacencyList ImToAl(const IncidentMatrix&);

    // Print the input instruction.
    static void PrintInstruction();
};

// List of edges form of graph representation.
class EdgesList {
    bool oriented;
    size_t v_count, e_count;
    std::vector<std::pair<uint64_t, uint64_t>> edges_list;

public:
    // Constructor providing input of list of edges.
    EdgesList(std::istream&, bool);

    // Constructor for convenient conversion.
    EdgesList(bool, const std::vector<std::pair<uint64_t, uint64_t>>&, size_t);

    // Output of graph in form of list of edges.
    friend std::ostream& operator <<(std::ostream&, const EdgesList&);

    // Covert from list of edges form to incident matrix form.
    friend IncidentMatrix ElToIm(const EdgesList&);

    // Convert from incident matrix form to list of edges form.
    friend EdgesList ImToEl(const IncidentMatrix&);

    // Print the input instruction.
    static void PrintInstruction();
};

// FO, FI, BFO forms of graph representation.
class FoFi {
    bool oriented;
    bool is_FO;
    bool is_BFO;
    size_t vertexes_count;
    std::vector<uint64_t> vertexes;

public:
    // Constructor providing input of FO, FI, BFO forms.
    FoFi(std::istream&, bool, bool, bool);

    // Constructor for convenient conversion.
    FoFi(const std::vector<uint64_t>&, bool, bool, bool);

    // Output of graph in FI, FO, BFO forms.
    friend std::ostream& operator <<(std::ostream&, const FoFi&);

    // Convert from FI, FO, BFO forms to incident matrix form.
    friend IncidentMatrix FoFiToIm(const FoFi&);

    // Convert from incident matrix form to FI, FO, BFO forms.
    friend FoFi ImToFoFi(const IncidentMatrix&);

    // Print the input instruction.
    static void PrintInstruction();
};

// MFO, MFI, BMFO forms of graph representation.
class MfoMfi {
    bool oriented;
    bool is_MFO;
    bool is_BMFO;
    size_t vertexes_count;
    std::vector<uint64_t> me;
    std::vector<size_t> mv;

public:
    // Constructor providing input of MFO, MFI, BMFO forms.
    MfoMfi(std::istream&, bool, bool, bool);

    // Constructor for convenient conversion.
    MfoMfi(const std::vector<uint64_t>&, const std::vector<size_t>&, bool, bool, bool);

    // Output of graph in FI, FO, BFO forms.
    friend std::ostream& operator <<(std::ostream&, const MfoMfi&);

    // Convert from MFI, MFO, BMFO forms to incident matrix form.
    friend IncidentMatrix MfoMfiToIm(const MfoMfi&);

    // Convert from incident matrix form to MFI, MFO, BMFO forms.
    friend MfoMfi ImToMfoMfi(const IncidentMatrix&);

    // Print the input instruction.
    static void PrintInstruction();
};

#endif //MAIN_CPP_GRAPHREPRESENTATIONS_H
