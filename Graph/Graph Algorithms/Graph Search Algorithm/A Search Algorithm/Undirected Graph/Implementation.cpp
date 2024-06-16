#include<iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits> // For INT_MAX
#include <utility> // For std::pair


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

    list < Edge > edgeList;

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

    list < Edge > getEdgeList() {
        return edgeList;
    }

    //  void addEdgeToEdgelist(int toVertexID, int weight)
    //  {
    //          Edge e(toVertexID,weight);
    //        edgeList.push_back(e); 
    //        cout<<"Edge between "<<state_id<<" and "<<toVertexID<<" added Successfully"<<endl;     
    //  }

    void printEdgeList() {
        cout << "[";
        for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
        cout << it -> getDestinationVertexID() << "(" << it -> getWeight() << ") --> ";
        }
        cout << "]";
        cout << endl;
    }

};

class Graph {

  vector < Vertex > vertices;

    public:

        bool checkIfVertexExistByID(int vid) {
        bool flag = false;
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i).getStateID() == vid) {
            return true;
            }
        }
        return flag;
        }

    void addVertex(Vertex newVertex) {
        bool check = checkIfVertexExistByID(newVertex.getStateID());
        if (check == true) {
        cout << "Vertex with this ID already exist" << endl;
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
        list < Edge > e;
        e = v.getEdgeList();
        bool flag = false;
        for (auto it = e.begin(); it != e.end(); it++) {
        if (it -> getDestinationVertexID() == toVertex) {
            flag = true;
            return flag;
            break;
        }

        }
        return flag;
    }

    void addEdgeByID(int fromVertex, int toVertex, int weight) {
        bool check1 = checkIfVertexExistByID(fromVertex);
        bool check2 = checkIfVertexExistByID(toVertex);

        bool check3 = checkIfEdgeExistByID(fromVertex, toVertex);
        if ((check1 && check2 == true)) {

        if (check3 == true) {
            cout << "Edge between " << getVertexByID(fromVertex).getStateName() << "(" << fromVertex << ") and " << getVertexByID(toVertex).getStateName() << "(" << toVertex << ") Already Exist" << endl;
        } else {

            for (int i = 0; i < vertices.size(); i++) {

            if (vertices.at(i).getStateID() == fromVertex) {
                Edge e(toVertex, weight);
                //edgeList.push_back(e); 
                //vertices.at(i).addEdgeToEdgelist(toVertex,weight);
                vertices.at(i).edgeList.push_back(e);
            } else if (vertices.at(i).getStateID() == toVertex) {
                Edge e(toVertex, weight);
                //edgeList.push_back(e); 
                //vertices.at(i).addEdgeToEdgelist(fromVertex,weight);
                vertices.at(i).edgeList.push_back(e);
            }
            }

            cout << "Edge between " << fromVertex << " and " << toVertex << " added Successfully" << endl;
        }
        } else {
        cout << "Invalid Vertex ID entered.";
        }
    }

    void setHeuristic(const unordered_map<int, int>& h) {
        heuristic = h;
    }

    void AStarSearch(int source, int goal) {
        if(!checkIfVertexExistByID(source) || !checkIfVertexExistByID(goal)) {
            cout << "Source or Goal vertex does not exist!" << endl;
            return;
        }

        vector<int> distance(vertices.size(), INT_MAX);
        vector<int> estimatedDistanceToGoal(vertices.size(), INT_MAX);
        vector<bool> visited(vertices.size(), false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        distance[source] = 0;
        estimatedDistanceToGoal[source] = heuristic[source]; // Initialize with heuristic estimate
        pq.push({estimatedDistanceToGoal[source], source});

        while(!pq.empty()) {
            int current = pq.top().second;
            pq.pop();

            if(current == goal) {
                cout << "Found path to goal. Distance: " << distance[goal] << endl;
                return; // Stop if we reach the goal
            }

            if(visited[current]) continue;
            visited[current] = true;

            for(Edge& edge : vertices[current].edgeList) {
                int next = edge.getDestinationVertexID();
                int weight = edge.getWeight();
                int newDist = distance[current] + weight;

                if(newDist < distance[next]) {
                    distance[next] = newDist;
                    estimatedDistanceToGoal[next] = distance[next] + heuristic[next]; // Total cost = known cost + heuristic estimate
                    pq.push({estimatedDistanceToGoal[next], next});
                }
            }
        }

        cout << "Goal not reachable from source." << endl;
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
        cout << "What operation do you want to perform? " <<
        " Select Option number. Enter 0 to exit." << endl;
        cout << "1. Add Vertex" << endl;
        cout << "2. Add Edge" << endl;
        cout << "3. Calculate Single Shortest Path Using A* Search Algorithm" << endl;
        cout << "4. Print Graph" << endl;
        cout << "0. Exit Program" << endl;

        cin >> option;
        Vertex v1;

        switch (option) { 
        case 0:

        break;

        case 1:
            cout << "Add Vertex Operation -" << endl;
            cout << "Enter State ID :";
            cin >> id1;
            cout << "Enter State Name :";
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
            int source, goal; 
            cout << "Calculate Single Shortest Path Using A* Search Algorithm" << endl;
            cout << "Enter Source Vertex ID: ";
            cin >> source;
            cout << "Enter Goal Vertex ID: ";
            cin >> goal;
            g.AStarSearch(source, goal);
            break;
            

        case 4:
            cout << "Print Graph Operation -" << endl;
            g.printGraph();

        break;

        default:
        
        cout << "Enter Proper Option number " << endl;
        }

        cout << endl;

    } while (option != 0);

    return 0;
}