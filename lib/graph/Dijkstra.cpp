#include "Dijkstra.h"
#include <string>
#include <sstream>
#include <assert.h>

using namespace std;

digraph::digraph() {
	this->first_vertex = nullptr;
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
	this->first_vertex = v;

	return v;
}

void digraph::add_arrow_end(struct vertex* v, int vertex_id, int weight) {
	struct arrow_end* a = new struct arrow_end;
	a->adj_vertex_id = vertex_id;
	a->weight = weight;
	a->h_link = v->h_link;
	v->h_link = a;
}

void digraph::dijkstra(int vertex_id) {

}

void digraph::print_digraph() {
	struct vertex* it = this->first_vertex;
	
	while (it) {
		cout << it->vertex_id << ": ";
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
