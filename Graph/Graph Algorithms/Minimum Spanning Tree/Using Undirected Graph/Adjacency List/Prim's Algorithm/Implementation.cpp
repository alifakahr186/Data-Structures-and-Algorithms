#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

class Edge;
class Vertex;

class Edge {
public:
    int DestinationVertexID;
    int weight;

    Edge() {}
    Edge(int destVID, int w) {
        DestinationVertexID = destVID;
        weight = w;
    }

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
    vector<Vertex> vertices;

public:
    bool checkIfVertexExistByID(int vid) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i].getStateID() == vid) {
                return true;
            }
        }
        return false;
    }

    void addVertex(Vertex newVertex) {
        if (checkIfVertexExistByID(newVertex.getStateID())) {
            cout << "Vertex with this ID already exists.\n";
        } else {
            vertices.push_back(newVertex);
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
       Vertex* vFrom = getVertexByID(fromVertex);
        Vertex* vTo = getVertexByID(toVertex);

        // Check both vertices exist
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
                    toV->edgeList.push_back(Edge(fromVertex, weight));  // Add the reverse edge for undirected graph
                }
                cout << "Edge added successfully.\n";
            }
        } else {
            cout << "Invalid vertex ID(s) entered.\n";
        }
    }

    int PrimsMST(int startVertexID) {
        if (!checkIfVertexExistByID(startVertexID)) {
            cout << "Vertex not found." << endl;
            return -1;  // Returning -1 for invalid vertex ID
        }
        
        unordered_map<int, bool> visited;
        
        int n = vertices.size();
        int mstWeight = 0;
        int edgeCount = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(make_pair(0, startVertexID));  // (weight, destinationID)

        while (!pq.empty()) {
            int u = pq.top().second;
            int w = pq.top().first;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;
            mstWeight += w;
            edgeCount++;

            Vertex* vertex = getVertexByID(u);
            if (!vertex) continue;  // Ensure vertex is valid

            for (auto& edge : vertex->edgeList) {
                int neighborID = edge.getDestinationVertexID();
                int weight = edge.getWeight();
                if (!visited[neighborID]) {
                    pq.push({weight, neighborID});
                }
            }

        }
        // MST complete once we add n-1 edges
        if (edgeCount != n - 1) {
            cout << "Graph is not connected. MST cannot be formed.\n";
            return -1;
        }

        return mstWeight;
    }

    void printGraph() {
        for (auto& vertex : vertices) {
            cout << vertex.getStateName() << " (" << vertex.getStateID() << ") --> ";
            vertex.printEdgeList();
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
