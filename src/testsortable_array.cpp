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
			cout << "   4 - lis algorithm\n";
			cout << "   5 - edit distance\n";
			cout << "	6 - carpenter task\n";
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
			case '4':
			{
				cout << "Input array size:\n";
				int ar_size;
				cin >> ar_size;
				sorted_array lis_arr(ar_size);
				lis_arr.read_array();
				lis_arr.lis_rec();
				lis_arr.lis_iter();
				break;
			}
			case '5':
			{
				cout << "Input two strings:\n";
				string s1, s2;
				int a = 0;
				int b = 0;
				cin >> s1;
				cin >> s2;
				edit_distance_rec(s1, s2, 1, 1, &a, &b);
				break;
			}
			case '6':
			{
				cout << "Input array size:\n";
				int ar_size;
				cin >> ar_size;
				sorted_array plank(ar_size);
				plank.read_array();
				plank.carpenter_task(4, 10);
				break;
			}
			case '0':
				return 0;
			}
		}

		return 0;
	}
}
