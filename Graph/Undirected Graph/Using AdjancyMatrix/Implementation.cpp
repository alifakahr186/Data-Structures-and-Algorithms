#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Vertex {
public:
    int state_id;
    string state_name;

    Vertex() : state_id(0), state_name("") {}
    Vertex(int id, string sname) : state_id(id), state_name(sname) {}

    int getStateID() { return state_id; }
    string getStateName() { return state_name; }
    void setID(int id) { state_id = id; }
    void setStateName(string sname) { state_name = sname; }
};

class Graph {
    vector<Vertex> vertices;
    vector<vector<int>> adjMatrix; // Adjacency Matrix

public:
    Graph() {}

    void addVertex(const Vertex& newVertex) {
        for (auto& vertex : vertices) {
            if (vertex.getStateID() == newVertex.getStateID()) {
                cout << "Vertex with this ID already exists" << endl;
                return;
            }
        }
        vertices.push_back(newVertex);
        // Resize the adjacency matrix every time a new vertex is added
        int newSize = vertices.size();
        adjMatrix.resize(newSize);
        for (auto& row : adjMatrix) {
            row.resize(newSize, 0); // Initialize new elements to 0
        }
        cout << "New Vertex Added Successfully" << endl;
    }

    void addEdgeByID(int fromVertex, int toVertex, int weight) {
        int fromIndex = -1, toIndex = -1;

        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i].getStateID() == fromVertex) fromIndex = i;
            if (vertices[i].getStateID() == toVertex) toIndex = i;
        }

        if (fromIndex == -1 || toIndex == -1) {
            cout << "Invalid Vertex ID entered." << endl;
            return;
        }

        // Since it's an undirected graph, we add the edge in both directions
        adjMatrix[fromIndex][toIndex] = weight;
        adjMatrix[toIndex][fromIndex] = weight;

        cout << "Edge between " << fromVertex << " and " << toVertex << " added successfully" << endl;
    }

    void printGraph() {
        cout << "Graph: (Adjacency Matrix Representation)" << endl;
        for (int i = 0; i < vertices.size(); ++i) {
            cout << vertices[i].getStateName() << " (" << vertices[i].getStateID() << ") --> ";
            for (int j = 0; j < vertices.size(); ++j) {
                // Print edge weights; 0 indicates no edge
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g;
    string sname;
    int id1, id2, w;
    int option;

    do {
        cout << "What operation do you want to perform? Select Option number. Enter 0 to exit." << endl;
        cout << "1. Add Vertex" << endl;
        cout << "2. Add Edge" << endl;
        cout << "3. Print Graph" << endl;
        cout << "0. Exit Program" << endl;

        cin >> option;

        switch (option) {
            case 0:
                cout << "Exiting program..." << endl;
                break;

            case 1:
                cout << "Add Vertex Operation -" << endl;
                cout << "Enter State ID: ";
                cin >> id1;
                cout << "Enter State Name: ";
                cin >> sname;
                {
                    Vertex v1(id1, sname);
                    g.addVertex(v1);
                }
                break;

            case 2:
                cout << "Add Edge Operation -" << endl;
                cout << "Enter ID of Source Vertex(State): ";
                cin >> id1;
                cout << "Enter ID of Destination Vertex(State): ";
                cin >> id2;
                cout << "Enter Weight of Edge: ";
                cin >> w;
                g.addEdgeByID(id1, id2, w);
                break;

            case 3:
                cout << "Print Graph Operation -" << endl;
                g.printGraph();
                break;

            default:
                cout << "Enter Proper Option number " << endl;
        }

        cout << endl;

    } while (option != 0);

    return 0;
}

