#include "railway.h"

/*
 - Main function to execute the program
 - Reads the number of towns, their positions, and the tolerance distance.
 - Outputs the optimal station positions or an error message if input is invalid.
 */
int main() {
    int n, tolerance;
    
    printf("Enter number of towns: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Error: Invalid number of towns\n");
        return 1;
    }
    
    int* positions = (int*)malloc(n * sizeof(int));
    printf("Enter positions of towns (in ascending order): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
        if (i > 0 && positions[i] <= positions[i-1]) {
            printf("Error: Positions must be in strictly ascending order\n");
            free(positions);
            return 1;
        }
    }
    
    printf("Enter tolerance distance: ");
    scanf("%d", &tolerance);
    
    if (tolerance <= 0) {
        printf("Error: Invalid tolerance distance\n");
        free(positions);
        return 1;
    }
    
    // Create linked list of town positions
    TownNode* towns = createTownList(positions, n);
    if (!towns) {
        printf("Error: Failed to create town list\n");
        free(positions);
        return 1;
    }
    
    // Find optimal stations based on tolerance distance
    StationNode* stations = findOptimalStations(towns, tolerance);
    if (!stations) {
        printf("Error: Failed to find optimal stations\n");
        freeTownList(towns);
        free(positions);
        return 1;
    }
    
    // Print the calculated station positions
    printStations(stations);
    
    // Clean up allocated memory
    freeTownList(towns);
    freeStationList(stations);
    free(positions);
    
    return 0;
}
