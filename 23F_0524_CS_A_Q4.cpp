#include <iostream>
#include <climits>
using namespace std;

const int num_blocks = 5;

class road_network
{
private:
    int adjacency_matrix[num_blocks][num_blocks];

public:
    road_network(int input_matrix[num_blocks][num_blocks])
    {
        for (int i = 0; i < num_blocks; ++i)
        {
            for (int j = 0; j < num_blocks; ++j)
            {
                adjacency_matrix[i][j] = input_matrix[i][j];
            }
        }
    }

    void find_mst()
    {
        int parent[num_blocks];
        int key[num_blocks];
        bool included_in_mst[num_blocks];

        for (int i = 0; i < num_blocks; ++i)
        {
            key[i] = INT_MAX;
            included_in_mst[i] = false;
            parent[i] = -1;
        }

        key[0] = 0;

        for (int count = 0; count < num_blocks - 1; ++count)
        {
            int min_key = INT_MAX, u;

            for (int v = 0; v < num_blocks; ++v)
            {
                if (!included_in_mst[v] && key[v] < min_key)
                {
                    min_key = key[v];
                    u = v;
                }
            }

            included_in_mst[u] = true;

            for (int v = 0; v < num_blocks; ++v)
            {
                if (adjacency_matrix[u][v] && !included_in_mst[v] && adjacency_matrix[u][v] < key[v])
                {
                    key[v] = adjacency_matrix[u][v];
                    parent[v] = u;
                }
            }
        }

        int total_cost = 0;
        cout << "====== minimum spanning tree (mst) ======\n";
        cout << "edges in the mst and their distances:\n";
        for (int i = 1; i < num_blocks; ++i)
        {
            cout << "block " << parent[i] << " - block " << i
                 << " : distance " << adjacency_matrix[i][parent[i]] << " km\n";
            total_cost += adjacency_matrix[i][parent[i]];
        }
        cout << "total cost of the road network: " << total_cost << " km\n";
        cout << "=========================================\n";
    }
};

int main()
{
    int adjacency_matrix[num_blocks][num_blocks] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}};

    road_network network(adjacency_matrix);
    network.find_mst();

    return 0;
}
