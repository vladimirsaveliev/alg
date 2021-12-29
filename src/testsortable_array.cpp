#include <iostream>
#include "../lib/array/sortable_array.h"

using namespace std;

extern "C" {
	int testsortable_array(void) {
		while (1) {
			char c;
			int key;
			sorted_array arr(100);
			arr.randomizer(-1024, 1024);
			

			cout << "   \x1b[37;1m1 - create array with random numbers\x1b[0m\n";
			cout << "   2 - sort with radix sort algorithm\n";
			cout << "   3 - sort with quick sort algorithm\n";
			cout << "   0 - exit\n";

			cin >> c;

			switch (c) {
			case '1':
				cout << "Not ready\n";
				break;
			case '2':
				cout << "Not ready\n";
				break;
			case '3':
				arr.quick_sort();
				arr.print_array();
				break;
			case '0':
				return 0;
			}
		}

		return 0;
	}
}
