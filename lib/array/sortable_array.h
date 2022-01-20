using namespace std;

class sorted_array
{
private:
	int* arr;
	int size;

public:
	sorted_array(int sizex);
	sorted_array(int arrx[], int sizex);
	~sorted_array();
	void read_array();
	void bubble_sort();
	void select_sort();
	void insert_sort();
	void merge_sort();
	int num_of_inverses();
	void radix_sort();
	void randomizer(int min, int max);
	void quick_sort();
	void lis_rec();
	void lis_iter();
	void carpenter_task(int D, int K);
	void print_array();
};

int edit_distance_rec(string &s1, string &s2, int i, int j, int *tail_insert, int *tail_delete);
