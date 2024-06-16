#include<iostream>
#include<vector>
#include<list>

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

    void printGraph() {
        for (int i = 0; i < vertices.size(); i++) {
            Vertex temp;
            temp = vertices.at(i);
            cout << temp.getStateName() << " (" << temp.getStateID() << ") --> ";
            temp.printEdgeList();
        }
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
        cout << "3. Print Graph" << endl;
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
