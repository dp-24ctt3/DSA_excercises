#include <iostream>
using namespace std;

int fibonnacci(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	return fibonnacci(n - 1) + fibonnacci(n - 2);
}

int main() {
	int n;
	cout << "Enter a non-negative number: ";
	cin >> n;
	if (n < 0) cout << "Invalid input.";
	else {
		for (int i = 0; i < n; i++) {
			cout << fibonnacci(i) << ' ';
		}
	}
	return 0;
}