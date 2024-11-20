#ifndef RAILWAY_H
#define RAILWAY_H

#include <stdio.h>
#include <stdlib.h>

// Node structure for the list of towns
typedef struct TownNode {
    int position;
    struct TownNode* next;
} TownNode;

// Node structure for the list of station positions
typedef struct StationNode {
    int position;
    struct StationNode* next;
} StationNode;

// Function prototypes
TownNode* createTownList(const int* positions, int count);      
StationNode* findOptimalStations(TownNode* towns, int tolerance); 
void freeTownList(TownNode* head);                              
void freeStationList(StationNode* head);                        
void printStations(StationNode* head);                         

#endif
