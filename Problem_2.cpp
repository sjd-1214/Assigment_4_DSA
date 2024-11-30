#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

#define V 4 // Number of cities

// Function to calculate the cost of a route
int calculateRouteCost(int graph[V][V], int route[], int num_cities) {
    int total_cost = 0;
    for (int i = 0; i < num_cities - 1; i++) {
        total_cost += graph[route[i]][route[i + 1]];
    }
    // Add the cost to return to the starting city
    total_cost += graph[route[num_cities - 1]][route[0]];
    return total_cost;
}

// Function to solve TSP using brute force
void solveTSP(int graph[V][V]) {
    int cities[V - 1]; // Array to store the cities (excluding the starting city 0)
    for (int i = 1; i < V; i++) { // Initialize cities array
        cities[i - 1] = i;
    }

    int min_cost = INT_MAX;
    int best_route[V];

    // Generate all permutations of the cities array
    do {
        int current_route[V];
        current_route[0] = 0; // Start at city 0
        for (int i = 0; i < V - 1; i++) {
            current_route[i + 1] = cities[i];
        }

        // Calculate the cost of the current route
        int current_cost = calculateRouteCost(graph, current_route, V);

        // Update the minimum cost and best route
        if (current_cost < min_cost) {
            min_cost = current_cost;
            for (int i = 0; i < V; i++) {
                best_route[i] = current_route[i];
            }
        }
    } while (next_permutation(cities, cities + V - 1));

    // Output the result
    cout << "Shortest Route: ";
    for (int i = 0; i < V; i++) {
        cout << best_route[i] << " ";
    }
    cout << best_route[0]; // Return to the starting city
    cout << "\nTotal Cost: " << min_cost << endl;
}

int main() {
    // Distance matrix
    int graph[V][V] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    cout << "Solving TSP using Brute Force...\n";
    solveTSP(graph);

    return 0;
}
