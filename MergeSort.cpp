#include <iostream>
using namespace std;

void print(int* arr, int n){
	for(int i=0;i<n;i++) cout << arr[i] << " ";
	cout << endl;
}

void merge(int* arr, int l, int mid, int r){
	int len1 = mid - l +1;
	int len2 = r - mid;

	int* larr = new int[len1];
	int* rarr = new int[len2];
	for(int i=0;i<len1;i++) larr[i] = arr[l+i];
	for(int i=0;i<len2;i++) rarr[i] = arr[mid+1+i];

	int pos = l;
	int idx1 = 0;
	int idx2 = 0;
	while(idx1<len1 && idx2<len2){
		if(larr[idx1]<rarr[idx2]) arr[pos++] = larr[idx1++];
		else if(larr[idx1]>rarr[idx2]) arr[pos++] = rarr[idx2++];
		else {
			arr[pos++] = larr[idx1++];
			arr[pos++] = rarr[idx2++];
		}
	}

	while(idx1<len1) arr[pos++] = larr[idx1++];
	while(idx2<len2) arr[pos++] = rarr[idx2++];
	
	delete [] larr;
	delete [] rarr;
}

void mergesort(int* arr, int l, int r){
	if(l>=r) return;

	int mid = l + (r-l)/2;
	
	mergesort(arr,l,mid);
	mergesort(arr,mid+1,r);
	
	merge(arr,l,mid,r);
	return;
}

int main(){
	int n;
	cin >> n;
	int* arr = new int[n];
	for(int i=0;i<n;i++) cin >> arr[i];

	mergesort(arr,0,n-1);
	
	print(arr,n);

	delete [] arr;
	
	return 0;
}