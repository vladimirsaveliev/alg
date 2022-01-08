#include <iostream>
#include <fstream>
#include "../lib/graph/Dijkstra.h"
#include "../lib/graph/graph.h"

using namespace std;

extern "C" {
	int testgraph() {
		graph g1;
		while (1) {
			char c;

			printf("   \x1b[37;1m1 - read graph from file\x1b[0m\n");
			printf("   2 - dfs algorithm\n");
			printf("   3 - read weighted graph\n");
			printf("   0 - return to main menu\n");

			scanf(" %c", &c);
			switch (c) {
			case '1':
			{
				ifstream infile;
				string f;
				cout << "Enter file name\n";
				cin >> f;
				infile.open(f);
				if (!infile.is_open()) {
					cout << "File not open\n";
					break;
				}
				g1.read_graph(infile);
				g1.print_graph();
				infile.close();
				break;
			}
			case '2':
			{
				int v;
				cout << "Input start vertex:\n";
				cin >> v;
				cout << "Spanning tree:\n";
				g1.dfs_spanning_tree(v);
				cout << "Connected component:\n";
				g1.dfs_graph(v);
				break;
			}
			case '3':
			{
				ifstream infile;
				string f;
				cout << "Enter file name\n";
				cin >> f;
				infile.open(f);
				if (!infile.is_open()) {
					cout << "File not open\n";
					break;
				}
				g1.read_wgraph(infile);
				g1.print_graph();
				infile.close();
				break;
			}
			case '0': 
				return 0;
			}
		}
	}
			
	int testdigraph() {
		digraph g1;
		while (1) {
			char c;

			printf("   \x1b[37;1m1 - read graph from file\x1b[0m\n");
			printf("   2  - dijkstra algorithm\n");
			printf("   3 - minimal cover\n");
			printf("   0 - return to main menu\n");

			scanf(" %c", &c);
			switch (c) {
			case '1':
			{
				ifstream infile;
				string f;
				cout << "Enter file name\n";
				cin >> f;
				infile.open(f);
				if (!infile.is_open()) {
					cout << "File not open\n";
					break;
				}
				g1.read_digraph(infile);
				g1.print_digraph();
				infile.close();
			}
			break;
			
			case '2':
				int start;
				cout << "Input starting vertex\n";
				cin >> start;
				g1.dijkstra(start);
				g1.print_digraph();	
				break;
			
			case '3':
				g1.tree_minimal_cover();
				break;

			case '0':
				return 0;
			}
		}
	}
}