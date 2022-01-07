#include "graph.h"
#include <iostream>

using namespace std;

graph::graph() {
	this->table = nullptr;
	this->n_vertex = 0;
}

graph::~graph() {
	this->deallocate_table();
}

void graph::print_graph() {
	for (int i = 0; i < this->n_vertex; i++) {
		for (int j = i; j < this->n_vertex; j++) {
			if (this->table[i][j].connected == true) {
				cout << "(" << i << ", " << j << ")\n";
			}
		}
	}
}

void graph::allocate_table() {
	this->table = new struct edge_info*[this->n_vertex];
	for (int i = 0; i < this->n_vertex; i++) {
		this->table[i] = new struct edge_info[this->n_vertex];
		for (int j = 0; j < this->n_vertex; j++) {
			this->table[i][j].connected = false;
		}
	}
}

void graph::deallocate_table() {
	for (int i = 0; i < this->n_vertex; i++) {
		delete[] this->table[i];
	}
	delete[] this->table;
}

// Input file:
//		2 
//		0 1
//	2 is number of vertex
//	0 1 - edge in graph

void graph::read_graph(istream &stream) {
	int id1;
	int id2;

	this->deallocate_table();
	stream >> this->n_vertex;
	this->allocate_table();
	
	while (stream >> id1 >> id2) {
		this->table[id1][id2].connected = true;
		this->table[id2][id1].connected = true;
	}
}
