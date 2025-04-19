#include <iostream>
using namespace std;

int LinearSearch(int n, int arr[], int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

int main(){
    int n, key;
    int arr[100];
    
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter the key to search: ";
    cin >> key;

    cout << LinearSearch(n, arr, key);
    return 0;
}