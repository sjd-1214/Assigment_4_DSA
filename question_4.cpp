#include <iostream>
#include <climits>
using namespace std;

const int total_blocks = 5;

class road_network {
private:
    int distance_matrix[total_blocks][total_blocks];

public:
    // Constructor to initialize the adjacency matrix
    road_network(int input_matrix[total_blocks][total_blocks]) {
        for (int i = 0; i < total_blocks; ++i) {
            for (int j = 0; j < total_blocks; ++j) {
                distance_matrix[i][j] = input_matrix[i][j];
            }
        }
    }

    // Function to find and display the Minimum Spanning Tree (MST)
    void find_minimum_spanning_tree() {
        int parent[total_blocks];          // Tracks the parent of each block in the MST
        int min_distance[total_blocks];   // Minimum distance to each block
        bool included_in_mst[total_blocks]; // Tracks if a block is included in the MST

        // Initialize all distances as infinite and MST inclusion as false
        for (int i = 0; i < total_blocks; ++i) {
            min_distance[i] = INT_MAX;
            included_in_mst[i] = false;
            parent[i] = -1;
        }

        min_distance[0] = 0; // Starting from block 0

        // Constructing MST using Prim's algorithm
        for (int count = 0; count < total_blocks - 1; ++count) {
            int minimum_key = INT_MAX, selected_block;

            // Select the block with the minimum distance not yet included in the MST
            for (int block = 0; block < total_blocks; ++block) {
                if (!included_in_mst[block] && min_distance[block] < minimum_key) {
                    minimum_key = min_distance[block];
                    selected_block = block;
                }
            }

            included_in_mst[selected_block] = true; // Include the selected block in the MST

            // Update distances for the neighboring blocks
            for (int neighbor = 0; neighbor < total_blocks; ++neighbor) {
                if (distance_matrix[selected_block][neighbor] && !included_in_mst[neighbor] && 
                    distance_matrix[selected_block][neighbor] < min_distance[neighbor]) {
                    min_distance[neighbor] = distance_matrix[selected_block][neighbor];
                    parent[neighbor] = selected_block;
                }
            }
        }

        // Display the MST and calculate the total cost
        int total_cost = 0;
        cout << "\n====== Minimum Spanning Tree (MST) ======\n";
        cout << "Edges in the MST and their distances:\n";
        cout << "-----------------------------------------\n";
        for (int block = 1; block < total_blocks; ++block) {
            cout << "Block " << parent[block] << " -> Block " << block
                 << " : Distance " << distance_matrix[block][parent[block]] << " km\n";
            total_cost += distance_matrix[block][parent[block]];
        }
        cout << "-----------------------------------------\n";
        cout << "Total Cost of the Road Network: " << total_cost << " km\n";
        cout << "=========================================\n";
    }
};

int main() {
    int road_distances[total_blocks][total_blocks] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    road_network network(road_distances);
    network.find_minimum_spanning_tree();

    return 0;
}
