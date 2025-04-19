#include <iostream>
using namespace std;


void sort(int n, int arr[]){
    //selection sort
    for (int i = 0; i < n; i++){
        int min = i;
        for (int j = i + 1; j < n; j++){
            if (arr[min] > arr[j]) min = j;
        }
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

int Triplets( int n, int arr[], int triplets[][3]){
    sort (n, arr);
    int count = 0;

    //choose arr[i] to be a fixed element
    for (int i = 0; i < n - 2; i++) {
        
        //skip the duplicated fixed element
        while (i > 0 && arr[i] == arr[i - 1]) i++;

        int left = i + 1,
            right = n - 1;

        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];
            if (sum == 0) {

                // save one valid triplet
                triplets[count][0] = arr[i];
                triplets[count][1] = arr[left];
                triplets[count][2] = arr[right];
                count++;
                
                //skip the duplicated 2nd number
                while (left < right && arr[left] == arr[left + 1]) left++;

                //skip the duplicated 3rd number
                while (left < right && arr[right] == arr[right - 1]) right--;

                //go to next value
                left++;
                right--;
                
            }
            else if (sum > 0) right--;
            else left++;
        }
    }
    return count;
}

int main(){
    int n, target;
    int arr[100];
    int triplets[100][3] = {0};
    
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "Enter the target number: ";
    cin >> target;


    int numoftriplets = Triplets(n, arr, triplets);

    //print result
    cout << '[';
    for (int i = 0; i < numoftriplets; i++){
        for (int j = 0; j < 3; j++){
            if (j == 0) cout << '[';
            cout << triplets[i][j];
            if (j < 2) cout << ", ";
        }
        cout << ']';
        if (i < numoftriplets - 1) cout << ", ";
    }
    cout << ']';

    return 0;
}


    

   