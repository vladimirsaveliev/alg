#include <iostream>

using namespace std;

int testsortable_array(void) {
	while (1) {
		char c;
		int key;

		cout << "   \x1b[37;1m1 - create array with random numbers\x1b[0m\n";
		cout << "   2 - sort with radix sort algorithm\n";
		cout << "   0 - exit\n";

		cin >> c;

		switch (c) {
		case '1':
			cout << "Not ready\n";
			break;
		case '2':
			cout << "Not ready\n";
			break;
		case '0':
			return 0;
		}
	}

	return 0;
}
