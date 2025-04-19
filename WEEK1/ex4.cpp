#include <iostream>
using namespace std;

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
	if (n == 1) {
		cout << "Move disk 1 from rod " << from_rod << " to " << to_rod << endl;;
		return;
	}

	// move (n - 1) upper disks to aux-rod (make space to move the nth disk)
	towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);

	// move the nth disk to the last rod
	cout << "Move disk " << n << " from rod " << from_rod << " to " << to_rod << endl;

	// move the remaining (n - 1) disks onto the nth disk
	towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
	int n;
	cout << "Enter a positive number: ";
	cin >> n;
	if (n < 1) cout << "Invalid input.";
	else towerOfHanoi(n, 'A', 'C', 'B');
	return 0;
}