#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

const int num_cities = 4;

int calculate_route_cost(int distance_matrix[num_cities][num_cities], int route[]) {
    int total_cost = 0;
    for (int i = 0; i < num_cities - 1; i++) {
        total_cost += distance_matrix[route[i]][route[i + 1]];
    }
    total_cost += distance_matrix[route[num_cities - 1]][route[0]];
    return total_cost;
}

void solve_tsp(int distance_matrix[num_cities][num_cities]) {
    int city_order[num_cities - 1];
    for (int i = 1; i < num_cities; i++) {
        city_order[i - 1] = i;
    }

    int minimum_cost = INT_MAX;
    int optimal_route[num_cities];

    do {
        int current_route[num_cities];
        current_route[0] = 0;
        for (int i = 0; i < num_cities - 1; i++) {
            current_route[i + 1] = city_order[i];
        }

        int current_cost = calculate_route_cost(distance_matrix, current_route);

        if (current_cost < minimum_cost) {
            minimum_cost = current_cost;
            for (int i = 0; i < num_cities; i++) {
                optimal_route[i] = current_route[i];
            }
        }
    } while (next_permutation(city_order, city_order + num_cities - 1));

    cout << "\n-------------------------------------------\n";
    cout << "             Traveling Salesman             \n";
    cout << "-------------------------------------------\n";
    cout << "Shortest Route: ";
    for (int i = 0; i < num_cities; i++) {
        cout << optimal_route[i] << " -> ";
    }
    cout << optimal_route[0] << endl;
    cout << "Total Cost: " << minimum_cost << "\n";
    cout << "-------------------------------------------\n";
}

void display_menu() {
    cout << "\n======== Traveling Salesman Problem ========\n";
    cout << "1. Solve TSP (Default Distance Matrix)\n";
    cout << "2. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
}

int main() {
    int distance_matrix[num_cities][num_cities] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int choice;
    do {
        display_menu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nSolving TSP using brute force...\n";
                solve_tsp(distance_matrix);
                break;

            case 2:
                cout << "\nExiting program. Goodbye!\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
                break;
        }
    } while (choice != 2);

    return 0;
}
