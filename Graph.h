#pragma once
#include "Vector.h"

class List {
public:
	char* name;
	int length;
	int index;
	List* next;
	List* previous;
	List() {
		name = new char[100];
		next = nullptr;
		previous = nullptr;
		this->length = -1;
		index = -1;
	}
	List(int length, size_t sizeN, int index) {
		this->name = new char[sizeN];
		next = nullptr;
		previous = nullptr;
		this->length = length;
		this->index = index;
	}
	~List() {
		delete previous;
		delete next;
	}
};

class City {
public:
	int index;
	char* name;
	int height;
	int width;
	List* firstNeighbour;
	List* lastNeighbour;
	List* neighbour;

	City* next;
	City* prev;

	City() {
		name = new char[100];
		next = nullptr;
		prev = nullptr;
		firstNeighbour = nullptr;
		lastNeighbour = nullptr;
		neighbour = nullptr;
		height = -1;
		width = -1;
		index = -1;
	}
	City(size_t sizeN, int height, int width, int index) {
		name = new char[sizeN];
		next = nullptr;
		prev = nullptr;
		firstNeighbour = nullptr;
		lastNeighbour = nullptr;
		neighbour = nullptr;
		this->height = height;
		this->width = width;
		this->index = index;
	}
	~City() {
		delete[] name;
		delete next;
		delete prev;
		firstNeighbour->~List();
		lastNeighbour->~List();
		neighbour->~List();
	}
};

struct coords {
	int i;
	int k;
	int length;
};