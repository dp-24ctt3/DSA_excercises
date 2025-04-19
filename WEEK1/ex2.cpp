#include <iostream>
using namespace std;

int factorial(int n) {
	// n! = n*(n - 1)*(n - 2)*...*1 = n*(n - 1)!	with 0! = 1
	if (n == 0) return 1;
	return n * factorial(n - 1);
}

int main() {
	int n;
	cout << "Enter a non-negative number: ";
	cin >> n;
	if (n < 0) cout << "Invalid input.";
	else cout << factorial(n);
	return 0;
}