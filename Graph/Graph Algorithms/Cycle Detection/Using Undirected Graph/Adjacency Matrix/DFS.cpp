#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <limits>

using namespace std;

class Vertex {
public:
    int state_id;
    string state_name;

    Vertex() {
        state_id = 0;
        state_name = "";
    }

    Vertex(int id, string sname) {
        state_id = id;
        state_name = sname;
    }
};

class Graph {
    vector<Vertex> vertices;
    vector<vector<int>> adjMatrix; // Adjacency Matrix

public:
    void addVertex(Vertex newVertex) {
        for (auto& v : vertices) {
            if (v.state_id == newVertex.state_id) {
                cout << "Vertex with this ID already exists.\n";
                return;
            }
        }
        vertices.push_back(newVertex);
        int newSize = vertices.size();
        adjMatrix.resize(newSize, vector<int>(newSize, 0));
        cout << "New Vertex Added Successfully\n";
    }

    int getVertexIndexByID(int vid) {
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i].state_id == vid) return i;
        }
        return -1;
    }

    void addEdgeByID(int fromVertex, int toVertex) {
        int fromIndex = getVertexIndexByID(fromVertex);
        int toIndex = getVertexIndexByID(toVertex);

        if (fromIndex == -1 || toIndex == -1) {
            cout << "Invalid Vertex ID entered.\n";
            return;
        }
        adjMatrix[fromIndex][toIndex] = 1;
        adjMatrix[toIndex][fromIndex] = 1;
        cout << "Edge added successfully.\n";
    }

    void detectCycleUsingDFS(int startVertexID) {
        int startIdx = getVertexIndexByID(startVertexID);
        if (startIdx == -1) {
            cout << "Vertex not found." << endl;
            return;
        }

        unordered_map<int, bool> visited;
        unordered_map<int, int> parent;
        stack<int> dfsStack;

        dfsStack.push(startIdx);
        visited[startIdx] = true;
        parent[startIdx] = -1;

        while (!dfsStack.empty()) {
            int currentIdx = dfsStack.top();
            dfsStack.pop();

            for (int neighborIdx = 0; neighborIdx < vertices.size(); ++neighborIdx) {
                if (adjMatrix[currentIdx][neighborIdx] != 0) { // Edge exists
                    if (!visited[neighborIdx]) {
                        visited[neighborIdx] = true;
                        dfsStack.push(neighborIdx);
                        parent[neighborIdx] = currentIdx;
                    } else if (parent[currentIdx] != neighborIdx) {
                        cout << "Cycle detected between " << vertices[currentIdx].state_name << " and " << vertices[neighborIdx].state_name << endl;
                        return;
                    }
                }
            }
        }

        cout << "No cycle detected.\n";
    }

    void printGraph() {
        cout << "Graph: (Adjacency Matrix Representation)\n";
        for (int i = 0; i < vertices.size(); ++i) {
            cout << vertices[i].state_name << " (" << vertices[i].state_id << ") ";
            for (int j = 0; j < vertices.size(); ++j) {
                cout << adjMatrix[i][j] << " ";
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
        cout << "3. Cycle Detection Using DFS Traversal\n";
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
            id1 = getValidIntInput("Enter Source Vertex ID: ");
            graph.detectCycleUsingDFS(id1);
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
