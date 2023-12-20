#include <iostream>

using namespace std;

int binarySearch(int arr[], int size, int key){
    int left = 0, right = size-1;

    while(left<=right){
        int mid = left + (right-left)/2;
        if(key==arr[mid]) return mid;
        else if(key>arr[mid]) left = mid+1;
        else right = mid-1;
    }
    return -1;
}

int main(){
    int even[8] = {2,5,7,9,11,15,21,25};
    int odd[7] = {3,5,7,10,31,54,70};
    cout << binarySearch(even,8,25) << endl;
    cout << binarySearch(odd,7,35) << endl;
    return 0;
}