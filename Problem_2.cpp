#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define V 4 // Number of cities

// Function to calculate the cost of a route
int calculateRouteCost(int graph[V][V], vector<int>& route) {
    int total_cost = 0;
    for (int i = 0; i < route.size() - 1; i++) {
        total_cost += graph[route[i]][route[i + 1]];
    }
    // Add the cost to return to the starting city
    total_cost += graph[route.back()][route[0]];
    return total_cost;
}

// Function to solve TSP using brute force
void solveTSP(int graph[V][V]) {
    vector<int> cities; // List of cities to visit
    for (int i = 1; i < V; i++) { // Start from city 1 (0 is the starting city)
        cities.push_back(i);
    }

    int min_cost = INT_MAX;
    vector<int> best_route;

    // Generate all permutations of the cities
    do {
        vector<int> current_route = {0}; // Start at city 0
        current_route.insert(current_route.end(), cities.begin(), cities.end());

        int current_cost = calculateRouteCost(graph, current_route);

        // Update the minimum cost and best route
        if (current_cost < min_cost) {
            min_cost = current_cost;
            best_route = current_route;
        }
    } while (next_permutation(cities.begin(), cities.end()));

    // Output the result
    cout << "Shortest Route: ";
    for (int city : best_route) {
        cout << city << " ";
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
