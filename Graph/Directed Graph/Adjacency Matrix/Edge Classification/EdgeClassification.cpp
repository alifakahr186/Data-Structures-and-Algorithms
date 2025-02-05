#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>

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
    vector<Vertex> vertices;
    vector<vector<int>> adjMatrix;
    unordered_map<int, bool> visited;
    unordered_map<int, int> startTime, finishTime;
    int time = 0;

public:
    Graph() {}

    bool checkIfVertexExistByID(int vid) {
        for (const auto &v : vertices) {
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

    int getVertexIndexByID(int vid) {
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
        adjMatrix[fromIndex][toIndex] = weight;
        cout << "Edge between " << fromVertex << " and " << toVertex << " added successfully\n";
    }

    void printGraph() {
        cout << "Graph: (Adjacency Matrix Representation)\n";
        cout << "     ";
        for (auto &vertex : vertices) {
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

    void classifyEdges() {
        time = 0;
        visited.clear();
        startTime.clear();
        finishTime.clear();

        for (auto &v : vertices) {
            if (!visited[v.getStateID()]) {
                DFS(v.getStateID());
            }
        }
    }

private:
    void DFS(int v) {
        visited[v] = true;
        startTime[v] = ++time;
        int vIndex = getVertexIndexByID(v);

        for (int uIndex = 0; uIndex < vertices.size(); ++uIndex) {
            if (adjMatrix[vIndex][uIndex] != 0) {
                int u = vertices[uIndex].getStateID();
                if (!visited[u]) {
                    cout << "Tree Edge: (" << v << " -> " << u << ")\n";
                    DFS(u);
                } else if (finishTime[u] == 0) {
                    cout << "Back Edge: (" << v << " -> " << u << ")\n";
                } else if (startTime[v] < startTime[u]) {
                    cout << "Forward Edge: (" << v << " -> " << u << ")\n";
                } else {
                    cout << "Cross Edge: (" << v << " -> " << u << ")\n";
                }
            }
        }
        finishTime[v] = ++time;
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
    int id1, id2, w;
    int option;

    do {
        cout << "What operation do you want to perform? "
                "Select Option number. Enter 0 to exit.\n";
        cout << "1. Add Vertex\n";
        cout << "2. Add Edge\n";
        cout << "3. Edge Classification" << endl;
        cout << "4. Print Graph\n";
        cout << "0. Exit Program\n";

        option = getValidIntInput("Enter option: ");
        Vertex v1;

        switch (option) {
        case 0:
            break;
            
        case 1:
            id1 = getValidIntInput("Enter State ID: ");
            sname = getValidStringInput("Enter State Name: ");
            v1 = Vertex(id1, sname);
            graph.addVertex(v1);
            break;

        case 2:
            id1 = getValidIntInput("Enter State ID of Source Vertex: ");
            id2 = getValidIntInput("Enter State ID of Destination Vertex: ");
            w = getValidIntInput("Enter Weight of Edge: ");
            graph.addEdgeByID(id1, id2, w);
            break;

        case 4:
            cout << "Edge Classification:\n";
            graph.classifyEdges();
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
