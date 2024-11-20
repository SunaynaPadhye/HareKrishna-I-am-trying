#include "railway.h"

/*
 - Function to create a linked list of town positions
 - Each position from the array is added as a node in the linked list.
 - Returns the head of the town linked list.
 */
TownNode* createTownList(const int* positions, int count) {
    if (!positions || count <= 0) return NULL;
    
    TownNode* head = NULL;
    TownNode* tail = NULL;
    
    // Iterate through each town position and create a linked list node
    for (int i = 0; i < count; i++) {
        TownNode* newNode = (TownNode*)malloc(sizeof(TownNode));
        if (!newNode) return NULL;
        
        newNode->position = positions[i];
        newNode->next = NULL;
        
        // Append the node to the linked list
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    return head;
}

/*
 - Function to find the optimal placement of railway stations
 - Uses a greedy approach to place stations at maximum distance (current town position + tolerance)
 - and skips towns already covered within the tolerance range.
 - Returns the head of the stations linked list.
 */
StationNode* findOptimalStations(TownNode* towns, int tolerance) {
    if (!towns || tolerance <= 0) return NULL;
    
    StationNode* stations = NULL;
    StationNode* stationsTail = NULL;
    TownNode* curr = towns;
    
    // Traverse the list of towns
    while (curr) {
        // Determine the optimal position for the station based on current town position
        int stationPos = curr->position + tolerance;
        
        // Create a new station node at the calculated position
        StationNode* newStation = (StationNode*)malloc(sizeof(StationNode));
        if (!newStation) return NULL;
        
        newStation->position = stationPos;
        newStation->next = NULL;
        
        // Add the new station node to the station linked list
        if (!stations) {
            stations = stationsTail = newStation;
        } else {
            stationsTail->next = newStation;
            stationsTail = newStation;
        }
        
        // Move to the next town not covered by the current station
        while (curr && curr->position <= stationPos + tolerance) {
            curr = curr->next;
        }
    }
    
    return stations;
}

/*
 - Function to free memory allocated for the linked list of towns
 */
void freeTownList(TownNode* head) {
    while (head) {
        TownNode* temp = head;
        head = head->next;
        free(temp);
    }
}

/*
 - Function to free memory allocated for the linked list of stations
 */
void freeStationList(StationNode* head) {
    while (head) {
        StationNode* temp = head;
        head = head->next;
        free(temp);
    }
}

/*
 - Function to print the positions of the stations
 - Outputs each station position in the linked list.
 */
void printStations(StationNode* head) {
    printf("Optimal station positions:\n");
    while (head) {
        printf("%d ", head->position);
        head = head->next;
    }
    printf("\n");
}
