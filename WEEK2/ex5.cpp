#include <iostream>
using namespace std;

bool isLargerThanTarget(int n, int arr[], int len, int target){
    int sum = 0;

    for (int i = 0; i < n - len; i++){
        sum = 0;
        for (int j = 0; j < len; j++){
            sum += arr[i + j];
            if (sum >= target){
                return true;
            }
        }
    }
    return false;
}

int LenSubarray(int n, int arr[], int target){
    int min = 1,
        max = n + 1,
        len;
    while (min < max){
        len = (min + max) / 2;
        if (isLargerThanTarget(n, arr, len, target)){
            max = len;
            cout << 1 << endl;
        }
        else{
            min = len + 1;
            cout << 0 << endl;
        }
    }

    if (min > n) return 0;
    return min;
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

    cout << LenSubarray(n, arr, target);
    return 0;
}