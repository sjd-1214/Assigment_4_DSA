#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

const int num_cities = 4;

int calculate_route_cost(int distance_matrix[num_cities][num_cities], int route[], int num_cities)
{
    int total_cost = 0;
    for (int i = 0; i < num_cities - 1; i++)
    {
        total_cost += distance_matrix[route[i]][route[i + 1]];
    }
    total_cost += distance_matrix[route[num_cities - 1]][route[0]];
    return total_cost;
}

void solve_tsp(int distance_matrix[num_cities][num_cities])
{
    int city_order[num_cities - 1];
    for (int i = 1; i < num_cities; i++)
    {
        city_order[i - 1] = i;
    }

    int min_cost = INT_MAX;
    int best_route[num_cities];

    do
    {
        int current_route[num_cities];
        current_route[0] = 0;
        for (int i = 0; i < num_cities - 1; i++)
        {
            current_route[i + 1] = city_order[i];
        }

        int current_cost = calculate_route_cost(distance_matrix, current_route, num_cities);

        if (current_cost < min_cost)
        {
            min_cost = current_cost;
            for (int i = 0; i < num_cities; i++)
            {
                best_route[i] = current_route[i];
            }
        }
    } while (next_permutation(city_order, city_order + num_cities - 1));

    cout << "===== traveling salesman problem (tsp) =====\n";
    cout << "shortest route: ";
    for (int i = 0; i < num_cities; i++)
    {
        cout << best_route[i] << " -> ";
    }
    cout << best_route[0] << endl;
    cout << "total cost: " << min_cost << "\n";
    cout << "===========================================\n";
}

int main()
{
    int distance_matrix[num_cities][num_cities] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}};

    cout << "solving tsp using brute force...\n";
    solve_tsp(distance_matrix);

    return 0;
}
