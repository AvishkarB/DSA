#include <iostream>
using namespace std;

void print(int* arr, int n){
	for(int i=0;i<n;i++) cout << arr[i] << " ";
	cout << endl;
}

//asc
void selsortrec(int* arr,int n, int start){
	if(start>n) return;

	int min = arr[start], pos = start;
	for(int i=start+1;i<n;i++) {
		if(arr[i]<min) {
			min = arr[i];
			pos = i;
		}
	}
	swap(arr[start],arr[pos]);
	
	selsortrec(arr,n,start+1);
	return;
}

//desc
void insertsortrec(int* arr, int n, int start){
	if(start>n) return;

	int temp = arr[start],pos;
	for(int i=start-1;i>=0;i--)
		if(arr[i]<arr[start])
			pos = i;
	for(int j=start;j>pos;j--)
		arr[j]=arr[j-1];
	arr[pos] = temp;

	insertsortrec(arr,n,start+1);
	return;
	
}

int main(){
	int n;
	cin >> n;
	int* arr = new int[n];
	for(int i=0;i<n;i++) cin >> arr[i];

	//selsortrec(arr,n,0);
	insertsortrec(arr,n,1);
	
	print(arr,n);

    delete [] arr;
	
	return 0;
}