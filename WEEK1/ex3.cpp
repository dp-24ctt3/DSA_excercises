#include <iostream>
using namespace std;

void generateBinaryStrings(int n, string str) {
	if (n == 0) {
		cout << str << endl;
		return;
	}
	generateBinaryStrings(n - 1, str + "0");
	generateBinaryStrings(n - 1, str + "1");
	
}


int main() {
	int n;
	cout << "Enter a non-negative number: ";
	cin >> n;
	if (n < 0) cout << "Invalid input.";
	else generateBinaryStrings(n, "");
	return 0;
}