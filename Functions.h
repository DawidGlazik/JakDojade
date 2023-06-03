#pragma once
#include "MaintainGraph.h"

void findNeighbours(int y, int x, int width, int height, char** map, bool** visited, City* firstCity, City* Scity);

void clearVisited(bool** visited, int height, int width);

void readTo2DArray(int width, int height, char** map);

bool findLetter(int y, int x, int i, int k, int width, int height, char** map, char buffer[], City* firstCity, City* city, int* counter);

void getCityName(int i, int k, int width, int height, char** map, char buffer[], City* firstCity, City* city, int* counter);

void findCities(int width, int height, char** map, char buffer[], City* firstCity, City* city, bool** visited, int* counter);

int minDistance(int distances[], bool visited[], int counter);

void printPath(City* startCity, City* endCity, City** path, int counter);

void findShortestRoad(int counter, char source[], char destination[], City* firstCity, int option);