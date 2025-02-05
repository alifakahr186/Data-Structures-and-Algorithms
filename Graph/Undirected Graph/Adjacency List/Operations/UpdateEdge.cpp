#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <limits>
#include <string>

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

    void setWeight(int newWeight) {
        weight = newWeight;
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

        // Check  both vertices exist
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

    void updateEdgeByID(int fromVertex, int toVertex, int newWeight) {
        Vertex* fromV = getVertexByID(fromVertex);
        Vertex* toV = getVertexByID(toVertex);

        if (fromV && toV) {
            // Flag to track if the edge was found
            bool edgeFound = false;

            // Update the edge from fromVertex to toVertex
            for (auto& edge : fromV->edgeList) {
                if (edge.getDestinationVertexID() == toVertex) {
                    edge.setWeight(newWeight); 
                    edgeFound = true;
                    cout << "Edge from " << fromVertex << " to " << toVertex << " updated successfully.\n";
                    break; 
                }
            }
            // Update the reverse edge from toVertex to fromVertex
            if (edgeFound) {
                for (auto& edge : toV->edgeList) {
                    if (edge.getDestinationVertexID() == fromVertex) {
                        edge.setWeight(newWeight); 
                        cout << "Edge from " << toVertex << " to " << fromVertex << " updated successfully.\n";
                        return; 
                    }
                }
            } else {
                cout << "Edge between " << fromVertex << " and " << toVertex << " does not exist.\n";
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
        cout << "3. Update Edge" << endl;
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

        case 3:
            id1 = getValidIntInput("Enter State ID of Source Vertex: ");
            id2 = getValidIntInput("Enter State ID of Destination Vertex: ");
            w = getValidIntInput("Enter Weight of Edge: ");
            graph.updateEdgeByID(id1, id2, w);
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
