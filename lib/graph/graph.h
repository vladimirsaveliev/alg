#pragma once
#include <iostream>

using namespace std;

struct edge_info
{
	bool connected;
};

class graph
{
private:
	struct edge_info** table;
	int n_vertex;

	void allocate_table();
	void deallocate_table();

public:
	graph();
	~graph();
	void print_graph();
	void read_graph(istream &stream);
};

