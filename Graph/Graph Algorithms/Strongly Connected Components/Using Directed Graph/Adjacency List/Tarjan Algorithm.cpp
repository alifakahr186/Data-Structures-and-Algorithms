#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <stack>
#include <string>
#include <limits>

using namespace std;

class Edge;
class Vertex;

class Edge {
public:
    int DestinationVertexID;
    int weight;

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

   void DFS(int vertexID, unordered_map<int, bool>& visited, unordered_map<int, int>& firstVisit,
            unordered_map<int, int>& lowLink, stack<int>& st, unordered_map<int, bool>& inStack, int& time) {

        visited[vertexID] = true;
        firstVisit[vertexID] = lowLink[vertexID] = ++time;
        st.push(vertexID);
        inStack[vertexID] = true;

        Vertex* vertex = getVertexByID(vertexID);
        for (auto& edge : vertex->edgeList) {
            int neighborID = edge.getDestinationVertexID();
            if (!visited[neighborID]) {
                DFS(neighborID, visited, firstVisit, lowLink, st, inStack, time);
                lowLink[vertexID] = min(lowLink[vertexID], lowLink[neighborID]);
            } else if (inStack[neighborID]) {
                lowLink[vertexID] = min(lowLink[vertexID], firstVisit[neighborID]);
            }
        }

        if (lowLink[vertexID] == firstVisit[vertexID]) {
            cout << "SCC: ";
            while (st.top() != vertexID) {
                int v = st.top();
                cout << v << " ";
                inStack[v] = false;
                st.pop();
            }
            cout << st.top() << endl;
            inStack[st.top()] = false;
            st.pop();
        }
    }

    void tarjan() {
        unordered_map<int, bool> visited;
        unordered_map<int, int> firstVisit;
        unordered_map<int, int> lowLink;
        unordered_map<int, bool> inStack;
        stack<int> st;
        int time = 0;

        for (auto& vertex : vertices) {
            int v = vertex.getStateID();
            if (!visited[v]) {
                DFS(v, visited, firstVisit, lowLink, st, inStack, time);
            }
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
    int id1, id2;
    int option;

    do {
        cout << "What operation do you want to perform? " <<
            "Select Option number. Enter 0 to exit.\n";
        cout << "1. Add Vertex\n";
        cout << "2. Add Edge\n";
        cout << "3. Strongly Connected Components Using Tarjan's Algorithm\n";
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
            graph.tarjan();
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
