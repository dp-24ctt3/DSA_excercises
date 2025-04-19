#include <iostream>
using namespace std;

bool is_sorted_ascendingly(int a[], int n) {
	// check if the last two numbers in array is sorted
	if (n == 0 || n == 1) return true;

	if (a[n - 1] < a[n - 2]) return false;
	else is_sorted_ascendingly(a, n - 1);
}

int main() {
	int arr1[] = { 1, 2, 3, 4, 4, 5 },
		arr2[] = { 3, 7, 4, 8, 6, 6 };

	if (is_sorted_ascendingly(arr1, sizeof(arr1) / sizeof(arr1[0]))) {
		cout << "Array 1 is sorted.\n";
	}
	else{
		cout << "Array 1 is NOT sorted.\n";
	}

	if (is_sorted_ascendingly(arr2, sizeof(arr2) / sizeof(arr2[0]))) {
		cout << "Array 2 is sorted.\n";
	}
	else {
		cout << "Array 2 is NOT sorted.\n";
	}

}