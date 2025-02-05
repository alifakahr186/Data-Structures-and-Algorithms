#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <queue>
#include <unordered_map>

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

    int getStateID() {
        return state_id;
    }

    string getStateName() {
        return state_name;
    }
};

class Graph {
private:
    vector<Vertex> vertices;
    vector<vector<int>> adjMatrix;
    unordered_map<int, int> idToIndex;
    int nextIndex;

public:
    Graph() : nextIndex(0) {}

    bool checkIfVertexExistByID(int vid) {
        return idToIndex.find(vid) != idToIndex.end();
    }

    void addVertex(Vertex newVertex) {
        if (checkIfVertexExistByID(newVertex.getStateID())) {
            cout << "Vertex with this ID already exists.\n";
        } else {
            vertices.push_back(newVertex);
            idToIndex[newVertex.getStateID()] = nextIndex;
            adjMatrix.resize(nextIndex + 1);
            for (auto& row : adjMatrix) {
                row.resize(nextIndex + 1, numeric_limits<int>::max());
            }
            nextIndex++;
            cout << "New Vertex Added Successfully\n";
        }
    }

    Vertex* getVertexByID(int vid) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i].getStateID() == vid) {
                return &vertices[i];
            }
        }
        return nullptr;
    }

    bool checkIfEdgeExistByID(int fromVertex, int toVertex) {
        auto fromIt = idToIndex.find(fromVertex);
        auto toIt = idToIndex.find(toVertex);
        if (fromIt == idToIndex.end() || toIt == idToIndex.end()) return false;
        return adjMatrix[fromIt->second][toIt->second] != numeric_limits<int>::max();
    }

    void addEdgeByID(int fromVertex, int toVertex, int weight, bool isDirected = false) {
        auto fromIt = idToIndex.find(fromVertex);
        auto toIt = idToIndex.find(toVertex);
        if (fromIt == idToIndex.end() || toIt == idToIndex.end()) {
            cout << "Invalid vertex ID(s) entered.\n";
            return;
        }

        int fromIdx = fromIt->second, toIdx = toIt->second;
        if (adjMatrix[fromIdx][toIdx] != numeric_limits<int>::max()) {
            cout << "Edge between " << fromVertex << " and " << toVertex << " already exists.\n";
            return;
        }

        adjMatrix[fromIdx][toIdx] = weight;
        if (!isDirected) adjMatrix[toIdx][fromIdx] = weight;
        cout << "Edge added successfully.\n";
    }

    int PrimsMST(int startVertexID) {
        auto it = idToIndex.find(startVertexID);
        if (it == idToIndex.end()) {
            cout << "Vertex not found." << endl;
            return -1;
        }

        int startIdx = it->second;
        int n = adjMatrix.size();
        if (n == 0) return -1;

        vector<bool> visited(n, false);
        int mstWeight = 0, edgeCount = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, startIdx});

        while (!pq.empty()) {
            int weight = pq.top().first, u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;
            mstWeight += weight;
            edgeCount++;

            for (int v = 0; v < n; ++v) {
                int w = adjMatrix[u][v];
                if (w != numeric_limits<int>::max() && !visited[v]) {
                    pq.push({w, v});
                }
            }
        }

        if (edgeCount != n - 1) {
            cout << "Graph is not connected. MST cannot be formed.\n";
            return -1;
        }
        return mstWeight;
    }

    void printGraph() {
        for (size_t i = 0; i < vertices.size(); ++i) {
            Vertex& v = vertices[i];
            cout << v.getStateName() << " (" << v.getStateID() << ") --> [";
            bool first = true;
            for (size_t j = 0; j < adjMatrix.size(); ++j) {
                if (i == j) continue;
                if (adjMatrix[i][j] != numeric_limits<int>::max()) {
                    if (!first) cout << " --> ";
                    cout << vertices[j].getStateID() << "(" << adjMatrix[i][j] << ")";
                    first = false;
                }
            }
            cout << "]" << endl;
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
        if (value.empty()) cout << "Invalid input. Please enter a non-empty string.\n";
        else return value;
    }
}

int main() {
    Graph graph;
    string sname;
    int id1, id2, w;
    int option;

    do {
        cout << "What operation do you want to perform? " <<
            "Select Option number. Enter 0 to exit.\n";
        cout << "1. Add Vertex\n";
        cout << "2. Add Edge\n";
        cout << "3. Print Graph\n";
        cout << "4. Calculate MST using Prim's Algorithm" << endl;
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

        case 3:
            cout << "Print Graph Operation -" << endl;
            graph.printGraph();
            break;
    
        case 4:
            id1 = getValidIntInput("Enter State ID of Starting Vertex: ");
            cout << "Minimum Spanning Tree Weight: " << graph.PrimsMST(id1) << endl;  // Print MST weight
            break;

        default:
            cout << "Enter a valid option number." << endl;
        }
        cout << endl;

    } while (option != 0);

    return 0;
}