#include <iomanip>
#include <iostream>
#include "graph.h"

using namespace std;


graph::graph() {
	this->table = nullptr;
	this->n_vertex = 0;
}

graph::~graph() {
	this->deallocate_table();
}

void print_weighted_edge(int i, int j, int weight) {
	cout << "(" << i << ", " << j << ", (" << weight << "))\n";
}

void print_edge(int i, int j) {
	cout << "(" << i << ", " << j << ")\n";
}

void graph::print_graph() {
	for (int i = 0; i < this->n_vertex; i++) {
		for (int j = i; j < this->n_vertex; j++) {
			if (this->table[i][j].connected == true) {
				if (this->weighted) {
					print_weighted_edge(i, j, this->table[i][j].weight);
				}
				else {
					print_edge(i, j);
				}
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
//		0 1 5
//	2 is number of vertices
//  0 1 - incident vertices of the edge in graph
//  5 is weight of this edge
void graph::read_wgraph(istream &stream) {
	int id1;
	int id2;
	int id3;

	this->deallocate_table();
	stream >> this->n_vertex;
	this->allocate_table();

	while (stream >> id1 >> id2 >> id3) {
		this->table[id1][id2].connected = true;
		this->table[id2][id1].connected = true;
		this->table[id1][id2].weight = id3;
		this->table[id2][id1].weight = id3;
	}

	this->weighted = true;
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

	this->weighted = false;
}

bool graph::is_weighted() {
	return this->weighted;
}

void graph::dfs_spanning_tree(int v) {
	this->dfs(v, dfs_st_mode);
}

void graph::dfs_graph(int v) {
	this->dfs(v, dfs_cn_mode);
}

// Lecture 2. Finding of a Connected Component of a Graph
// if mode = ST
//		print ST
void graph::dfs(int v, dfs_mode mode) {
	if (v >= this->n_vertex) {
		cout << "Invalid vertex\n";
		return;
	}
	for (int i = 0; i < this->n_vertex; i++) {
		this->table[i][i].state = gs_unmarked;
	}
	this->dfs_rec(v, mode);
	if (mode == dfs_cn_mode) {
		this->print_closed_vertices();
	}
}

void graph::print_closed_vertices() {
	for (int i = 0; i < this->n_vertex; i++) {
		if (this->table[i][i].state == gs_closed) {
			cout << setw(5) << i;
		}
	}
	cout << "\n";
}

void graph::dfs_rec(int v, dfs_mode mode) {
	if (this->table[v][v].state != gs_unmarked) {
		return;
	}
	this->table[v][v].state = gs_opened;
	for (int i = 0; i < this->n_vertex; i++) {
		if (this->table[v][i].connected == true) {
			if (mode == dfs_cn_mode) {
				this->dfs_rec(i, mode);
			}
			else {
				if (this->table[i][i].state == gs_unmarked) {
					print_edge(v, i);
					this->dfs_rec(i, mode);
				}
			}
		}
	}
	this->table[v][v].state = gs_closed;
}


