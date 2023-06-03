#include "Functions.h"

void findNeighbours(int y, int x, int width, int height, char** map, bool** visited, City* firstCity, City* Scity) {
	Vector<coords> queue;

	queue.PushBack({ y, x, 0 });
	visited[y][x] = true;

	while (!queue.Empty()) {
		int i = queue.GetFirst().i;
		int k = queue.GetFirst().k;
		int length = queue.GetFirst().length;
		queue.PopFirst();

		if (map[i][k] == '*' && (i != y || k != x)) {
			City* temp = findCity(firstCity, i, k);
			addNeighbour(Scity->firstNeighbour, Scity->lastNeighbour, length, temp->name, temp->index);
		}
		else {
			if (i > 0 && (map[i - 1][k] == '#' || map[i - 1][k] == '*') && !visited[i - 1][k]) {
				queue.PushBack({ i - 1, k, length + 1 });
				visited[i - 1][k] = true;
			}
			if (i < height - 1 && (map[i + 1][k] == '#' || map[i + 1][k] == '*') && !visited[i + 1][k]) {
				queue.PushBack({ i + 1, k, length + 1 });
				visited[i + 1][k] = true;
			}
			if (k > 0 && (map[i][k - 1] == '#' || map[i][k - 1] == '*') && !visited[i][k - 1]) {
				queue.PushBack({ i, k - 1, length + 1 });
				visited[i][k - 1] = true;
			}
			if (k < width - 1 && (map[i][k + 1] == '#' || map[i][k + 1] == '*') && !visited[i][k + 1]) {
				queue.PushBack({ i, k + 1, length + 1 });
				visited[i][k + 1] = true;
			}
		}
	}
}

void clearVisited(bool** visited, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			visited[i][j] = false;
		}
	}
}

void readTo2DArray(int width, int height, char** map) {
	int i = 0, k = 0;
	char x;
	while (i < height) {
		while (k < width) {
			x = (char)getchar();
			if (x == '\n' || x == '\t' || x == ' ') continue;
			else {
				map[i][k] = x;
				k++;
			}
		}
		k = 0;
		i++;
	}
}

bool findLetter(int y, int x, int i, int k, int width, int height, char** map, char buffer[], City* firstCity, City* city, int* counter) {
	int copyK = k;
	if (i + y >= 0 && k + x >= 0 && i + y < height && k + x < width) {
		if (map[i + y][k + x] != '.' && map[i + y][k + x] != '#' && map[i + y][k + x] != '*') {
			while (k >= 0) {
				k--;
				if (i < 0 || k < 0 || map[i + y][k + x] == '.' || map[i + y][k + x] == '#' || map[i + y][k + x] == '*') {
					int z = 0;
					for (int o = x + k + 1; o < width; o++) {
						if (map[i + y][o] == '.' || map[i + y][o] == '#' || map[i + y][o] == '*') break;
						buffer[z] = map[i + y][o];
						z++;
					}
					buffer[z] = '\0';
					addCity(firstCity, city, buffer, i, copyK, *counter);
					*counter = *counter + 1;
					return true;
				}
			}
		}
	}
	return false;
}

void getCityName(int i, int k, int width, int height, char** map, char buffer[], City* firstCity, City* city, int* counter) {
	if (findLetter(-1, -1, i, k, width, height, map, buffer, firstCity, city, counter)) return;
	if (findLetter(-1, 0, i, k, width, height, map, buffer, firstCity, city, counter)) return;
	if (findLetter(-1, 1, i, k, width, height, map, buffer, firstCity, city, counter)) return;
	if (findLetter(0, 1, i, k, width, height, map, buffer, firstCity, city, counter)) return;
	if (findLetter(0, -1, i, k, width, height, map, buffer, firstCity, city, counter)) return;
	if (findLetter(1, 0, i, k, width, height, map, buffer, firstCity, city, counter)) return;
	if (findLetter(1, -1, i, k, width, height, map, buffer, firstCity, city, counter)) return;
	if (findLetter(1, 1, i, k, width, height, map, buffer, firstCity, city, counter)) return;
}

void findCities(int width, int height, char** map, char buffer[], City* firstCity, City* city, bool** visited, int* counter) {
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (map[i][k] == '*') {
				getCityName(i, k, width, height, map, buffer, firstCity, city, counter);
			}
		}
	}
	for (int i = 0; i < height; i++) {
		for (int k = 0; k < width; k++) {
			if (map[i][k] == '*' && !visited[i][k]) {
				visited[i][k] = true;
				City* Scity = findCity(firstCity, i, k);
				Scity->neighbour = new List();
				strcpy(Scity->neighbour->name, "first");
				Scity->neighbour->next = nullptr;
				Scity->neighbour->previous = nullptr;
				Scity->firstNeighbour = Scity->neighbour;
				Scity->lastNeighbour = Scity->neighbour;
				findNeighbours(i, k, width, height, map, visited, firstCity, Scity);
				clearVisited(visited, height, width);
			}
		}
	}
}

int minDistance(int distances[], bool visited[], int counter) {
	int min = INT_MAX;
	int minIndex = -1;
	for (int i = 0; i < counter; i++) {
		if (!visited[i] && distances[i] <= min) {
			min = distances[i];
			minIndex = i;
		}
	}
	return minIndex;
}

void printPath(City* startCity, City* endCity, City** path, int counter) {
	char** list = new char* [counter];
	for (int i = 0; i < counter; i++) {
		list[i] = new char[MAX_STRING];
		strcpy(list[i], "");
	}
	int i = counter - 1;
	if (startCity == endCity) {
		for (int i = 0; i < counter; i++) {
			delete[] list[i];
		}
		delete[] list;
		return;
	}
	City* currentCity = path[endCity->index];
	while (currentCity != startCity) {
		strcpy(list[i], currentCity->name);
		currentCity = path[currentCity->index];
		i--;
	}
	for (int j = 0; j < counter; j++) {
		if (list[j] != nullptr) {
			if (strcmp(list[j], startCity->name) != 0 && strcmp(list[j], endCity->name) != 0) {
				cout << " " << list[j];
			}
		}
	}
	for (int i = 0; i < counter; i++) {
		delete[] list[i];
	}
	delete[] list;
}

void findShortestRoad(int counter, char source[], char destination[], City* firstCity, int option) {
	City* path[MAX_NODE];
	for (int i = 0; i < MAX_NODE; i++) {
		path[i] = nullptr;
	}
	int distances[MAX_NODE];
	bool* visited = new bool[counter];
	for (int i = 0; i < counter; i++) {
		distances[i] = INT_MAX;
		visited[i] = false;
	}
	City* sourceCity = findCity(firstCity, source);
	int indexSource = sourceCity->index;
	distances[indexSource] = 0;
	for (int i = 0; i < counter - 1; i++) {
		int j = minDistance(distances, visited, counter);
		visited[j] = true;
		City* temp = findCity(firstCity, j);
		List* current = temp->firstNeighbour;
		while (current != nullptr) {
			int k = current->index;
			int length = current->length;
			if (!visited[k] && distances[j] != INT_MAX && distances[j] + length < distances[k]) {
				distances[k] = distances[j] + length;
				path[k] = temp;
			}
			current = current->next;
		}
	}
	City* destCity = findCity(firstCity, destination);
	int indexDest = destCity->index;
	cout << distances[indexDest];
	if (option == 1) printPath(sourceCity, destCity, path, counter);
	cout << endl;
	delete[] visited;
}