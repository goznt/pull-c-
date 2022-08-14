#include <iostream>
#include <time.h>
using namespace std;

class TSort{
private:
	template <typename T>
	void merge_split(T *data, size_t l, size_t m, size_t r){
		//Used to split a source array into two halfs and sort each set
		int n1 = (m - l + 1);
		int n2 = (r - m);

		size_t x = 0;
		size_t y = 0;
		size_t z = 0;

		T *L;
		T *R;
		//Create arrays
		L = new T[n1]; // Left
		R = new T[n2]; // Right
		//Copy data to left array
		while (x < n1){
			L[x] = data[l + x];
			x++;
		}
		//Copy data to right array
		while (y < n2){
			R[y] = data[m + 1 + y];
			y++;
		}
		//Reset variables for next loops
		x = 0;
		y = 0;
		//Set z to left
		z = l;

		while (x < n1 && y < n2){
			//Compare left array to right array
			if (L[x] <= R[y]){
				//Set data
				data[z] = L[x];
				x++;
			}
			else{
				//Set data
				data[z] = R[y];
				y++;
			}
			z++;
		}
		//Copy any remaining left array back to data array
		while (x < n1){
			//Set data array with left array data
			data[z] = L[x];
			x++;
			z++;
		}
		//Copy any remaining right array back to data array
		while (y < n2){
			//Set data array with right array data
			data[z] = R[y];
			y++;
			z++;
		}
		//Delete left and right arrays.
		delete[]L;
		delete[]R;
	}
public:
	//Merge sort algorithm
	template <typename T>
	void merge_sort(T *data, size_t l, size_t r){
		
		if (l >= r){
			return;
		}
		//Get middle of data array
		int mid = l + (r - l) / 2;
		//Merge left side
		merge_sort(data, l, mid);
		//Merge right side
		merge_sort(data, mid + 1, r);
		merge_split(data, l, mid, r);
	}

	//Bobble sort algorithm
	template <typename T>
	void bubble_sort(T *data, const size_t r){
		T temp;
		bool swapped;
		for (size_t x = 0; x < r; x++){
			swapped = false;
			for (size_t y = x + 1; y < r; y++){
				//Compare data x to data y
				if (data[x] >= data[y]){
					//Swap data
					temp = data[y];
					data[y] = data[x];
					data[x] = temp;
					//Tell us the data have been swaped.
					swapped = true;
				}
			}
			if (!swapped){
				break;
			}
		}
	}

	//Insertion Sort
	template <typename T>
	void insertion_sort(T*data, const size_t size){
		size_t x;
		size_t y;
		T key;

		for (x = 1; x < size; x++){
			//get data
			key = data[x];

			y = (x - 1);

			while (y >= 0 && data[y] > key){
				//Set data y+1 to data y
				data[y + 1] = data[y];
				//DEC y
				y--;
			}
			//Set data with key
			data[y + 1] = key;
		}
	}
	//Shell sort
	template <typename T>
	void shell_sort(T*data, const size_t size){
		T da;
		size_t x;
		size_t y;
		int interval = 1;

		while (interval <= size / 3){
			interval *= (3 + 1);
		}

		while (interval > 0){

			for (x = interval; x < size; x++){
				//Get data
				da = data[x];
				//Set y to x
				y = x;
				//Do the sorting
				while (y > interval - 1 && data[y - interval] >= da){
					data[y] = data[y - interval];
					y -=interval;
				}
				//Set data to da
				data[y] = da;
			}
			interval += (-1 * 3);
		}
	}

	//Selection sort algorithm
	template <typename T>
	void selection_sort(T*data, const size_t size){
		T temp;
		size_t min;

		for (size_t x = 0; x < size - 1; x++){
			//Get minimum element
			min = x;
			for (int y = x + 1; y < size; y++){
				//Compare data
				if (data[y] <= data[min]){
					//Set minimum element to y
					min = y;
				}
			}
			//Do swap
			temp = data[x];
			data[x] = data[min];
			data[min] = temp;
		}
	}
};

template <typename T>
void Display(T *data, const size_t size){
	size_t x = 0;
	//Just display the elements in a array
	while (x < size){
		std::cout << data[x] << " ";
		x++;
	}
	std::cout << std::endl;
}

int main(){
	//Tests
	int *nums;
	float test[6] = { 1.2, 3.6, 0.1, 6.3, 10.5, 1.3 };
	int test2[5] = { 48, 12 ,32, 28, 11 };
	double test3[7] = { 10, 18, 30, 12, 4, 11, 2.5 };
	int test4[9] = { 6, 2, 9, 1, 3, 5, 8, 4, 7 };
	size_t size = 12;
	nums = new int[size];
	TSort sort;

	//Make some random numbers and store them in nums array
	srand(time(NULL));

	for (int x = 0; x < size; x++){
		//Set random value 0..128
		nums[x] = rand() % 128;
	}

	std::cout << "Merge Sort::" << std::endl;
	//Display unsorted nums
	std::cout << "Unsorted: ";
	Display(nums, size);
	//Merge sort the nums array
	sort.merge_sort<int>(nums, 0, (size - 1));

	//Display sorted array
	std::cout << "Sorted:   ";
	Display(nums, size);
	std::cout << std::endl << "Bubble Sort::" << std::endl;

	std::cout << "Unsorted: ";
	Display(test, 6);
	sort.bubble_sort<float>(test, 6);
	std::cout << "Sorted:   ";
	Display(test, 6);

	std::cout << std::endl << "Selection Sort::" << std::endl;
	std::cout << "Unsorted:  ";
	Display(test2, 5);
	sort.selection_sort(test2, 5);
	std::cout << "Sorted:    ";
	Display(test2, 5);

	std::cout << std::endl << "insertion Sort::" << std::endl;
	std::cout << "Unsorted:  ";
	Display(test3, 7);
	sort.insertion_sort<double>(test3, 7);
	std::cout << "Sorted:    ";
	Display(test3, 7);

	std::cout << std::endl << "Shell Sort::" << std::endl;
	std::cout << "Unsorted:  ";
	Display(test4, 9);
	sort.shell_sort<int>(test4, 9);
	std::cout << "Sorted:    ";
	Display(test4, 9);

	//Clear nums array
	delete[]nums;
	system("pause");
	return EXIT_SUCCESS;
}
