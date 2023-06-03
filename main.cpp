#include "Functions.h"

int main()
{
    int width, height, flights, counter, queries;
    cin >> width;
    cin >> height;
	char* buffer = new char[MAX_STRING];
	counter = 0;
    char** map;
	map = new char* [height];
	for (int i = 0; i < height; i++) {
		map[i] = new char [width];
	}

	bool** visited;
	visited = new bool* [height];
	for (int i = 0; i < height; i++) {
		visited[i] = new bool[width];
	}

	clearVisited(visited, height, width);
	
	City* firstCity;
	City* lastCity;
	City* city = new City();
	strcpy(city->name, "first");
	city->next = nullptr;
	city->prev = nullptr;
	firstCity = city;
	lastCity = city;

	readTo2DArray(width,height, map);
	findCities(width, height, map, buffer, firstCity, city, visited, &counter);
	cin >> flights;
	char* first = new char[MAX_STRING];
	char* second = new char[MAX_STRING];
	int number;
	for (int i = 0; i < flights; i++) {
		cin >> first;
		cin >> second;
		cin >> number;
		City* temp1 = findCity(firstCity, first);
		City* temp2 = findCity(firstCity, second);
		if (!isDuplicate(temp1->firstNeighbour, temp2->name, number)) addNeighbour(temp1->firstNeighbour, temp1->lastNeighbour, number, second, temp2->index);
	}
	cin >> queries;
	for (int i = 0; i < queries; i++) {
		cin >> first;
		cin >> second;
		cin >> number;
		findShortestRoad(counter, first, second, firstCity, number);
	}
	for (int i = 0; i < height; i++) {
		delete map[i];
	}
	delete[] map;

	for (int i = 0; i < height; i++) {
		delete visited[i];
	}
	delete[] visited;
	delete[] first;
	delete[] second;
}
