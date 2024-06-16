#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <ctime>

using namespace std;

class EdgeType;
class Edge;
class Vertex;

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
    int weight;

    Edge() {
        type = EdgeType::TREE;  // Initialize the type to TREE by default
    }
    Edge(int destVID, int w) {
        DestinationVertexID = destVID;
        weight = w;
    }
    void setEdgeValues(int destVID, int w) {
        DestinationVertexID = destVID;
        weight = w;
    }
    void setWeight(int w) {
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
    void setID(int id) {
        state_id = id;
    }
    void setStateName(string sname) {
        state_name = sname;
    }

    list<Edge> getEdgeList() {
        return edgeList;
    }

    void printEdgeList() {
        cout << "[";
        for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
            cout << it->getDestinationVertexID() << "(" << it->getWeight() << ") --> ";
        }
        cout << "]";
        cout << endl;
    }
};

class Graph {
    vector<Vertex> vertices;

public:
    bool checkIfVertexExistByID(int vid) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i).getStateID() == vid) {
                return true;
            }
        }
        return false;
    }

    void addVertex(Vertex newVertex) {
        if (checkIfVertexExistByID(newVertex.getStateID())) {
            cout << "Vertex with this ID already exists" << endl;
        } else {
            vertices.push_back(newVertex);
            cout << "New Vertex Added Successfully" << endl;
        }
    }

    Vertex getVertexByID(int vid) {
        Vertex temp;
        for (int i = 0; i < vertices.size(); i++) {
            temp = vertices.at(i);
            if (temp.getStateID() == vid) {
                return temp;
            }
        }
        return temp;
    }

    bool checkIfEdgeExistByID(int fromVertex, int toVertex) {
        Vertex v = getVertexByID(fromVertex);
        list<Edge> e
        e = v.getEdgeList();
        for (auto it = e.begin(); it != e.end(); it++) {
            if (it->getDestinationVertexID() == toVertex) {
                return true;
            }
        }
        return false;
    }

    void addEdgeByID(int fromVertex, int toVertex, int weight) {
        bool check1 = checkIfVertexExistByID(fromVertex);
        bool check2 = checkIfVertexExistByID(toVertex);

        if (check1 && check2) {
            if (checkIfEdgeExistByID(fromVertex, toVertex)) {
                cout << "Edge from " << fromVertex << " to " << toVertex << " already exists" << endl;
            } else {
                for (int i = 0; i < vertices.size(); i++) {
                    if (vertices.at(i).getStateID() == fromVertex) {
                        Edge e(toVertex, weight);
                        vertices.at(i).edgeList.push_back(e);
                        cout << "Edge from " << fromVertex << " to " << toVertex << " added Successfully" << endl;
                        break; // Since it's directed, add only one way and then stop
                    }
                }
            }
        } else {
            cout << "Invalid Vertex ID entered." << endl;
        }
    }

    vector<Vertex> vertices;
    unordered_map<int, bool> visited;
    unordered_map<int, int> startTime;
    unordered_map<int, int> finishTime;
    int time;

    void DFS(int startVertexID) {
        time = 0; 
        visited.clear(); 
        startTime.clear(); 
        finishTime.clear(); 

        if (!visited[startVertexID]) {
            DFSVisit(getVertexByID(startVertexID)); // Start DFS from the specified vertex
        }

        // Optionally, continue DFS for any unvisited vertices
        for (auto &vertex : vertices) {
            if (!visited[vertex.getStateID()]) {
                DFSVisit(vertex);
            }
        }
    }

    void printEdgeClassification() {
        cout << "Edge Classification:" << endl;

        for (int i = 0; i < vertices.size(); i++) {
            for (Edge &e : vertices[i].edgeList) {
                
                cout << "Edge from " << vertices[i].getStateID() << " to " << e.DestinationVertexID << ": ";
                switch (e.type) {
                    case TREE:
                        cout << "Tree Edge";
                        break;
                    case FORWARD:
                        cout << "Forward Edge";
                        break;
                    case BACKWARD:
                        cout << "Backward Edge";
                        break;
                    case CROSS:
                        cout << "Cross Edge";
                        break;
                }
                cout << endl;
            }
        }
    }


    void printGraph() {
        for (int i = 0; i < vertices.size(); i++) {
            Vertex temp;
            temp = vertices.at(i);
            cout << temp.getStateName() << " (" << temp.getStateID() << ") --> ";
            temp.printEdgeList();
        }
    }

    private:
    void DFSVisit(Vertex &v) {
        visited[v.getStateID()] = true;
        startTime[v.getStateID()] = ++time;

        for (int i = 0; i < v.edgeList.size(); i++) {
            Edge &e = v.edgeList[i];
            if (!visited[e.DestinationVertexID]) {
                e.type = TREE;
                DFSVisit(vertices[e.DestinationVertexID]);
            } else {
                if (startTime[v.getStateID()] < startTime[e.DestinationVertexID]) {
                    e.type = FORWARD;
                } else if (startTime[v.getStateID()] > startTime[e.DestinationVertexID]) {
                    e.type = BACKWARD;
                } else {
                    e.type = CROSS;
                }
            }
        }

        finishTime[v.getStateID()] = ++time;
    }
};

int main() {
    Graph g;
    string sname;
    int id1, id2, w;
    int option;

    do {
        cout << "What operation do you want to perform? "
             << "Select Option number. Enter 0 to exit." << endl;
        cout << "1. Add Vertex" << endl;
        cout << "2. Add Edge" << endl;
        cout << "3. Edge Classification" << endl;
        cout << "4. Print Graph" << endl;
        cout << "0. Exit Program" << endl;

        cin >> option;
        Vertex v1;

        switch (option) {
        case 0:
            break;

        case 1:
            cout << "Add Vertex Operation -" << endl;
            cout << "Enter State ID: ";
            cin >> id1;
            cout << "Enter State Name: ";
            cin >> sname;
            v1.setID(id1);
            v1.setStateName(sname);
            g.addVertex(v1);
            break;

        case 2:
            cout << "Add Edge Operation -" << endl;
            cout << "Enter ID of Source Vertex(State): ";
            cin >> id1;
            cout << "Enter ID of Destination Vertex(State): ";
            cin >> id2;
            cout << "Enter Weight of Edge: ";
            cin >> w;
            g.addEdgeByID(id1, id2, w);
            break;

        case 3:
            cout << "DFS Edge Classification Operation -" << endl;
            cout << "Enter ID of Starting Vertex: ";
            cin >> id1;
            g.DFS(id1); 
            g.printEdgeClassification(); 
            break;

        case 4:
            cout << "Print Graph Operation -" << endl;
            g.printGraph();
            break;

        default:
            cout << "Enter Proper Option number" << endl;
        }
        cout << endl;

    } while (option != 0);

    return 0;
}
