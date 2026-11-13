// COMSC-210 | Lab 34 | Huiluan Yie

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <functional>
using namespace std;

const int SIZE = 11;

// This application represents a university campus shuttle network.
// Each node is a shuttle stop.
// Each edge is a direct shuttle route.
// Each weight is travel time in minutes.
const string STOP_NAMES[SIZE] =
{
    "Main Gate",
    "Library",
    "Student Center",
    "Science Hall",
    "North Dormitory",
    "Recreation Center",
    "Arts Building",
    "Parking Garage",
    "Health Center",
    "Engineering Building",
    "Stadium"
};

struct Edge
{
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph
{
public:
    // Adjacency-list representation of the graph.
    vector<vector<Pair>> adjList;

    // Constructor
    Graph(const vector<Edge>& edges)
    {
        adjList.resize(SIZE);

        // Add both directions because the graph is undirected.
        for (const Edge& edge : edges)
        {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    void printGraph()
    {
        cout << "Graph's adjacency list:\n";

        for (int i = 0; i < adjList.size(); i++)
        {
            cout << i << " --> ";

            for (Pair vertex : adjList[i])
            {
                cout << "(" << vertex.first
                     << ", " << vertex.second << ") ";
            }

            cout << '\n';
        }
    }

    void DFS(int start)
    {
        // DFS() traverses the graph depth-first.
        // arguments: starting vertex
        // returns: none

        vector<bool> visited(SIZE, false);
        stack<int> vertices;

        vertices.push(start);

        cout << "\nDFS starting from vertex "
             << start << ":\n";

        while (!vertices.empty())
        {
            int current = vertices.top();
            vertices.pop();

            if (!visited[current])
            {
                visited[current] = true;
                cout << current << ' ';

                // Add adjacent vertices to the stack.
                for (Pair neighbor : adjList[current])
                {
                    if (!visited[neighbor.first])
                    {
                        vertices.push(neighbor.first);
                    }
                }
            }
        }

        cout << '\n';
    }

    void BFS(int start)
    {
        // BFS() traverses the graph breadth-first.
        // arguments: starting vertex
        // returns: none

        vector<bool> visited(SIZE, false);
        queue<int> vertices;

        vertices.push(start);
        visited[start] = true;

        cout << "\nBFS starting from vertex "
             << start << ":\n";

        while (!vertices.empty())
        {
            int current = vertices.front();
            vertices.pop();

            cout << current << ' ';

            // Add unvisited adjacent vertices to the queue.
            for (Pair neighbor : adjList[current])
            {
                if (!visited[neighbor.first])
                {
                    visited[neighbor.first] = true;
                    vertices.push(neighbor.first);
                }
            }
        }

        cout << '\n';
    }
};

// Application function prototypes
void displayCampusNetwork(const Graph&);
void runCampusDFS(Graph&, int);
void runCampusBFS(Graph&, int);
void shortestPath(const Graph&, int);

int main()
{
    vector<Edge> edges =
    {
        // Removed original nodes 1 and 6.
        //
        // Renumbered the retained original nodes:
        // original 0 -> new 0
        // original 2 -> new 1
        // original 3 -> new 2
        // original 4 -> new 3
        // original 5 -> new 4
        //
        // Added six new nodes numbered 5 through 10.
        {0, 1, 4},
        {0, 2, 7},
        {0, 7, 6},
        {1, 2, 3},
        {1, 3, 5},
        {1, 6, 8},
        {2, 3, 4},
        {2, 4, 6},
        {2, 8, 5},
        {3, 8, 2},
        {3, 9, 4},
        {4, 5, 3},
        {4, 8, 4},
        {5, 10, 5},
        {5, 8, 7},
        {6, 7, 4},
        {6, 9, 6},
        {7, 10, 8},
        {8, 9, 3},
        {8, 10, 6},
        {9, 10, 4}
    };

    // In this application, each vertex is a campus shuttle stop,
    // each edge is a direct shuttle route, and each weight is the
    // route's travel time in minutes.
    Graph graph(edges);

    displayCampusNetwork(graph);
    runCampusDFS(graph, 0);
    runCampusBFS(graph, 0);

    return 0;
}

// function definition
void displayCampusNetwork(const Graph& graph)
{
    // displayCampusNetwork() displays the graph as a real-world
    // university campus shuttle network.
    // arguments: Graph object
    // returns: none

    cout << "Campus Shuttle Network Topology:\n";
    cout << "================================\n";

    for (int i = 0; i < SIZE; i++)
    {
        cout << "Stop " << i
             << " (" << STOP_NAMES[i]
             << ") connects to:\n";

        for (Pair route : graph.adjList[i])
        {
            cout << "  -> Stop "
                 << route.first
                 << " (" << STOP_NAMES[route.first] << ")"
                 << " - Travel time: "
                 << route.second
                 << " minutes\n";
        }
    }
}

void runCampusDFS(Graph& graph, int start)
{
    // runCampusDFS() uses DFS as a maintenance inspection route.
    // Maintenance personnel inspect one route as deeply as possible
    // before returning to inspect another part of the network.
    // arguments: Graph object and starting stop
    // returns: none

    cout << "\nCampus Maintenance Inspection:\n";
    cout << "Purpose: Inspecting all shuttle stops and routes\n";
    cout << "Starting location: Stop "
         << start << " (" << STOP_NAMES[start] << ")\n";

    graph.DFS(start);
}

void runCampusBFS(Graph& graph, int start)
{
    // runCampusBFS() uses BFS to examine shuttle stops by their
    // number of route connections from the starting location.
    // arguments: Graph object and starting stop
    // returns: none

    cout << "\nCampus Service Area Analysis:\n";
    cout << "Purpose: Examining shuttle stops layer by layer\n";
    cout << "Starting location: Stop "
         << start << " (" << STOP_NAMES[start] << ")\n";

    graph.BFS(start);
}