#include <iostream>
#include <queue>
using namespace std;

class heap {
  public:
	int size;
	int arr[100];

	heap(){
		size = 0;
		arr[size] = -1;
	}

	void insert(int data) {
		size++;
		int index = size;
		arr[index] = data;
		
		while(index>1) {
			int parent = index/2;
			if(arr[parent] < arr[index])
				swap(arr[parent],arr[index]);
			else return;
			index = parent;
		}
	}

	void print() {
		for(int i=1;i<=size;i++) cout << arr[i] << " ";
		cout << endl;
	}

	void deleteHeap() {
		if(size==0) {
			cout << "Already Empty" << endl;
			return;
		}
		
		arr[1]=arr[size];
		size--;

		int index = 1;
		while(index<size){
            int leftIndex = 2*index;
            int rightIndex = 2*index + 1;
            int swapIndex = index;

            if(leftIndex<=size && arr[swapIndex]<arr[leftIndex]) swapIndex = leftIndex;
            if(rightIndex<=size && arr[swapIndex]<arr[rightIndex]) swapIndex = rightIndex;

            if(swapIndex!=index){
                swap(arr[index], arr[swapIndex]);
                index = swapIndex;
            }
            else return ;
        }
	}

};

//1-indexing
void heapify(int arr[], int n, int i) {
	int largest = i;
	int left = 2*i;
	int right = 2*i+1;

	if(left<=n && arr[left]>arr[largest])
		largest = left;
	if(right<=n && arr[right]>arr[largest])
		largest = right;

	if(largest!=i) {
		swap(arr[largest],arr[i]);
		heapify(arr,n,largest);
	}
}

//0-indexing
// void heapify(int arr[], int n, int i) {
// 	int largest = i;
// 	int left = 2*i+1;
// 	int right = 2*i+2;

// 	if(left<n && arr[left]>arr[largest]) largest = left;
// 	if(right<n && arr[right]>arr[largest]) largest = right;

// 	if(largest!=i) {
// 		swap(arr[largest],arr[i]);
// 		heapify(arr,n,largest);
// 	}
// }

void print(int arr[],int n) {
	for(int i=1;i<=n;i++) cout << arr[i] << " ";
	cout << endl;
}

void heapSort(int arr[], int n) {
	int size = n;
	while(size>1) {
		swap(arr[1],arr[size]);
		size--;
		
		/*int index = 1;
		while(index<size){
            int leftIndex = 2*index;
            int rightIndex = 2*index + 1;
            int swapIndex = index;

            if(leftIndex<=size && arr[swapIndex]<arr[leftIndex]) swapIndex = leftIndex;
            if(rightIndex<=size && arr[swapIndex]<arr[rightIndex]) swapIndex = rightIndex;

            if(swapIndex!=index){
                swap(arr[index], arr[swapIndex]);
                index = swapIndex;
            }
            else break;
        } OR just heapify */
		heapify(arr,size,1);
	}
}

int main() {
    heap h1;
	h1.insert(3);
	h1.insert(1);
	h1.insert(4);
	h1.insert(2);
	h1.insert(5);
	h1.insert(6);
	h1.insert(8);
	h1.insert(99);
	h1.insert(32);
	h1.print();
	h1.deleteHeap();
	h1.print();

	//heapify an array
	int arr1[8] = {-1,34,123,543,1,23,7,10};
	int n = 7;
	for(int i=n/2;i>=1;i--) heapify(arr1,n,i); //1-indexing
	//for(int i=n/2-1;i>=0;i--) heapify(arr1,n,i); //0-indexing

	print(arr1,7);

	//Heap Sort
	heapSort(arr1,7);
	print(arr1,7);
	heapSort(h1.arr,h1.size);
	h1.print();

	priority_queue<int> maxheap;
	priority_queue< int, vector<int>, greater<int> > minheap;
}