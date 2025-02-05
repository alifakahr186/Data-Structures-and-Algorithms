#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Vertex {
public:
    int state_id;
    string state_name;

    Vertex() : state_id(0), state_name("") {}
    Vertex(int id, string sname) : state_id(id), state_name(sname) {}

    int getStateID() const { return state_id; }
    string getStateName() const { return state_name; }
};

class Graph {
    vector<Vertex> vertices;
    vector<vector<int>> adjMatrix; // Adjacency Matrix

public:
    Graph() {}

    bool checkIfVertexExistByID(int vid) const {
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
        cout << "New Vertex Added Successfully\n";
    }

    int getVertexIndexByID(int vid) const {
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i].getStateID() == vid) return i;
        }
        return -1;
    }

    void addEdgeByID(int fromVertex, int toVertex, int weight) {
        int fromIndex = getVertexIndexByID(fromVertex);
        int toIndex = getVertexIndexByID(toVertex);

        if (fromIndex == -1 || toIndex == -1) {
            cout << "Invalid Vertex ID entered.\n";
            return;
        }

        // Add the edge in both directions for an undirected graph
        adjMatrix[fromIndex][toIndex] = weight;
        adjMatrix[toIndex][fromIndex] = weight;

        cout << "Edge between " << fromVertex << " and " << toVertex << " added successfully.\n";
    }

    void deleteVertexByID(int vid) {
        int vIndex = getVertexIndexByID(vid);
        if (vIndex == -1) {
            cout << "Vertex with ID " << vid << " not found.\n";
            return;
        }

        // Remove the vertex from the vertices list
        vertices.erase(vertices.begin() + vIndex);

        // Remove the corresponding row from adjacency matrix
        adjMatrix.erase(adjMatrix.begin() + vIndex);

        // Remove the corresponding column from adjacency matrix
        for (auto& row : adjMatrix) {
            row.erase(row.begin() + vIndex);
        }

        cout << "Vertex with ID " << vid << " deleted successfully.\n";
    }

    void printGraph() const {
        cout << "Graph: (Adjacency Matrix Representation)\n";
        cout << "     ";
        for (const auto& vertex : vertices) {
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

int getValidIntInput(const string& prompt) {
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

string getValidStringInput(const string& prompt) {
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
    int id1, id2, w;
    int option;

    do {
        cout << "What operation do you want to perform? "
             "Select Option number. Enter 0 to exit.\n";
        cout << "1. Add Vertex\n";
        cout << "2. Add Edge\n";
        cout << "3. Delete Vertex\n";
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
            w = getValidIntInput("Enter Weight of Edge: ");
            graph.addEdgeByID(id1, id2, w);
            break;

        case 3:
            id1 = getValidIntInput("Enter State ID of Vertex to Delete: ");
            graph.deleteVertexByID(id1);
            break;

        case 4:
            cout << "Print Graph Operation -\n";
            graph.printGraph();
            break;

        default:
            cout << "Enter a valid option number.\n";
        }
        cout << endl;

    } while (option != 0);

    return 0;
}
