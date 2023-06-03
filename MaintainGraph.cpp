#include "MaintainGraph.h"
bool isDuplicate(List* firstNeighbour, char name[], int length) {
	List* traverser = firstNeighbour;
	while (traverser != nullptr) {
		if (strcmp(traverser->name, name) == 0) {
			if (length < traverser->length) traverser->length = length;
			return true;
		}
		traverser = traverser->next;
	}
	return false;
}

City* GetLast(City* firstNode) {
	if (firstNode == nullptr) return nullptr;
	City* temp = firstNode;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	return temp;
}

List* GetLast(List* firstNode) {
	if (firstNode == nullptr) return nullptr;
	List* temp = firstNode;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	return temp;
}

City* findCity(City* firstCity, int height, int width) {
	City* traverser = firstCity;
	while (traverser != nullptr) {
		if (strcmp(traverser->name, "first") == 0) traverser = traverser->next;
		if (traverser->height == height && traverser->width == width) return traverser;
		traverser = traverser->next;
	}
	return nullptr;
}

City* findCity(City* firstCity, char name[]) {
	City* traverser = firstCity;
	while (traverser != nullptr) {
		if (strcmp(traverser->name, "first") == 0) traverser = traverser->next;
		if (strcmp(traverser->name, name) == 0) return traverser;
		traverser = traverser->next;
	}
	return nullptr;
}

City* findCity(City* firstCity, int index) {
	City* traverser = firstCity;
	while (traverser != nullptr) {
		if (strcmp(traverser->name, "first") == 0) traverser = traverser->next;
		if (traverser->index == index) return traverser;
		traverser = traverser->next;
	}
	return nullptr;
}

void addCity(City* firstCity, City* newCity, char name[], int height, int width, int index) {
	newCity = new City(strlen(name), height, width, index);
	strcpy(newCity->name, name);
	City* last = GetLast(firstCity);
	newCity->next = nullptr;
	newCity->prev = last;
	if (last == nullptr) return;
	last->next = newCity;
}

void addNeighbour(List* firstNeighbour, List* neighbour, int length, char name[], int index) {
	neighbour = new List(length, strlen(name), index);
	strcpy(neighbour->name, name);
	List* last = GetLast(firstNeighbour);
	neighbour->next = nullptr;
	neighbour->previous = last;
	if (last == nullptr) return;
	last->next = neighbour;
}