#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

#define NumCities 4

int calculateRouteCost(int distanceMatrix[NumCities][NumCities], int route[], int numCities) {
    int totalCost = 0;
    for (int i = 0; i < numCities - 1; i++) {
        totalCost += distanceMatrix[route[i]][route[i + 1]];
    }
    totalCost += distanceMatrix[route[numCities - 1]][route[0]];
    return totalCost;
}

void solveTsp(int distanceMatrix[NumCities][NumCities]) {
    int cityOrder[NumCities - 1];
    for (int i = 1; i < NumCities; i++) {
        cityOrder[i - 1] = i;
    }

    int minCost = INT_MAX;
    int bestRoute[NumCities];

    do {
        int currentRoute[NumCities];
        currentRoute[0] = 0;
        for (int i = 0; i < NumCities - 1; i++) {
            currentRoute[i + 1] = cityOrder[i];
        }

        int currentCost = calculateRouteCost(distanceMatrix, currentRoute, NumCities);

        if (currentCost < minCost) {
            minCost = currentCost;
            for (int i = 0; i < NumCities; i++) {
                bestRoute[i] = currentRoute[i];
            }
        }
    } while (next_permutation(cityOrder, cityOrder + NumCities - 1));

    cout << "===== Traveling Salesman Problem (TSP) =====\n";
    cout << "Shortest Route: ";
    for (int i = 0; i < NumCities; i++) {
        cout << bestRoute[i] << " -> ";
    }
    cout << bestRoute[0] << endl;
    cout << "Total Cost: " << minCost << "\n";
    cout << "===========================================\n";
}

int main() {
    int distanceMatrix[NumCities][NumCities] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    cout << "Solving TSP using Brute Force...\n";
    solveTsp(distanceMatrix);

    return 0;
}
