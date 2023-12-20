#include <iostream>
using namespace std;

class linked{
	public:
	int data;
	linked* next;

	linked(int data){
		this->data = data;
		this->next = NULL;
	}

	~linked(){
		this->next = NULL;
		delete next;
	}
};

void print(linked* head){
	linked* temp = head;
	while(temp->next!=NULL){
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << temp->data << endl;
}

void insertAt(linked* &head, int pos, int data){
	if(pos==0){
		linked* newl = new linked(data);
		newl->next = head;
		head = newl;
		return;
	}
	else{
		linked* temp = head; int count = 1;
		while(count++ < pos) temp = temp->next;

		if(temp->next==NULL){
			linked* newl = new linked(data);
			temp->next = newl;
		}
		else{
			linked* newl = new linked(data);
			newl->next = temp->next;
			temp->next = newl;
		}
	}
}

void deleteAt(linked* &head, int pos){
	if(pos==0){
		linked* oldl = head;
		head = oldl->next;
		oldl->next = NULL;
		delete oldl;
	}
	else{
		linked* temp = head; int count = 1;
		while(count++ < pos) temp = temp->next;

		linked* oldl = temp->next;
		if(oldl->next==NULL){
			temp->next = NULL;
		}
		else{
			temp->next = oldl->next;
			oldl->next = NULL;
		}
		delete oldl;
	}
}

void reverseList(linked* &head){
	linked* prev = NULL;
	linked* curr = head;
	
	while(curr!=NULL){
		linked* futr = curr->next;
		curr->next = prev;
		prev = curr;
		curr = futr;
	}
	head = prev;
}

int getLength(linked* head){
	linked* temp = head;
	int len = 0;
	while(temp!=NULL){
		len++;
		temp = temp->next;
	}
	return len;
}

void middle(linked* head){
	int len = getLength(head);
	int mid = len/2, cnt = 0;
	linked* temp = head;
	while(cnt++<mid) temp = temp->next;
	print(temp);
}

linked* kReverse(linked* &head, int k){

	if(getLength(head) < k) return head;

	linked* prev = head;
    linked* curr = head->next;
    int count= 1;
    while(count++<k) {
        linked* futr = curr->next;
        curr->next = prev;
        prev = curr;
        curr = futr;
    }

    head->next = kReverse(curr,k);

    return prev;
}

void floyds(linked* &head){
	linked* slow = head;
	linked* fast = head;
	bool loop = false;
	while(slow!=NULL && fast!=NULL && fast->next!=NULL){
		slow = slow->next;
		fast = fast->next->next;
		if(slow==fast) {
			loop = true;
			break;
		}
	}
	if(loop==true) {
		cout << "Loop detected" << endl;
		
		slow = head;
		while(slow!=fast){
			slow = slow->next;
			fast = fast->next;
		}
		cout << "Loop starts at " << slow->data << endl;

		linked* temp = slow;
		cout << "Elements present in loop: ";
		while(temp->next != slow) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << temp->data << endl;
		temp->next = NULL;
		cout << "Loop broken" << endl << endl;
	}
	else cout << "No loop detected" << endl;
}

linked* findMid(linked* head){
	linked* slow = head;
	linked* fast = head->next;
	while(fast!=NULL && fast->next != NULL){
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

linked* merge (linked* left,linked* right){

	if(left==NULL) return right;
	if(right==NULL) return left;

	linked* ans = new linked(-1);
	linked* temp = ans;
	
	while(left!=NULL && right!=NULL) {
		if(left->data < right->data) {
			temp->next = left;
			temp = temp->next;
			left = left->next;
		}
		else if(left->data > right->data) {
			temp->next = right;
			temp = temp->next;
			right = right->next;
		}
		else {
			temp->next = left;
			temp = temp->next;
			left = left->next;
			temp->next = right;
			temp = temp->next;
			right = right->next;
		}
	}

	while(left!=NULL) {
		temp->next = left;
		temp = temp->next;
		left = left->next;
	}

	while(right!=NULL) {
		temp->next = right;
		temp = temp->next;
		right = right->next;
	}

	return ans->next;
}

linked* mergeSort(linked* head){
	
	if(head->next==NULL || head==NULL) return head;
	
	linked* mid = findMid(head);

	linked* left = head;
	linked* right = mid->next;
	mid->next = NULL;

	left = mergeSort(left);
	right = mergeSort(right);

	return merge(left,right);
}

int main(){
	linked* l1 = new linked(5);
	linked* head = l1;
	print(head);

	insertAt(head,0,7);
	print(head);
	
	insertAt(head,0,8);
	print(head);

	insertAt(head,3,4);
	print(head);
	
	insertAt(head,3,69);
	print(head);

	reverseList(head);
	print(head);

	insertAt(head,3,695);
	print(head);

	reverseList(head);
	print(head);

	cout << getLength(head) << endl;

	deleteAt(head,5);
	print(head);

	deleteAt(head,0);
	print(head);

	deleteAt(head,0);
	print(head);

	deleteAt(head,0);
	print(head);

	deleteAt(head,0);
	print(head);

	reverseList(head);
	print(head);

	middle(head);
	
	insertAt(head,0,7);
	print(head);

	middle(head);

	insertAt(head,1,5);
	print(head);

	insertAt(head,0,1);
	print(head);

	insertAt(head,2,15);
	print(head);

	middle(head);

	insertAt(head,4,17);
	print(head);
	
	insertAt(head,4,17);
	print(head);

	insertAt(head,4,1);
	print(head);

	middle(head);

	head = kReverse(head,6);
	print(head);

	head = kReverse(head,2);
	print(head);

	//head->next->next->next->next->next = head->next;
	floyds(head);
	floyds(head);

	linked* result = mergeSort(head);
	print(result);
}