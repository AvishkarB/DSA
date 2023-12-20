#include <iostream>
using namespace std;

void print(int* arr, int n){
	for(int i=0;i<n;i++) cout << arr[i] << " ";
	cout << endl;
}

void quicksort(int* arr, int l, int r){
	
	if(l>=r) return;
	
	int pivot = arr[l], count = 0;
	for(int i=l+1;i<=r;i++) if(arr[i]<pivot) count++;

	int pivotidx = l+count;
	swap(arr[l],arr[pivotidx]);
	
	int i=l, j=r;
	while(i<pivotidx && j>pivotidx) {
		if(arr[i]>=pivot && arr[j]<=pivot) swap(arr[i++],arr[j--]);
		else if(arr[i]<pivot) i++;
		else if(arr[j]>pivot) j--;
	}
	/*while(i<pivotidx && j>pivotidx) {
		while (arr[i]<pivot) i++;
		while (arr[j]>pivot) j--;
		if(i<pivotidx && j>pivotidx) swap(arr[i++],arr[j--]);
	}*/

	quicksort(arr,l,pivotidx-1);
	quicksort(arr,pivotidx+1,r);
	return;
}

int main(){
	int n;
	cin >> n;
	int* arr = new int[n];
	for(int i=0;i<n;i++) cin >> arr[i];

	quicksort(arr,0,n-1);
	
	print(arr,n);

	delete [] arr;
	
	return 0;
}