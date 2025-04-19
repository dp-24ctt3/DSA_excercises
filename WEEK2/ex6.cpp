#include <iostream>
using namespace std;

bool isSumExist(int n, int arr[], int target){
    int left = 0;
    int right = n - 1;

    while (left < right){
        int sum = arr[left] + arr[right];
        if (sum > target){
            right--;
        }
        else if (sum < target){
            left++;
        }
        else{
            return true;
        }
    }

    return false;
}

int main(){
    int n, target;
    int arr[100];
    
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter the target number: ";
    cin >> target;

    if (isSumExist(n, arr, target)) cout << "YES";
    else cout << "NO";

    return 0;
}