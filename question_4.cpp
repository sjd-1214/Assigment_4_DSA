#include <iostream>
#include <climits>
using namespace std;

const int numBlocks = 5;

class RoadNetwork {
private:
    int adjacencyMatrix[numBlocks][numBlocks];

public:
    RoadNetwork(int inputMatrix[numBlocks][numBlocks]) {
        for (int i = 0; i < numBlocks; ++i) {
            for (int j = 0; j < numBlocks; ++j) {
                adjacencyMatrix[i][j] = inputMatrix[i][j];
            }
        }
    }

    void findMst() {
        int parent[numBlocks];
        int key[numBlocks];
        bool includedInMst[numBlocks];

        for (int i = 0; i < numBlocks; ++i) {
            key[i] = INT_MAX;
            includedInMst[i] = false;
            parent[i] = -1;
        }

        key[0] = 0;

        for (int count = 0; count < numBlocks - 1; ++count) {
            int minKey = INT_MAX, u;

            for (int v = 0; v < numBlocks; ++v) {
                if (!includedInMst[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }

            includedInMst[u] = true;

            for (int v = 0; v < numBlocks; ++v) {
                if (adjacencyMatrix[u][v] && !includedInMst[v] && adjacencyMatrix[u][v] < key[v]) {
                    key[v] = adjacencyMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        int totalCost = 0;
        cout << "====== Minimum Spanning Tree (MST) ======\n";
        cout << "Edges in the MST and their distances:\n";
        for (int i = 1; i < numBlocks; ++i) {
            cout << "Block " << parent[i] << " - Block " << i 
                 << " : Distance " << adjacencyMatrix[i][parent[i]] << " km\n";
            totalCost += adjacencyMatrix[i][parent[i]];
        }
        cout << "Total cost of the road network: " << totalCost << " km\n";
        cout << "=========================================\n";
    }
};

int main() {
    int adjacencyMatrix[5][5] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    RoadNetwork network(adjacencyMatrix);
    network.findMst();

    return 0;
}
