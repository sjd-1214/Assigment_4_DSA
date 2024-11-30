#include <iostream>
#include <climits>
using namespace std;

const int V = 5; // Number of blocks (vertices)

class Graph
{
private:
    int graph[V][V]; // Adjacency matrix

public:
    Graph(int g[V][V])
    {
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                graph[i][j] = g[i][j];
            }
        }
    }

    // Function to implement Prim's Algorithm for MST
    void primMST()
    {
        int parent[V]; // Array to store the constructed MST
        int key[V];    // Key values used to pick the minimum weight edge
        bool inMST[V]; // To track the vertices already included in MST

        // Initialize key values to infinity, inMST to false and parent to -1
        for (int i = 0; i < V; ++i)
        {
            key[i] = INT_MAX;
            inMST[i] = false;
            parent[i] = -1;
        }

        key[0] = 0; // Start from the first block (block 0)

        // Perform the MST construction
        for (int count = 0; count < V - 1; ++count)
        {
            int minKey = INT_MAX, u;

            // Find the vertex with the minimum key value that is not yet included in MST
            for (int v = 0; v < V; ++v)
            {
                if (!inMST[v] && key[v] < minKey)
                {
                    minKey = key[v];
                    u = v;
                }
            }

            // Include the vertex in the MST
            inMST[u] = true;

            // Update the key values and parent for adjacent vertices
            for (int v = 0; v < V; ++v)
            {
                if (graph[u][v] && !inMST[v] && graph[u][v] < key[v])
                {
                    key[v] = graph[u][v];
                    parent[v] = u;
                }
            }
        }

        // Print the MST edges and total cost
        int totalCost = 0;
        cout << "Minimum Spanning Tree (MST) edges and total cost:\n";
        for (int i = 1; i < V; ++i)
        {
            cout << "Block " << parent[i] << " - Block " << i << " with distance: " << graph[i][parent[i]] << " km\n";
            totalCost += graph[i][parent[i]];
        }
        cout << "Total cost of the road network: " << totalCost << " km\n";
    }
};

int main()
{
    // Graph representation as an adjacency matrix
    int graph[5][5] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}};

    // Create a Graph object
    Graph g(graph);

    // Find the Minimum Spanning Tree (MST) using Prim's algorithm
    g.primMST();

    return 0;
}
