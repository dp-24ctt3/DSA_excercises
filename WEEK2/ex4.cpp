#include <iostream>
using namespace std;

int isValidCapacity(int n, int weights[], int days, int capacity) {
    int sum = 0;
    for (int i = 0; i < n; i++){
        if (sum + weights[i] > capacity){
            days--;
            if (days <= 0) break;
            sum = 0;
        }

        sum += weights[i];
    }
    return days;
}

int MinCapacity(int n, int weights[], int days){
    int min = weights[0];
    int max = 0;

    for (int i = 0; i < n; i++){
        max += weights[i];
    }

    // binary search
    while(min < max){
        int capacity = (min + max) / 2;
        if (isValidCapacity(n, weights, days, capacity) > 1){
            max = capacity;
        }
        else if (isValidCapacity(n, weights, days, capacity)  < 1){
            min = capacity;
        }
        else
            return capacity;
    }
}

int main(){
    int n, days;
    int weights[100];
    
    cout << "Enter the number of packages: ";
    cin >> n;

    cout << "Enter the weight of each package: ";
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    cout << "Enter number of days: ";
    cin >> days;

    cout << MinCapacity(n, weights, days);
    return 0;
}