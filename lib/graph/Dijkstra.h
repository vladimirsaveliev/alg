#include <iostream>

using namespace std;

struct arrow_end {
	int adj_vertex_id;
	int weight;
	struct arrow_end* h_link;
	struct vertex* vertex;
};

struct vertex {
	int vertex_id;
	struct arrow_end* h_link;
	struct vertex* v_link;
};

class digraph {
private:
	struct vertex* first_vertex;
	
	struct vertex* find_vertex(int vertex_id);

	struct vertex* add_vertex(int vertex);

	void add_arrow_end(struct vertex* v, int vertex_id, int weight);

	void free_graph();

public:
	digraph();
		
	~digraph();

	void read_digraph(istream &stream);

	void dijkstra(int vertex_id);

	void print_digraph();
};