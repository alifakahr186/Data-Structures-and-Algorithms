#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <queue>
#include <limits>
#include <string>
#include <climits>

using namespace std;

class Edge {
public:
    int DestinationVertexID;
    int capacity;
    int flow;

    Edge() {}
    Edge(int destVID, int c) {
        DestinationVertexID = destVID;
        capacity = c;
        flow = 0;
    }

    int getDestinationVertexID() {
        return DestinationVertexID;
    }

    int getCapacity() {
        return capacity;
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
        for (auto it = edgeList.begin(); it != edgeList.end(); ++it) {
            cout << it->DestinationVertexID << "(" << it->capacity << ")";
            if (next(it) != edgeList.end()) {
                cout << " --> ";
            }
        }
        cout << "]\n";
    }
};

class Graph {
    vector<Vertex> vertices;
    unordered_map<int, unordered_map<int, int>> residualCapacity;

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

    void addEdgeByID(int fromVertex, int toVertex, int capacity) {
        Vertex* fromV = getVertexByID(fromVertex);
        Vertex* toV = getVertexByID(toVertex);

        if (fromV && toV) {
            if (checkIfEdgeExistByID(fromVertex, toVertex)) {
                cout << "Edge between " << fromVertex << " and " << toVertex << " already exists.\n";
            }else{
                fromV->edgeList.push_back(Edge(toVertex, capacity));
                residualCapacity[fromVertex][toVertex] = capacity;  // Set capacity in the residual graph
                residualCapacity[toVertex][fromVertex] = 0;  // Reverse edge capacity in residual graph
                cout << "Directed edge added successfully from " << fromVertex << " to " << toVertex << ".\n";
            }
        } else {
            cout << "Invalid vertex ID(s) entered.\n";
        }
    }

    bool isValidSource(int sourceID) {
        Vertex* sourceVertex = getVertexByID(sourceID);
        if (!sourceVertex) return false;

        for (auto& vertex : vertices) {
            for (auto& edge : vertex.edgeList) {
                int neighborID = edge.getDestinationVertexID();  

                if (neighborID == sourceID) {
                    return false;  
                }
            }
        }
        return true;
    }

    bool isValidSink(int sinkID) {
        Vertex* sinkVertex = getVertexByID(sinkID);
        if (!sinkVertex) return false;

        return sinkVertex->edgeList.empty();  // A valid sink should have no outward edges
    }

    bool BFS(int source, int sink, unordered_map<int, int>& parent) {
        unordered_map<int, bool> visited;
        queue<int> bfsQueue;
        bfsQueue.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!bfsQueue.empty()) {
            int currentVertexID = bfsQueue.front();
            bfsQueue.pop();
            
            Vertex* currentVertex = getVertexByID(currentVertexID);  
            for (auto& edge : currentVertex->edgeList) {
                int neighborID = edge.getDestinationVertexID();  

                if (!visited[neighborID] && residualCapacity[currentVertexID][neighborID] > 0) {
                    parent[neighborID] = currentVertexID;
                    visited[neighborID] = true;
                    
                    if (neighborID == sink) {
                        return true;
                    }
                    bfsQueue.push(neighborID);
                }
            }
        }

        return false;
   
    }

    int fordFulkerson(int source, int sink) {
        if (!checkIfVertexExistByID(source) || !checkIfVertexExistByID(sink)) {
            cout << "One or both of the specified vertices do not exist." << endl;
            return 0;
        }
        
        if(!isValidSource(source)){
            cout << "The source vertex is not correct. " << endl;
            return 0;
        }

        if(!isValidSink(sink)){
            cout << "The sink vertex is not correct. " << endl;
            return 0;
        }

        unordered_map<int, int> parent;
        int maxFlow = 0;

        while (BFS(source, sink, parent)) {
            int pathFlow = INT_MAX; 
            int currentNode = sink;          

            // Find the maximum flow through the path found by BFS
            while (currentNode != source) {
                int previousNode = parent[currentNode];  
                pathFlow = min(pathFlow, residualCapacity[previousNode][currentNode]);
                currentNode = previousNode;  
            }
            
            // Update residual capacities of the edges and reverse edges along the path
            currentNode = sink; 
            while (currentNode != source) {
                int previousNode = parent[currentNode];
                
                residualCapacity[previousNode][currentNode] -= pathFlow;
                residualCapacity[currentNode][previousNode] += pathFlow;
                
                currentNode = previousNode;  
            }
            maxFlow += pathFlow;
        }
        return maxFlow;
    }

    void printGraph() {
        for (auto& vertex : vertices) {
            cout << vertex.getStateName() << " (" << vertex.getStateID() << ") --> ";
            vertex.printEdgeList();
        }
    }

};

// Utility functions for valid input
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
        if (!value.empty()) {
            return value;
        }
        cout << "Invalid input. Please enter a non-empty string.\n";
    }
}

int main() {
    Graph graph;
    string sname;
    int id1, id2;
    int option;
    int capacity;

    do {
        cout << "What operation do you want to perform? " <<
            "Select Option number. Enter 0 to exit.\n";
        cout << "1. Add Vertex\n";
        cout << "2. Add Edge\n";
        cout << "3. Calulate Maximum Flow Using Ford Fulkerson Algorithm\n";
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
            capacity = getValidIntInput("Enter Capacity: ");
            graph.addEdgeByID(id1, id2, capacity);
            break;

        case 3:
            id1 = getValidIntInput("Enter Source Vertex ID: ");
            id2 = getValidIntInput("Enter Sink Vertex ID: ");
            cout << "The maximum possible flow is: " << graph.fordFulkerson(id1, id2) << endl;
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
