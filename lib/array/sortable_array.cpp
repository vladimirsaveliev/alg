#include <iostream>
#include <assert.h>
#include <math.h>
#include "sortable_array.h"
#include <iomanip>

using namespace std;

struct arrayx {
	int* arr;
	int size;
};

void sorted_array::read_array() {
	cout << "Input " << this->size << " elements into array:\n";
	for (int i = 0; i < this->size; i++) {
		cin >> this->arr[i];
	}
}

 int range_rand(int min, int max) {
	int rc = 0;
	assert(min <= max);
	rc = (rand() % (max - min + 1)) + min;
	assert(rc >= min && rc <= max);

	return rc;
}

struct arrayx _quick_sort(struct arrayx *x) {
	if (x->size <= 1) {
		return *x;
	}
	int pivot = x->arr[x->size / 2];
	struct arrayx l;
	l.size = 0;
	l.arr = new int[x->size];
	struct arrayx m;
	m.size = 0;
	m.arr = new int[x->size];
	struct arrayx r;
	r.size = 0;
	r.arr = new int[x->size];
	for (int i = 0; i < x->size; i++) {
		if (x->arr[i] < pivot) {
			l.arr[l.size++] = x->arr[i];
			continue;
		}
		if (x->arr[i] > pivot) {
			r.arr[r.size++] = x->arr[i];
			continue;
		}
		m.arr[m.size++] = x->arr[i];
	}
	l = _quick_sort(&l);
	r = _quick_sort(&r);
	int ind = 0;
	for (int i = 0; i < l.size; i++) {
		x->arr[ind++] = l.arr[i];
	}
	for (int i = 0; i < m.size; i++) {
		x->arr[ind++] = m.arr[i];
	}
	for (int i = 0; i < r.size; i++) {
		x->arr[ind++] = r.arr[i];
	}

	delete[] l.arr;
	delete[] m.arr;
	delete[] r.arr;

	return *x;
}
sorted_array::sorted_array(int sizex)
{
	this->size = sizex;
	this->arr = new int[sizex];
}

sorted_array::sorted_array(int arrx[], int sizex) {
	this->size = sizex;
	this->arr = new int[sizex];
	for (int i = 0; i < sizex; i++) {
		this->arr[i] = arrx[i];
	}
}

sorted_array::~sorted_array() {
	delete[] this->arr;
}

	// Properties:
	//	time complexity O(x^2)
	//	stable, in-place, data sensitive
void sorted_array::bubble_sort() {
	int end = this->size - 1;
	int changed = 1;
	while (changed == 1) {
		changed = 0;
		for (int i = 0; i < end; i++) {
			if (arr[i] > arr[i + 1]) {
				int tmp = arr[i + 1];
				arr[i + 1] = arr[i];
				arr[i] = tmp;
				changed = 1;
			}
		}
		end--;
	}
}

// Properties:
//	time complexity O(n^2)
//	in-place, not data sensitive, not stable
void sorted_array::select_sort() {
	for (int i = 0; i < this->size; i++) {
		int ind = i;
		for (int j = i + 1; j < this->size; j++) {
			if (arr[j] < arr[ind]) {
				ind = j;
			}
		}
		int tmp = arr[i];
		arr[i] = arr[ind];
		arr[ind] = tmp;
	}
}

// Properties:
//	time complexity O(n^2)
//	in-place, data sensitive, stable
void sorted_array::insert_sort() {
	for (int i = 1; i < this->size; i++) {
		int key = arr[i];
		int j = i - 1;
		while ((j >= 0) && (arr[j] > key)) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

void sorted_array::merge_sort() {

}

// Design an algorithm which finds out the number 
// of inverses in the input sequence.
// Ex 2. Tutorial 5
int sorted_array::num_of_inverses() {
	int count = 0;
	for (int i = 1; i <= this->size; i++) {
		for (int j = i + 1; j <= this->size; j++) {
			if (arr[i] > arr[j]) {
				count++;
			}
		}
	}
	
	return count;
}

// Array elements are {0 <= this->arr[i] <= this->size^3 - 1}
void sorted_array::radix_sort() {
	int *count = new int[this->size];
	int* output = new int[this->size];
	for (int k = 0; k < 3; k++) {
		int div = pow(this->size, k);
		for (int i = 0; i < this->size; i++) {
			count[i] = 0;
		}
		for (int i = 0; i < this->size; i++) {
			int rem = ((this->arr[i] / div) % this->size);
			count[rem]++;
		}
		for (int i = 1; i < this->size; i++) {
			count[i] += count[i - 1];
		}
		// Build output array
		for (int i = this->size - 1; i >= 0; i--) {
			int rem = ((this->arr[i] / div) % this->size);
			int pos = count[rem] - 1;
			output[pos] = this->arr[i];
			count[rem]--;
		}
			// Copy output array to P
		for (int i = 0; i < this->size; i++) {
			this->arr[i] = output[i];
		}
		this->print_array();
	}
}

void sorted_array::randomizer(int min, int max) {
	for (int i = 0; i < this->size; i++) {
		this->arr[i] = range_rand(min, max);
	}
}

void sorted_array::quick_sort() {
	struct arrayx x;
	x.arr = this->arr;
	x.size = this->size;
	_quick_sort(&x);
}

int length_lis_rec(int j, int size, int* arr) {
	int d = 1;
	for (int i = j + 1; i < size; i++) {
		if (arr[i] > arr[j]) {
			int lis_j = 1 + length_lis_rec(i, size, arr);
			if (d < lis_j) {
				d = lis_j;
			}
		}
	}

	return d;
}

// Longest increasing sequence (Recursive version)
void sorted_array::lis_rec() {
	int* tmp = new int[this->size + 1];
	tmp[0] = INT_MIN;
	for (int i = 0; i < this->size; i++) {
		tmp[i + 1] = this->arr[i];
	}
	cout << "LIS rec equals: " << length_lis_rec(0, this->size, tmp) - 1 
		 << "\n";

	delete[] tmp;
}

//Longest Increasing Sequence (Iterative version)
void sorted_array::lis_iter() {
	int* tmp = new int[this->size + 1];
	tmp[0] = INT_MIN;
	for (int i = 0; i < this->size; i++) {
		tmp[i + 1] = this->arr[i];
	}
	int* T = new int[this->size + 1];
	int* P = new int[this->size + 1];
	for (int i = this->size; i >= 0; i--) {
		T[i] = 1;
		P[i] = 0;
		for (int j = i + 1; j <= this->size; j++) {
			if (tmp[i] < tmp[j] && T[i] < 1 + T[j]) {
				T[i] = 1 + T[j];
				P[i] = j;
			}
		}
	}
	cout << "LIS iter equals " << T[0] - 1 << "\n";
	int ind = 0;
	while (P[ind] != 0) {
		cout << setw(3) << tmp[P[ind]];
		ind = P[ind];
	}
	cout << "\n";

	delete[] tmp;
	delete[] T;
}

/*
	CuttingBoardPrice(i)
		if prices[i] is set
			return prices[i]
		prices[i] = K
		for j: 0..D-1
			prices[i] -= P[i+j]
		
		return prices[i]
*/

int cutting_board_price(int i, int D, int K, int* plank, int N) {
	int board_price;
	board_price = K;
	if (N - i < D) {
		return INT_MIN;
	}
	for (int j = 0; j < D; j++) {
		board_price -= plank[i + j];
	}
	
	return board_price;
}

/*
	return maximal total price of all cutting boards starting with i’th

	CarpenterAlg(i)
		length =  CuttingBoardPrice(i)
		total[i] = length
		for j: i..N - D + 1
			if total[i] < length + CarpenterAlg(j + D)
			total[i] = length + CarpenterAlg(j + D)
		return total[i]
*/

void print_board(int board_price, int D, int i, int *plank, int N) {
	cout << "board:" << board_price << ", starts from " << i << ", defect costs: ";
	int end = i + D;
	if (end > N) {
		end = N;
	}
	for (int j = i; j < end; j++) {
		cout << plank[j] << ", ";
	}
	cout << "\n";
}


int carpenter_rec(int i, int D, int K, int* plank, int N, int* solution) {
	int total = 0;
	int prev = -1;
	int end = i + D;
	if (end > N) {
		end = N;
	}
	for (int j = i; j < end; j++) {
		int board_price = cutting_board_price(j, D, K, plank, N);
		print_board(board_price, D, j, plank, N);
		int rest_price = carpenter_rec(j + D, D, K, plank, N, solution);
		if (total < board_price + rest_price) {
			total = board_price + rest_price;
			cout << "Included index " << j << "\n";
			if (prev != -1) {
				solution[prev] = 0;
				cout << "Excluded index " << prev << "\n";
			}
			solution[j] = 1;
			prev = j;
		}
	}

	return total;
}


void sorted_array::carpenter_task(int D, int K) {
	int* solution = new int[this->size - D + 1]; // Element of this array is 1 if cutting board is in optimal selection
	for (int i = 0; i < this->size - D + 1; i++) {
		solution[i] = 0;
	}
	cout << "Total max price is: " << carpenter_rec(0, D, K, this->arr, this->size, solution) << "\n";
	for (int i = 0; i < this->size - D + 1; i++) {
		if (solution[i] != 0) {
			print_board(cutting_board_price(i, D, K, this->arr, this->size), D, i, this->arr, this->size);
		}
	}
	cout << "\n";
}

struct edit_distance_info {
	int changes;
	int deletes;
	int inserts;
} distance_info;

// Edit distance (Recursive algorithm)
// number of characters changed
int edit_distance_rec(string &s1, string &s2, int i, int j, 
					  int *tail_inserts, int *tail_deletes) {
	if (i == 1 && j == 1) {
		distance_info.changes = 0;
		distance_info.deletes = 0;
		distance_info.inserts = 0;
	}
	int arr[6] = { 0, 0, 0, 0, 0, 0 };
	if (i > s1.length()) {
		*tail_inserts = s2.length() - j + 1;
		return s2.length() - j + 1;
	}
	if (j > s2.length()) {
		*tail_deletes = s1.length() - i + 1;
		return s1.length() - i + 1;
	}
	int l_change = edit_distance_rec(s1, s2, i + 1, j + 1, &arr[0], &arr[1]);
	if (s1[i - 1] != s2[j - 1]) {
		l_change++;
	}
	int l_delete = 1 + edit_distance_rec(s1, s2, i + 1, j, &arr[2], &arr[3]);
	int l_insert = 1 + edit_distance_rec(s1, s2, i, j + 1, &arr[4], &arr[5]);

	if (l_change <= l_delete && l_change <= l_insert) {
		if (s1[i - 1] != s2[j - 1]) {
			distance_info.changes++;
		}
		distance_info.inserts += arr[0];
		distance_info.deletes += arr[1];
		if (i == 1 && j == 1) {
			cout << "Edit distance: " << l_change <<
				", inserts: " << distance_info.inserts <<
				", deletes: " << distance_info.deletes <<
				", changes: " << distance_info.changes <<
				"\n";
		}
		return l_change;
	}
	if (l_delete <= l_change && l_delete <= l_insert) {
		distance_info.deletes++;
		distance_info.inserts += arr[2];
		distance_info.deletes += arr[3];
		if (i == 1 && j == 1) {
			cout << "Edit distance: " << l_delete <<
				", inserts: " << distance_info.inserts <<
				", deletes: " << distance_info.deletes <<
				", changes: " << distance_info.changes <<
				"\n";
		}
		return l_delete;
	}
	distance_info.inserts++;
	distance_info.inserts += arr[4];
	distance_info.deletes += arr[5];
	if (i == 1 && j == 1) {
		cout << "Edit distance: " << l_insert <<
			", inserts: " << distance_info.inserts <<
			", deletes: " << distance_info.deletes <<
			", changes: " << distance_info.changes <<
			"\n";
	}

	return l_insert;
}

void sorted_array::print_array() {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << "\n";
}

/*
int main() {
	sorted_array new_arr = sorted_array(10);
	new_arr.randomizer(0, pow(10, 3) - 1);
	new_arr.print_array();
	new_arr.quick_sort();
	new_arr.print_array();

	return 0;
}
*/
