#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <string>
#include <unordered_map>
#include <queue>

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
    unordered_map<int, int> heuristic;

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

    void addEdgeByID(int fromVertex, int toVertex, int weight) {
        Vertex* fromV = getVertexByID(fromVertex);
        Vertex* toV = getVertexByID(toVertex);

        if (fromV && toV) {
            if (checkIfEdgeExistByID(fromVertex, toVertex)) {
                cout << "Edge between " << fromVertex << " and " << toVertex << " already exists.\n";
            } else {
                fromV->edgeList.push_back(Edge(toVertex, weight));  // Only add the edge in one direction
                cout << "Directed edge added successfully from " << fromVertex << " to " << toVertex << ".\n";
            }
        } else {
            cout << "Invalid vertex ID(s) entered.\n";
        }
    }

    void AStarSearch(int startVertexID, int goalVertexID, unordered_map<int, int>& distance) {
        if (!checkIfVertexExistByID(startVertexID) || !checkIfVertexExistByID(goalVertexID)) {
            cout << "Start or goal vertex not found." << endl;
            return;
        }

        unordered_map<int, int> parent;
        unordered_map<int, bool> visited;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        for (auto& vertex : vertices) {
            distance[vertex.getStateID()] = INT_MAX;
            visited[vertex.getStateID()] = false;
        }

        distance[startVertexID] = 0;
        pq.push({0, startVertexID});
        parent[startVertexID] = -1;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (u == goalVertexID) {
                cout << "Goal reached.\n";
                printPath(parent, goalVertexID);
                return;
            }

            if (visited[u]) continue;
            visited[u] = true;

            Vertex* vertex = getVertexByID(u);
            for (auto& edge : vertex->edgeList) {
                int neighborID = edge.getDestinationVertexID();
                int weight = edge.getWeight();
                int newDist = distance[u] + weight;

                if (!visited[neighborID] && newDist < distance[neighborID]) {
                    distance[neighborID] = newDist;
                    int estimatedCost = distance[neighborID] + heuristic[neighborID];
                    pq.push({estimatedCost, neighborID});
                    parent[neighborID] = u;
                }
            }
        }

        cout << "Goal not reachable from source." << endl;
    }

    void setHeuristic(unordered_map<int, int>& h) {
        heuristic = h;
    }

    void findShortestPath(int startVertexID, int endVertexID) {
        unordered_map<int, int> distance;
        AStarSearch(startVertexID, endVertexID, distance);

        if (distance[endVertexID] == INT_MAX) {
            cout << "No path exists." << endl;
        } else {
            cout << " Shortest path distance from vertex " << startVertexID << " to vertex " << endVertexID << ": " << distance[endVertexID] << endl;
        }
    }

    void printPath(const unordered_map<int, int>& parent, int goalVertexID) {
        if (parent.at(goalVertexID) == -1) {
            cout << goalVertexID;
            return;
        }
        printPath(parent, parent.at(goalVertexID));
        cout << " -> " << goalVertexID;
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

    unordered_map<int, int> heuristicMap = {
        {0, 5}, 
        {1, 3},
        {2, 4},
        {3, 2},
        {4, 6},
        {5, 0}
    };

    graph.setHeuristic(heuristicMap);

    do {
        cout << "What operation do you want to perform? Select Option number. Enter 0 to exit.\n";
        cout << "1. Add Vertex\n";
        cout << "2. Add Edge\n";
        cout << "3. Calculate Single Shortest Path Using A* Search Algorithm\n";
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
            id1 = getValidIntInput("Enter Start Vertex ID: ");
            id2 = getValidIntInput("Enter End Vertex ID: ");
            graph.findShortestPath(id1, id2);
            break;

        case 4:
            graph.printGraph();
            break;

        default:
            cout << "Enter a valid option number." << endl;
        }
        cout << endl;

    } while (option != 0);

    return 0;
}
