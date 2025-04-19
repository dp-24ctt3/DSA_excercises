#include <iostream>
using namespace std;

int BinaryWithCondition(int arr[], int left, int right){
    int mid;
    while (left < right){
        mid = (left + right) / 2;
        if (arr[mid] > arr[right]) {
            left = mid + 1;
        }
        else{
            right = mid;
        }
    }

    return right;
}

int main(){
    int n;
    int arr[100];
    
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << endl << BinaryWithCondition(arr, 0, n - 1);
    return 0;
}