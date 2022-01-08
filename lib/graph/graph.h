#pragma once
#include <iostream>

using namespace std;

enum dfs_mode {
	dfs_st_mode,
	dfs_cn_mode
};

enum graph_state_t {
	gs_unmarked,
	gs_opened,
	gs_closed
};

struct edge_info
{
	bool connected;
	bool in_graph;
	int weight;
	graph_state_t state;
};

class graph
{
private:
	struct edge_info** table;
	int n_vertex;
	bool weighted;

	void allocate_table();
	void deallocate_table();
	void dfs(int v, dfs_mode mode);
	void print_closed_vertices();
	void dfs_rec(int v, dfs_mode mode);
	bool spanning_tree_edge(graph& mst);

public:
	graph();
	~graph();
	void print_graph();
	void read_graph(istream &stream);
	void read_wgraph(istream &stream);
	void dfs_graph(int v);
	void dfs_spanning_tree(int v);
	bool is_weighted();
	void jarnik(graph& mst);
};

