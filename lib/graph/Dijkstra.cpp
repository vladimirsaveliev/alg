#include "Dijkstra.h"
#include <string>
#include <sstream>
#include <assert.h>
#include <limits>

using namespace std;

digraph::digraph() {
	this->first_vertex = nullptr;
	this->nr_open_vertices = 0;
}

digraph::~digraph() {
	free_graph();
}

void digraph::read_digraph(istream &stream) {
	free_graph();
	string str;
	int id1;
	int id2;
	int weight;
	while (getline(stream, str)) {
		stringstream s(str);
		s >> id1;
		struct vertex* begin = find_vertex(id1);
		if (begin == nullptr) {
			begin = add_vertex(id1);
		}
		if (s >> id2) {
			struct vertex* end;
			end = find_vertex(id2);
			if (end == nullptr) {
				end = add_vertex(id2);
			}
			if (s >> weight) {
				// Add id2 adjucency list
				add_arrow_end(begin, id2, weight);
			}
			else {
				cout << "Format invalid\n";
				abort();
			}
		}
	}
}

// Return value:
//		nullptr if not found
//		pointer to vertex if found
struct vertex* digraph::find_vertex(int vertex_id) {
	struct vertex* v = this->first_vertex;
	struct vertex* next;
	while (v != nullptr) {
		if (v->vertex_id == vertex_id) {
			return v;
		}
		next = v->v_link;
		v = next;
	}

	return nullptr;
}

// This assumes vertex is not in graph
// Insert new vertex to head of list
struct vertex* digraph::add_vertex(int vertex) {
	assert(find_vertex(vertex) == nullptr);
	struct vertex* v = new struct vertex;
	v->vertex_id = vertex;
	v->h_link = nullptr;
	v->v_link = this->first_vertex;
	v->h = 0;
	v->P = v;
	this->first_vertex = v;

	return v;
}

void digraph::add_arrow_end(struct vertex* v, int vertex_id, int weight) {
	struct arrow_end* a = new struct arrow_end;
	a->adj_vertex_id = vertex_id;
	a->weight = weight;
	a->h_link = v->h_link;
	a->vertex = find_vertex(vertex_id);
	v->h_link = a;
}


// Lecture 12, p.15
void digraph::dijkstra(int vertex_id) {
	struct vertex* it = this->first_vertex;
	/*
	 * (1) For every vertex v:
	 * (2) state(v) := unmarked
	 * (3) h(v) := +∞, P(v) := undef	
	 */
	while (it) {
		it->h = INT_MAX;
		it->P = nullptr; // Undefined predecessor
		it->state = unmarked;
		it = it->v_link;
	}
	/*
	 * (4) state(v0) := open
	 * (5) h(v0) := 0
	 */
	struct vertex* v0 = find_vertex(vertex_id);
	if (v0 == nullptr) {
		cout << "Vertex not found\n";
		return;
	}
	v0->state = opened;
	this->nr_open_vertices++;
	v0->h = 0;
	// (6) While there is some open vertex do
	while (this->nr_open_vertices > 0) {
		// (7) Select an open vertex v with smallest h(v)
		struct vertex* v = select_vertex();
		if (v == nullptr) {
			break;
		}
		// (8) For every successor w of vertex v do
		struct arrow_end* w = v->h_link;
		while (w) {
			/*
			 * If h(w) > h(v) + l((v, w)) then
			 * (10) h(w) := h(v) + l((v, w))
			 * (11) state(w) := open
			 * (12) P(w) := v
			 */
			if (w->vertex->h > v->h + w->weight) {
				w->vertex->h = v->h + w->weight;
				if (w->vertex->state != opened) {
					this->nr_open_vertices++;
					w->vertex->state = opened;
				}
				w->vertex->P = v;
			}
			
			w = w->h_link;
		}
		v->state = closed;
		this->nr_open_vertices--;
	}
}

// Select open vertex with smallest path to initial vertex 
struct vertex* digraph::select_vertex() {
	struct vertex* it = this->first_vertex;
	struct vertex* op_vertex = nullptr;
	while (it) {
		if (it->state == opened) {
			if (op_vertex == nullptr) {
				op_vertex = it;
			}
			else {
				if (op_vertex->h > it->h) {
					op_vertex = it;
				}
			}
		}
		
		it = it->v_link;
	}

	return op_vertex;
}

void digraph::print_digraph() {
	struct vertex* it = this->first_vertex;
	
	while (it) {
		cout << it->vertex_id << ": h = " << it->h << "; pred = " << (it->P ? it->P->vertex_id : -1) << ";\n\t";
		struct arrow_end* it2 = it->h_link;
		while (it2) {
			cout << it2->adj_vertex_id << "(" << it2->weight << ") ";
			it2 = it2->h_link;
		}
		cout << "\n";	
		it = it->v_link;
	}
}

void digraph::free_graph() {
	struct vertex* it = this->first_vertex;

	while (it) {
		struct arrow_end* it2 = it->h_link;
		while (it2) {
			struct arrow_end* h = it2->h_link;
			delete it2;
			it2 = h;
		}
		struct vertex* t = it->v_link;
		delete it;
		it = t;
	}
	this->first_vertex = nullptr;
}
