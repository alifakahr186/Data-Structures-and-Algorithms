#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <limits>
#include <unordered_map>

using namespace std;

class Edge;
class Vertex;

class Edge {
public:
    int DestinationVertexID;

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

    bool dfs(int startVertexID, unordered_map<int, bool>& visited, unordered_map<int, bool>& recStack) {
        // Mark the current node as visited and add it to the recStack
        visited[startVertexID] = true;
        recStack[startVertexID] = true;

        Vertex* currentVertex = getVertexByID(startVertexID);
        if (currentVertex) {
            for (auto& edge : currentVertex->edgeList) {
                int neighborID = edge.getDestinationVertexID();
                if (!visited[neighborID]) {
                    // Recur for the adjacent vertex
                    if (dfs(neighborID, visited, recStack))
                        return true; // Cycle found
                } else if (recStack[neighborID]) {
                    // If the neighbor is in the recursion stack, we found a cycle
                    return true; 
                }
            }
        }

        // Remove the vertex from the recursion stack
        recStack[startVertexID] = false;
        return false;
    }

    bool hasCycle() {
        unordered_map<int, bool> visited;
        unordered_map<int, bool> recStack;

        for (auto& vertex : vertices) {
            if (!visited[vertex.getStateID()]) {
                if (dfs(vertex.getStateID(), visited, recStack)) {
                    return true; // Cycle detected
                }
            }
        }
        return false;
    }

    bool topologicalSort() {
        if (hasCycle()) {
            cout << "Topological sort not possible due to a cycle in the graph.\n";
            return false;
        }

        unordered_map<int, int> indegree;
        queue<int> zeroIndegreeQueue;
        vector<int> topologicalOrder;

        // Initialize all indegrees to 0
        for (auto& vertex : vertices) {
            indegree[vertex.getStateID()] = 0;
        }

        // Compute indegrees for each vertex
        for (auto& vertex : vertices) {
            for (auto& edge : vertex.edgeList) {
                indegree[edge.getDestinationVertexID()]++;
            }
        }

        // Add all vertices with indegree 0 to the queue
        for (auto& vertex : vertices) {
            if (indegree[vertex.getStateID()] == 0) {
                zeroIndegreeQueue.push(vertex.getStateID());
            }
        }

        // Process the nodes in zeroIndegreeQueue
        while (!zeroIndegreeQueue.empty()) {
            int current = zeroIndegreeQueue.front();
            zeroIndegreeQueue.pop();
            topologicalOrder.push_back(current);

            Vertex* currentVertex = getVertexByID(current);
            if (currentVertex) {
                for (auto& edge : currentVertex->edgeList) {
                    int neighborID = edge.getDestinationVertexID();
                    indegree[neighborID]--;
                    if (indegree[neighborID] == 0) {
                        zeroIndegreeQueue.push(neighborID);
                    }
                }
            }
        }

        // If topologicalOrder doesn't contain all vertices, a cycle exists
        if (topologicalOrder.size() != vertices.size()) {
            cout << "Topological sort not possible due to a cycle in the graph.\n";
            return false;
        }
        else{
            cout << "Topological Sort Order: ";
            for (int vertexID : topologicalOrder) {
                cout << vertexID << " ";
            }
        }

        cout << endl;
        return true;
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
    int id1, id2;
    int option;

    do {
        cout << "What operation do you want to perform? " <<
            "Select Option number. Enter 0 to exit.\n";
        cout << "1. Add Vertex\n";
        cout << "2. Add Edge\n";
        cout << "3. Topological Sort" << endl;
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
            graph.topologicalSort();
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
