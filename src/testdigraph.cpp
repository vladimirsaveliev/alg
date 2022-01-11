#include <iostream>
#include <fstream>
#include <iomanip>
#include "../lib/graph/Dijkstra.h"
#include "../lib/graph/graph.h"

using namespace std;

extern "C" {
	int testgraph() {
		graph g1;
		graph g2;
		while (1) {
			char c;

			printf("   \x1b[37;1m1 - read graph from file\x1b[0m\n");
			printf("   2 - dfs algorithm\n");
			printf("   3 - read weighted graph\n");
			printf("   4 - Jarnik algorithm(find min spannning tree)\n");
			printf("   5 - Kruskal algorithm(find min spannning tree)\n");
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
			case '4':
				if (!g1.is_weighted()) {
					cout << "Jarnik algorithm works only with weighted graph\n";
					break;
				}
				g1.jarnik(g2);
				g2.print_graph();
				break;
			case '5':
				if (!g1.is_weighted()) {
					cout << "Kruskal algorithm works only with weighted graph\n";
					break;
				}
				g1.krusksal(g2);
				g2.print_graph();
				break;
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
/*
	Consider an empty hash table of size 17 (slots with indices 0,…,16). 
	Insert one by one the elements 19,69,53,52,27,18 (in this order) 
	using OpenInsert from the lecture, double hashing strategy with 
	thombstones, and the hash function h(k,i)=(6⋅k+i⋅(4⋅kmod7+1))mod17.
	Then delete items 27,69 using OpenDelete from the lecture.
	Finally, insert elements 29,37,18 using OpenInsert.
	Write down the final hash table content from box 0 to 16 
	as a sequence of numbers separated by commas. 
	Write "-" if the slot is empty and "t" if the slot contains a 
	thombstone.	
*/
#define TOMBSTONE INT_MAX 
#define EMPTY INT_MIN

	int hash_size;
	int coef_k; 
	int coef_2k;
	int mod_int; 
	int mod_ext; 
	int plus_one;

	int h(int key, int i) 
	{
		return (coef_k * key + i * (coef_2k * key % mod_int + plus_one)) % mod_ext;
	}

	bool insert_to_ht(int k, int* arr, int hasht_size) {
		for (int i = 0; i < hasht_size; i++) {
			int ind = h(k, i);
			if (arr[ind] == EMPTY || arr[ind] == TOMBSTONE) {				
				arr[ind] = k;
				return true;
			}
		}

		cout << "Insert failed\n";
		return false;
	}

	bool delete_from_ht(int k, int* arr, int hasht_size) {
		for (int i = 0; i < hasht_size; i++) {
			int ind = h(k, i);
			if (arr[ind] == k) {
				arr[ind] = TOMBSTONE;
				return true;
			}
			if (arr[ind] == EMPTY) {
				break;
			}
		}

		cout << "Delete failed\n";
		return false;
	}


	void hash_function() {	
		int k;
		
		cout << "h(k, i) = (6 * k + i * (4 * k mod7 + 1)) mod 17\n";
		cout << "Example: 17 6 4 7 17 1\n";
		cin >> hash_size;
		cin >> coef_k;
		cin >> coef_2k;
		cin >> mod_int;
		cin >> mod_ext;
		cin >> plus_one;

		int* arr = new int[hash_size];
		for (int i = 0; i < hash_size; i++) {
			arr[i] = EMPTY;
		}

		cout << "Enter numbers to insert:\n";
		while (cin >> k) {
			if (k >= 0) {
				insert_to_ht(k, arr, hash_size);
			}
			if (k < 0) {
				delete_from_ht(-k, arr, hash_size);
			}
			for (int i = 0; i < hash_size; i++) {
				if (arr[i] == TOMBSTONE) {
					cout << setw(5) << "T";
				}
				else if (arr[i] == EMPTY) {
					cout << setw(5) << "-";
				}
				else {
					cout << setw(5) << arr[i];
				}
			}
			cout << "\n";
		}
		string c;
		cin >> c;
	}
}