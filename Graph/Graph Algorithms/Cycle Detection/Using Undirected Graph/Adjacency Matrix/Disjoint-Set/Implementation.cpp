#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <utility>
#include <unordered_map> 

using namespace std;

class Vertex {
public:
    int state_id;
    string state_name;

    Vertex() : state_id(0), state_name("") {}
    Vertex(int id, string sname) : state_id(id), state_name(sname) {}

    int getStateID() { return state_id; }
    string getStateName() { return state_name; }
};

class Graph {
private:
    vector<Vertex> vertices;
    vector<vector<int>> adjMatrix;
    vector<pair<int, int>> cycleEdges;  // To store edges of the cycle
    unordered_map<int, int> idToIndex;  // Map vertex ID to matrix index
    int nextIndex;

public:
    Graph() : nextIndex(0) {}

    bool checkIfVertexExistByID(int vid) {
        for (const auto& v : vertices) {
            if (v.getStateID() == vid) return true;
        }
        return false;
    }

    void addVertex(Vertex newVertex) {
        if (checkIfVertexExistByID(newVertex.getStateID())) {
            cout << "Vertex with this ID already exists.\n";
            return;
        }
        vertices.push_back(newVertex);
        int newSize = vertices.size();
        adjMatrix.resize(newSize, vector<int>(newSize, 0));

        // Update the idToIndex map with the new vertex
        idToIndex[newVertex.getStateID()] = newSize - 1;
        
        cout << "New Vertex Added Successfully\n";
    }

    int getVertexIndexByID(int vid) {
        auto it = idToIndex.find(vid);
        if (it != idToIndex.end()) {
            return it->second;
        }
        return -1; // Invalid vertex ID
    }

    bool checkIfEdgeExistByID(int fromVertex, int toVertex) {
        int fromIndex = getVertexIndexByID(fromVertex);
        int toIndex = getVertexIndexByID(toVertex);
        if (fromIndex == -1 || toIndex == -1) return false;
        return adjMatrix[fromIndex][toIndex] != 0; // Edge exists if not 0
    }

    void addEdgeByID(int fromVertex, int toVertex) {
        int fromIndex = getVertexIndexByID(fromVertex);
        int toIndex = getVertexIndexByID(toVertex);

        if (fromIndex == -1 || toIndex == -1) {
            cout << "Invalid Vertex ID entered.\n";
            return;
        }

        adjMatrix[fromIndex][toIndex] = 1;
        adjMatrix[toIndex][fromIndex] = 1; // Assuming an undirected graph
        cout << "Edge added successfully.\n";
    }

    void makeSet(vector<int>& parent, vector<int>& rank, int n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(vector<int>& parent, int node) {
        if (parent[node] != node) {
            parent[node] = find(parent, parent[node]);  // Path compression
        }
        return parent[node];
    }

    bool unionSets(vector<int>& parent, vector<int>& rank, int u, int v) {
        int rootU = find(parent, u);
        int rootV = find(parent, v);

        if (rootU == rootV) {
            return true;  // Cycle detected
        }

        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return false;  // No cycle detected
    }

    bool DisjointSet() {
        int n = vertices.size();
        vector<int> parent(n);
        vector<int> rank(n, 0);
        makeSet(parent, rank, n);

        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            for (size_t j = i + 1; j < adjMatrix.size(); ++j) {
                if (adjMatrix[i][j] != 0) { // Check if there is an edge
                    if (unionSets(parent, rank, i, j)) {
                        int fromVertexID = vertices[i].getStateID();
                        int toVertexID = vertices[j].getStateID();
                        cycleEdges.push_back({fromVertexID, toVertexID});
                        cout << "Cycle detected in the graph. Cycle edge: " << fromVertexID << " <--> " << toVertexID << endl;
                        return true;
                    }
                }
            }
        }

        return false;  // No cycle detected
    }

    void printCycleEdges() {
        if (cycleEdges.empty()) {
            cout << "No cycle edges found.\n";
        } else {
            cout << "Cycle edges:\n";
            for (auto& edge : cycleEdges) {
                cout << edge.first << " <--> " << edge.second << endl;
            }
        }
    }

    void printGraph() {
        cout << "Graph: (Adjacency Matrix Representation)\n";
        cout << "     ";
        for (auto& vertex : vertices) {
            cout << vertex.getStateName() << "(" << vertex.getStateID() << ") ";
        }
        cout << "\n";

        for (int i = 0; i < vertices.size(); ++i) {
            cout << vertices[i].getStateName() << "(" << vertices[i].getStateID() << ") ";
            for (int j = 0; j < vertices.size(); ++j) {
                cout << adjMatrix[i][j] << "  ";
            }
            cout << endl;
        }
    }
};

int getValidIntInput(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string getValidStringInput(string prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (value.empty()) {
            cout << "Invalid input. Please enter a non-empty string.\n";
        } else {
            return value;
        }
    }
}


int main() {
    Graph graph;
    string sname;
    int id1, id2;
    int option;

    do {
        cout << "What operation do you want to perform? Select Option number. Enter 0 to exit.\n";
        cout << "1. Add Vertex\n";
        cout << "2. Add Edge\n";
        cout << "3. Cycle detection using Disjoint-set" << endl;
        cout << "4. Print Graph\n";
        cout << "0. Exit Program\n";

        option = getValidIntInput("Enter option: ");

        switch (option) {
        case 0:
            break;

        case 1:
            id1 = getValidIntInput("Enter State ID: ");
            sname = getValidStringInput("Enter State Name: ");
            graph.addVertex(Vertex(id1, sname));
            break;

        case 2:
            id1 = getValidIntInput("Enter State ID of Source Vertex: ");
            id2 = getValidIntInput("Enter State ID of Destination Vertex: ");
            graph.addEdgeByID(id1, id2);
            break;

        case 3:
            if (graph.DisjointSet()) {
                cout << "Cycle detected in the graph.\n";
                graph.printCycleEdges();  // Print edges forming the cycle
            } else {
                cout << "No cycle detected in the graph.\n";
            }
            break;

        case 4:
            graph.printGraph();
            break;

        default:
            cout << "Enter a valid option number." << endl;
        }
        cout << endl;

    } while (option != 0);

    return 0;
}
