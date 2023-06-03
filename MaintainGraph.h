#pragma once
#include "Graph.h"

bool isDuplicate(List* firstNeighbour, char name[], int length);

City* GetLast(City* firstNode);

List* GetLast(List* firstNode);

City* findCity(City* firstCity, int height, int width);

City* findCity(City* firstCity, char name[]);

City* findCity(City* firstCity, int index);

void addCity(City* firstCity, City* newCity, char name[], int height, int width, int index);

void addNeighbour(List* firstNeighbour, List* neighbour, int length, char name[], int index);