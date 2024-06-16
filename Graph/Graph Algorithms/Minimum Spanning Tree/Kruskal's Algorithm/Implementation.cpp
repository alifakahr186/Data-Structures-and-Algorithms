#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <algorihtm>

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
};

class Graph {
    vector<Vertex> vertices;

public:
    bool checkIfVertexExistByID(int vid) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i).state_id == vid) {
                return true;
             }
        }
        return false;
    }

    void addVertex(Vertex newVertex) {
        bool check = checkIfVertexExistByID(newVertex.state_id);
        if (check) {
            cout << "Vertex with this ID already exists" << endl;
        } else {
            vertices.push_back(newVertex);
            cout << "New Vertex Added Successfully" << endl;
        }
    }

    Vertex getVertexByID(int vid) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i).state_id == vid) {
                return vertices.at(i);
            }
        }
        return Vertex(); // Return an empty vertex if not found
    }

    void addEdgeByID(int fromVertex, int toVertex, int weight) {
        vertices[fromVertex].edgeList.push_back(Edge(toVertex, weight));
        vertices[toVertex].edgeList.push_back(Edge(fromVertex, weight));
        cout << "Edge between " << fromVertex << " and " << toVertex << " added Successfully" << endl;
    }

    void printGraph() {
        for (int i = 0; i < vertices.size(); i++) {
            Vertex temp = vertices.at(i);
            cout << temp.state_name << " (" << temp.state_id << ") --> [";
            for (auto it = temp.edgeList.begin(); it != temp.edgeList.end(); it++) {
                cout << it->DestinationVertexID << "(" << it->weight << ") --> ";
            }
            cout << "]" << endl;
        }
    }

    <vector<int, int, int>> convertToEdgeList() {
        vector<int, int, int> edgeList;

        for (auto vertex : vertices) {
            int fromVertexID = vertex.state_id;
            for (auto edge : vertex.edgeList) {
                int toVertexID = edge.DestinationVertexID;
                int weight = edge.weight;
                // Since it's an undirected graph, add each edge only once
                bool exists = false;
                for (const auto& Edge : edgeList) {
                    if (Edge == make_tuple(fromVertexID, toVertexID, weight) ||
                        Edge == make_tuple(toVertexID, fromVertexID, weight)) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    edge List.push_back(make_tuple(fromVertexID, toVertexID, weight));
                }
            }
        }
        return edgeList;
    }

    void makeSet(vector<int> &parent, vector<int> &rank, int n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int findParent(vector<int> &parent, int node) {
        if (parent[node] == node) {
            return node;
        }
        return parent[node] = findParent(parent, parent[node]); //For path compression
    }

    void unionSet(int u, int v, vector<int> &parent, vector<int>& rank) {
        u = findParent(parent, u);
        v = findParent(parent, v);

        if (rank[u] < rank[v]) {
            parent[u] = v;
        } else if (rank[v] < rank[u]) {
            parent[v] = u;
        } else {
            parent[v] = u;
            rank[u]++;
        }
    }

    int kruskal() {
        vector<int> parent(vertices.size());
        vector<int> rank(vertices.size());
        makeSet(parent, rank, vertices.size());

        int minWeight = 0;
        vector<tuple<int, int, int>> edgeList = convertToEdgeList();

        sort(edgeList.begin(), edgeList.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
            return get<2>(a) < get<2>(b);
        });

        for (int i = 0; i < edgeList.size(); i++) {
            int u = findParent(parent, get<0>(edgeList[i]));
            int v = findParent(parent, get<1>(edgeList[i]));
            int wt = get<2>(edgeList[i]);

            if (u != v) {
                minWeight += wt;
                unionSet(u, v, parent, rank);
            }
        }
        return minWeight;
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
        cout << "4. Calculate Minimum Spanning Tree using Kruskal's Algorithm" << endl;
        cout << "0. Exit Program" << endl;

        cin >> option;

        switch (option) {
            case 0:
                break;

            case 1:
                cout << "Add Vertex Operation -" << endl;
                cout << "Enter State ID :";
                cin >> id1;
                cout << "Enter State Name :";
                cin >> sname;
                g.addVertex(Vertex(id1, sname));
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

            case 4:
                cout << "Calculate Minimum Spanning Tree using Kruskal's Algorithm -" << endl;
                cout << "Minimum Weight of Spanning Tree: " << g.kruskal() << endl;
                break;

            default:
                cout << "Enter Proper Option number " << endl;
        }

        cout << endl;

    } while (option != 0);

    return 0;
}
