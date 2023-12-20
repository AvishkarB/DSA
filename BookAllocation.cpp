#include <iostream>
using namespace std;

bool Possible(int arr[], int n, int m, int mid){
	int students = 1;
	int pages = 0;
	for(int i=0;i<n;i++){
		if(pages+arr[i]<=mid) 
			pages+=arr[i];
		else {
			students++;
			pages = arr[i];
			if(students>m || pages>mid) return false;
		}
	}
	return true;
}

int findPages(int arr[], int n, int m) {
    if(m>n) return -1;
	
	int left = 0, right = 0;
    for(int i=0;i<n;i++) right+=arr[i];

	int ans = -1;
	while(left<=right){
		int mid = left+(right-left)/2;
		if(Possible(arr,n,m,mid)){
			ans = mid;
			right = mid-1;
		}
		else left = mid+1;
	}
	return ans;
}

int main(){
    int arr[5] = {25,46,28,49,24};
    cout << findPages(arr,5,4);
    return 0;
}