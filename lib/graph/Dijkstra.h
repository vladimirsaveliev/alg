#include <iostream>

using namespace std;

struct arrow_end {
	int adj_vertex_id;
	int weight;
	struct arrow_end* h_link;
	struct vertex* vertex;
};

enum digraph_state_t
{
	ds_unmarked,
	ds_opened,
	ds_closed
};

struct vertex {
	int vertex_id;
	struct arrow_end* h_link;
	struct vertex* v_link;
	int h; // shortest path length to initial vertex
	struct vertex* P; // predecessor on the shortest path 
	digraph_state_t state;
	bool incover;
};

class digraph {
private:
	struct vertex* first_vertex;
	int nr_open_vertices;
	
	struct vertex* find_vertex(int vertex_id);

	struct vertex* add_vertex(int vertex);

	struct vertex* select_vertex();

	void add_arrow_end(struct vertex* v, int vertex_id, int weight);

	void free_graph();

public:
	digraph();
		
	~digraph();

	void read_digraph(istream &stream);

	void dijkstra(int vertex_id);

	void print_digraph();

	void tree_minimal_cover();
};