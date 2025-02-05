#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <unordered_map>
#include <string>

using namespace std;

class EdgeType {
public:
    enum Type {
        TREE,
        FORWARD,
        BACKWARD,
        CROSS
    };
};

class Edge {
public:
    int DestinationVertexID;
    EdgeType::Type type;

    Edge() {}
    Edge(int destVID) {
        DestinationVertexID = destVID;
    }

    int getDestinationVertexID() {
        return DestinationVertexID;
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
                cout << it->getDestinationVertexID();
                if (next(it) != edgeList.end()) {
                    cout << " --> ";
                }
            }
        }
        cout << "]\n";
    }

};

class Graph {
protected:
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
        Vertex* v = getVertexByID(fromVertex);
        if (v != nullptr) {
            for (auto& edge : v->edgeList) {
                if (edge.getDestinationVertexID() == toVertex) {
                    return true;
                }
            }
        }
        return false;
    }

    void addEdgeByID(int fromVertex, int toVertex) {
        Vertex* fromV = getVertexByID(fromVertex);
        Vertex* toV = getVertexByID(toVertex);

        if (fromV && toV) {
            if (checkIfEdgeExistByID(fromVertex, toVertex)) {
                cout << "Edge between " << fromVertex << " and " << toVertex << " already exists.\n";
            } else {
                fromV->edgeList.push_back(Edge(toVertex));  // Only add the edge in one direction
                cout << "Directed edge added successfully from " << fromVertex << " to " << toVertex << ".\n";
            }
        } else {
            cout << "Invalid vertex ID(s) entered.\n";
        }
    }

    void printGraph() {
        for (auto& vertex : vertices) {
            cout << vertex.getStateName() << " (" << vertex.getStateID() << ") --> ";
            vertex.printEdgeList();
        }
    }

};

class Classification : public Graph {
    unordered_map<int, int> startTime;
    unordered_map<int, int> finishTime;
    unordered_map<int, bool> visited;
    int time;

    // Lists to store classified edges
    list<pair<int, int>> treeEdges;
    list<pair<int, int>> forwardEdges;
    list<pair<int, int>> backwardEdges;
    list<pair<int, int>> crossEdges;

public:
    void DFS(int startVertexID) {
        if (!checkIfVertexExistByID(startVertexID)) {
            cout << "Vertex not found." << endl;
            return;
        }

        visited.clear();
        startTime.clear();
        finishTime.clear();
        time = 0;

        cout << "Depth-First Search Traversal starting from Vertex " << getVertexByID(startVertexID)->getStateName() << ":\n";
        DFSVisit(startVertexID);
        
        for (auto &vertex : vertices) {
            if (!visited[vertex.getStateID()]) {
                DFSVisit(vertex.getStateID());
            }
        }
    }

    void printEdgeClassification() {
        cout << "Edge Classification:\n";
        
        cout << "\nTREE EDGE: ";
        for (const auto &edge : treeEdges) {
            cout << "(" << edge.first << " -> " << edge.second << ") ";
        }

        cout << "\nFORWARD EDGE: ";
        for (const auto &edge : forwardEdges) {
            cout << "(" << edge.first << " -> " << edge.second << ") ";
        }

        cout << "\nBACKWARD EDGE: ";
        for (const auto &edge : backwardEdges) {
            cout << "(" << edge.first << " -> " << edge.second << ") ";
        }

        cout << "\nCROSS EDGE: ";
        for (const auto &edge : crossEdges) {
            cout << "(" << edge.first << " -> " << edge.second << ") ";
        }
        cout << endl;
    }

private:
    void DFSVisit(int vertexID) {
        visited[vertexID] = true;
        startTime[vertexID] = ++time;

        Vertex *currentVertex = getVertexByID(vertexID);
        if (!currentVertex) return;

        for (auto &edge : currentVertex->edgeList) {
            int neighborID = edge.getDestinationVertexID();

            if (!visited[neighborID]) {
                edge.type = EdgeType::TREE;
                treeEdges.emplace_back(vertexID, neighborID);
                DFSVisit(neighborID);
            } 
            else if (finishTime.find(neighborID) == finishTime.end()) {
                edge.type = EdgeType::BACKWARD;
                backwardEdges.emplace_back(vertexID, neighborID);

            } 
            else if (startTime[vertexID] < startTime[neighborID]) {
                edge.type = EdgeType::FORWARD;
                forwardEdges.emplace_back(vertexID, neighborID);

            } 
            else {
                edge.type = EdgeType::CROSS;
                crossEdges.emplace_back(vertexID, neighborID);
            }
        }
        
        finishTime[vertexID] = ++time;
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
    Classification graph;
    string sname;
    int id1, id2;
    int option;

    do {
        cout << "What operation do you want to perform? " <<
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
            graph.addEdgeByID(id1, id2);
            break;

        case 3:
            id1 = getValidIntInput("Enter State ID of Source Vertex: ");
            graph.DFS(id1); 
            graph.printEdgeClassification();
            break;

        case 4:
            cout << "Print Graph Operation -" << endl;
            graph.printGraph();
            break;

        default:
            cout << "Enter a valid option number." << endl;
        }
        cout << endl;

    } while (option != 0);

    return 0;
}
