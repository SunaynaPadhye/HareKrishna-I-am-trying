#include "railway.h"
#include <string.h>

// Test case structure
typedef struct {
    int positions[100];        // Array of town positions
    int num_towns;             // Number of towns
    int tolerance;             // Tolerance distance
    int expected_stations[100]; // Expected station positions
    int num_stations;          // Number of expected stations
} TestCase;

/*
 - Function to run a single test case
 - Compares the expected result with the actual output and prints pass/fail message
 */
void runTestCase(TestCase* test, int test_number) {
    // Create the linked list of town positions
    TownNode* towns = createTownList(test->positions, test->num_towns);
    StationNode* stations = findOptimalStations(towns, test->tolerance);
    
    // Collect the actual results
    int actual_stations[100];
    int count = 0;
    StationNode* curr = stations;
    while (curr) {
        actual_stations[count++] = curr->position;
        curr = curr->next;
    }
    
    // Validate the results
    if (count != test->num_stations) {
        printf("Test Case %d Failed: Expected %d stations, got %d\n", test_number, test->num_stations, count);
    } else {
        int passed = 1;
        for (int i = 0; i < count; i++) {
            if (actual_stations[i] != test->expected_stations[i]) {
                passed = 0;
                break;
            }
        }
        if (passed) {
            printf("Test Case %d Passed\n", test_number);
        } else {
            printf("Test Case %d Failed: Station positions do not match expected output\n", test_number);
        }
    }
    
    // Clean up
    freeTownList(towns);
    freeStationList(stations);
}

/*
 - Function to run all test cases
 */
void runAllTests() {
    // Define test cases
    TestCase tests[] = {
        {{4, 7, 9, 22, 33}, 5, 3, {7, 25, 36}, 3},            // Normal case with multiple towns
        {{1, 2, 3, 4, 5}, 5, 1, {2, 5}, 2},               // Small tolerance distance
        {{1, 10, 20, 30, 40}, 5, 5, {6, 25, 45}, 3},         // Larger tolerance distance
        {{0, 5, 10, 15, 20}, 5, 5, {5, 20}, 2},           // All towns evenly spaced
        {{1, 2, 4, 8, 16}, 5, 2, {3, 10, 18}, 3},             // Tolerance does not cover all towns
        {{1}, 1, 5, {6}, 1},                              // Edge case: single town
        {{1, 2}, 2, 10, {11}, 1},                         // Edge case: two towns covered by one station
        {{1, 100, 200, 300}, 4, 50, {51, 250}, 2},       // Edge case: widely spaced towns
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);
    for (int i = 0; i < num_tests; i++) {
        runTestCase(&tests[i], i + 1);
    }
}

int main() {
    printf("Running test cases for optimal railway station placement:\n");
    runAllTests();
    return 0;
}
