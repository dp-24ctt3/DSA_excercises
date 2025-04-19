#include <iostream>
using namespace std;

int LinearSearchwithSentinel(int n, int arr[], int key){
    int sentinel = arr[n - 1];
    arr[n - 1] = key;
    int i = 0;

    while (arr[i] != key) {
        i++;
    }

    arr[n - 1] = sentinel;
    if (i < n - 1 || arr[n - 1] == key) {
        return i;
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

    cout << LinearSearchwithSentinel(n, arr, key);
    return 0;
}
