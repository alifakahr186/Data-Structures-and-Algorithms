#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <tuple>
#include <limits>

using namespace std;

class Edge;
class Vertex;

class Edge {
public:
    int DestinationVertexID;
    int weight;

    Edge() {}
    Edge(int destVID, int w) : DestinationVertexID(destVID), weight(w) {}

    int getDestinationVertexID() {
        return DestinationVertexID;
    }

    int getWeight() {
        return weight;
    }
};

class Vertex {
public:
    int state_id;
    string state_name;
    list<Edge> edgeList;

    Vertex() : state_id(0), state_name("") {}

    Vertex(int id, string sname) : state_id(id), state_name(sname) {}

    int getStateID() {
        return state_id;
    }

    string getStateName() {
        return state_name;
    }

    void printEdgeList() {
        cout << "[";
        if (!edgeList.empty()) {
            for (auto it = edgeList.begin(); it != edgeList.end(); ++it) {
                cout << it->getDestinationVertexID() << "(" << it->getWeight() << ")";
                if (next(it) != edgeList.end()) {
                    cout << " --> ";
                }
            }
        }
        cout << "]\n";
    }
};

class Graph {
    unordered_map<int, Vertex> vertices; // Change from vector to map

public:
    bool checkIfVertexExistByID(int vid) {
        return vertices.find(vid) != vertices.end();
    }

    void addVertex(Vertex newVertex) {
        if (checkIfVertexExistByID(newVertex.getStateID())) {
            cout << "Vertex with this ID already exists.\n";
        } else {
            vertices[newVertex.getStateID()] = newVertex;
            cout << "New Vertex Added Successfully\n";
        }
    }

    Vertex* getVertexByID(int vid) {
        auto it = vertices.find(vid);
        if (it != vertices.end()) {
            return &it->second;
        }
        return nullptr;
    }

    bool checkIfEdgeExistByID(int fromVertex, int toVertex) {
        Vertex* vFrom = getVertexByID(fromVertex);
        Vertex* vTo = getVertexByID(toVertex);

        if (vFrom && vTo) {
            for (auto& edge : vFrom->edgeList) {
                if (edge.getDestinationVertexID() == toVertex) {
                    return true;
                }
            }

            for (auto& edge : vTo->edgeList) {
                if (edge.getDestinationVertexID() == fromVertex) {
                    return true;
                }
            }
        }
        return false;
    }

    void addEdgeByID(int fromVertex, int toVertex, int weight, bool isDirected = false) {
        Vertex* fromV = getVertexByID(fromVertex);
        Vertex* toV = getVertexByID(toVertex);

        if (fromV && toV) {
            if (checkIfEdgeExistByID(fromVertex, toVertex)) {
                cout << "Edge between " << fromVertex << " and " << toVertex << " already exists.\n";
            } else {
                fromV->edgeList.push_back(Edge(toVertex, weight));
                if (!isDirected) {
                    toV->edgeList.push_back(Edge(fromVertex, weight));  // Add reverse edge for undirected graph
                }
                cout << "Edge added successfully.\n";
            }
        } else {
            cout << "Invalid vertex ID(s) entered.\n";
        }
    }

    void makeSet(unordered_map<int, int>& parent, unordered_map<int, int>& rank) {
        for (const auto& vertexPair : vertices) {
            int id = vertexPair.first;
            parent[id] = id;
            rank[id] = 0;
        }
    }

    int find(unordered_map<int, int>& parent, int node) {
        if (parent[node] != node) {
            parent[node] = find(parent, parent[node]);  // Path compression
        }
        return parent[node];
    }

    void unionSets(unordered_map<int, int>& parent, unordered_map<int, int>& rank, int u, int v) {
        int rootU = find(parent, u);
        int rootV = find(parent, v);

        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

    int kruskalMST() {
        unordered_map<int, int> parent;
        unordered_map<int, int> rank;
        makeSet(parent, rank);

        vector<tuple<int, int, int>> edgeList;  // (weight, fromVertexID, toVertexID)

        for (auto& vertexPair : vertices) {
            int fromVertexID = vertexPair.first;
            for (auto& edge : vertexPair.second.edgeList) {
                int toVertexID = edge.getDestinationVertexID();
                int weight = edge.getWeight();

                if (fromVertexID < toVertexID) {
                    edgeList.push_back(make_tuple(weight, fromVertexID, toVertexID));
                }
            }
        }

        sort(edgeList.begin(), edgeList.end());

        int mstWeight = 0;
        int edgeCount = 0;

        for (const auto& [weight, fromVertexID, toVertexID] : edgeList) {
            int rootU = find(parent, fromVertexID);
            int rootV = find(parent, toVertexID);

            if (rootU != rootV) {
                mstWeight += weight;
                unionSets(parent, rank, rootU, rootV);
                edgeCount++;
            }

            if (edgeCount == vertices.size() - 1) {
                return mstWeight;
            }
        }

        cout << "Graph is not connected. MST cannot be formed.\n";
        return -1;
    }

    void printGraph() {
        for (auto& vertex : vertices) {
            cout << vertex.second.getStateName() << " (" << vertex.second.getStateID() << ") --> ";
            vertex.second.printEdgeList();
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
    int id1, id2, w;
    int option;

    do {
        cout << "What operation do you want to perform? " <<
            "Select Option number. Enter 0 to exit.\n";
        cout << "1. Add Vertex\n";
        cout << "2. Add Edge\n";
        cout << "3. Print Graph\n";
        cout << "4. Calculate MST using Kruskal Algorithm" << endl;
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
            cout << "Minimum Spanning Tree Weight: " << graph.kruskalMST() << endl;
            break;

        default:
            cout << "Enter a valid option number." << endl;
        }
        cout << endl;

    } while (option != 0);

    return 0;
}
