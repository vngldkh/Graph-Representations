#include "GraphRepresentations.h"
#include <iostream>
#include <fstream>
#include "Graph.cpp"

// The first function to call. It greets the user.
bool Init() {
    std::cout << " ####  #####   ####  #####  ##  ##  #### " << std::endl;
    std::cout << "##     ##  ## ##  ## ##  ## ##  ## ##    " << std::endl;
    std::cout << "## ### #####  ###### #####  ######  #### " << std::endl;
    std::cout << "##  ## ##  ## ##  ## ##     ##  ##     ##" << std::endl;
    std::cout << " ####  ##  ## ##  ## ##     ##  ##  #### " << std::endl;
    std::cout << std::endl;
    std::cout << "1. Input the graph." << std::endl;
    std::cout << "2. Exit the program." << std::endl;
    std::cout << "Enter the corresponding option to continue: " << std::endl;
    std::string input;
    int option;
    bool wrong_input;

    // Try to input until the user enters the correct value.
    do {
        std::cout << ">>";
        getline(std::cin, input);
        option = std::atoi(input.c_str());
        wrong_input = input.empty() || !(option == 1 || option == 2);
        if (wrong_input)
            std::cout << "Entered option doesn't exist! Try again:" << std::endl;
    } while (wrong_input);

    // Return 'true', if user don't want to leave the program.
    return option == 1;
}

// Check file for existence.
bool FileExists(const std::string& path) {
    bool exists = false;
    std::ifstream ifs(path.c_str());
    if(ifs.is_open())
        exists = true;
    ifs.close();
    return exists;
}

// Provide the correct path of input file.
std::string EnterPath() {
    std::cout << "Enter the path:" << std::endl;
    std::string path;
    bool wrong_input;

    // While input's not correct, repeat it.
    do {
        std::cout << ">>";
        std::cin >> path;
        wrong_input = !FileExists(path);
        if (wrong_input)
            std::cout << "Wrong path! Try again:" << std::endl;
    } while (wrong_input);
    return path;
}

// Let user choose input/output stream.
// Returns the 'code' of chosen stream.
int ChooseStreamType(const std::string& type) {
    std::cout << "Select the preferred " << type << " stream:" << std::endl;
    std::cout << "1. Console." << std::endl;
    std::cout << "2. File." << std::endl;
    std::string input;
    int option;
    bool wrong_input;

    // While input's not correct, repeat it.
    do {
        std::cout << ">>";
        getline(std::cin, input);
        option = atoi(input.c_str());
        wrong_input = input.empty() || !(option >= 1 && option <= 2);
        if (wrong_input)
            std::cout << "The entered option doesn't exist! Please, try again:" << std::endl;
    } while (wrong_input);
    std::cout << std::endl;

    return option;
}

// Ask user if their graph is oriented.
// Return 'true', if the graph is oriented.
bool Oriented() {
    std::cout << "Is your graph oriented?" << std::endl;
    std::cout << "1. Yes." << std::endl << "2. No." << std::endl;
    std::string input;
    int option;
    bool wrong_input;

    // While input's not correct, repeat it.
    do {
        std::cout << ">>";
        getline(std::cin, input);
        option = atoi(input.c_str());
        wrong_input = input.empty() || !(option >= 1 && option <= 2);
        if (wrong_input)
            std::cout << "The entered option doesn't exist! Please, try again:" << std::endl;
    } while (wrong_input);

    return option == 1;
}

// Ask user for their preferred representation type.
// Return the code of chosen type.
int ChooseRepresentation(bool oriented) {
    // Print out supported types according to graph type (oriented or not).
    std::cout << std::endl << "Select the preferred representation type:" << std::endl;
    std::cout << "1. Adjacency matrix." << std::endl<< "2. Incident matrix." << std::endl;
    std::cout << "3. Adjacency list." << std::endl << "4. List of edges." << std::endl;
    std::cout << "5. FO." << std::endl << "6. MFO." << std::endl;
    if (oriented)
        std::cout << "7. FI." << std::endl << "8. MFI." << std::endl;
    else
        std::cout << "7. BFO." << std::endl << "8. BMFO." << std::endl;

    std::string input;
    int option;
    bool wrong_input;

    // While input's not correct, repeat it.
    do {
        std::cout << ">>";
        getline(std::cin, input);
        option = atoi(input.c_str());
        wrong_input = input.empty() || !(option >= 1 && option <= 10);
        if (wrong_input)
            std::cout << "The entered option doesn't exist! Please, try again:" << std::endl;
    } while (wrong_input);
    std::cout << std::endl;
    return option;
}

// Print the input manual according to chosen representation type.
void PrintInstruction(int representation_type) {
    std::cout << "To import graph properly follow the instructions written below:" << std::endl;
    switch (representation_type) {
        case 1:
            AdjacencyMatrix::PrintInstruction();
            break;
        case 2:
            IncidentMatrix::PrintInstruction();
            break;
        case 3:
            AdjacencyList::PrintInstruction();
            break;
        case 4:
            EdgesList::PrintInstruction();
            break;
        case 5:
        case 7:
            FoFi::PrintInstruction();
            break;
        case 6:
        case 8:
            MfoMfi::PrintInstruction();
            break;
    }
}

// Input of graph.
Graph Input() {
    bool oriented = Oriented();
    int representation_type = ChooseRepresentation(oriented);
    PrintInstruction(representation_type);
    IncidentMatrix graph;
    std::cout << std::endl;
    int stream_type = ChooseStreamType("input");
    if (stream_type == 1) {
        std::cout << "Please, enter your graph below following the instruction:" << std::endl;
        return Graph::Enter(std::cin, oriented, representation_type);
    } else {
        std::string path = EnterPath();
        std::ifstream ifs(path);
        auto graph = Graph::Enter(ifs, oriented, representation_type);
        ifs.close();
        return graph;
    }
}

// Output of graph.
void Output(const Graph& graph) {
    int representation_type = ChooseRepresentation(graph.GetOriented());
    int stream_type = ChooseStreamType("output");
    if (stream_type == 1) {
        graph.Display(std::cout, representation_type);
    } else {
        std::string path;
        std::cout << "Enter the path:" << std::endl << ">>";
        std::cin >> path;
        std::ofstream ofs(path);
        graph.Display(ofs, representation_type);
    }
}

// Do the requested action.
bool MenuOptions(Graph& graph, int option) {
    switch (option) {
        case 1:
            Output(graph);
            return true;
        case 2:
            graph.Degrees();
            return true;
        case 3:
            std::cout << std::endl << "Count of" << (graph.GetOriented() ? "arcs" : "edges")
            << ": " << graph.EdgesCount() << std::endl;
            return true;
        case 4:
            graph.DFS();
            return true;
        case 5:
            graph.DFSRecursiveInit();
            return true;
        case 6:
            graph.BFS();
            return true;
        case 7:
            std::cout << std::endl;
            graph = Input();
            std::cout << "New graph has been successfully imported!" << std::endl;
            return true;
        default:
            return false;
    }
}

// Print the supported action and ask the user what to do next.
bool Menu(Graph& graph) {
    std::cout << "What's next?" << std::endl;
    std::cout << "1. Display that graph." << std::endl;
    std::cout << "2. Display vertexes' degrees." << std::endl;
    std::cout << "3. Display count of edges." << std::endl;
    std::cout << "4. DFS (Non-recursive)." << std::endl;
    std::cout << "5. DFS (Recursive)." << std::endl;
    std::cout << "6. BFS." << std::endl;
    std::cout << "7. Input new graph." << std::endl;
    std::cout << "8. Exit the program." << std::endl;
    std::cout << "Enter the corresponding number to continue:" << std::endl;

    std::string input;
    int option;
    bool wrong_input;

    // While input's not correct, repeat it.
    do {
        std::cout << ">>";
        std::cin >> std::ws;
        getline(std::cin, input);
        option = atoi(input.c_str());
        wrong_input = input.empty() || !(option >= 1 && option <= 8);
        if (wrong_input)
            std::cout << "The entered option doesn't exist! Please, try again:" << std::endl;
    } while (wrong_input);
    return MenuOptions(graph, option);
}
