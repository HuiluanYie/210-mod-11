// COMSC-210 | Lab 34 | Huiluan Yie

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

const int SIZE = 11;

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

    Graph graph(edges);

    graph.printGraph();
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}