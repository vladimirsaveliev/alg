class sorted_array
{
private:
	int* arr;
	int size;

public:
	sorted_array(int sizex);
	sorted_array(int arrx[], int sizex);
	~sorted_array();
	void bubble_sort();
	void select_sort();
	void insert_sort();
	void merge_sort();
	int num_of_inverses();
	void radix_sort();
	void randomizer(int min, int max);
	void quick_sort();
	void print_array();
};
