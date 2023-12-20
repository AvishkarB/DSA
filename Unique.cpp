#include <iostream>

using namespace std;

void printarr(int* arr,int size){
    for(int i=0;i<size;i++) cout << arr[i] << " ";
    cout << endl;
}

bool uniqueOccurrences(int* arr, int arrSize){
    int count[arrSize];
    int pos = 0;
    for(int i=0;i<arrSize;i++){
        if (arr[i]==2000) continue;
        int counter = 0;
        int temp = arr[i];
        for(int j=0;j<arrSize;j++){
            if(temp==arr[j]){
                counter++;
                arr[j]=2000;
            }
        }
        count[pos]=counter;
        pos++;
    }
    
    for(int k=0;k<pos;k++)
        for(int l=0;l<pos;l++)
            if(count[l]==count[k] && l!=k)
                return false;
    return true;
}

int main(){
    int arr[6] = {1,2,2,1,1,3};
    int size = sizeof(arr)/sizeof(int);
    cout << uniqueOccurrences(arr,size);
    return 0;
}