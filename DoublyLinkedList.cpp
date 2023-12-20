#include <iostream>
using namespace std;

class LL {
public:
int data;
LL* next;
LL* prev;

LL(int data){
	this->data = data;
	this->next = NULL;
	this->prev = NULL;
}

~LL(){
	if(this->next != NULL){
		delete next;
		this->next = NULL;
	}
	if(this->prev != NULL){
		delete prev;
		this->prev = NULL;
	}
}
};

void print(LL* &head){
	LL* temp = head;
	
	while(temp!=NULL){
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}

int getLength(LL* head){
	LL* temp = head;
	int len=0;
	
	while(temp!=NULL){
		len++;
		temp = temp->next;
	}
	return len;
}

void insertAtHead(LL* &head,int data){
	LL* l1 = new LL(data);
	l1->next = head;
	head->prev = l1;
	head = l1;
}

void insertAtTail(LL* &tail, int data){
	LL* l1 = new LL(data);
	tail->next = l1;
	l1->prev = tail;
	tail = l1;
}

void insertAtPos(LL* &head,LL* &tail,int pos, int data){
	if(pos==0) {
		insertAtHead(head,data);
		return;
	}
	
	LL* temp = head; int cnt=1;
	while(cnt++<pos) temp = temp->next;

	if(temp->next==NULL) {
		insertAtTail(tail,data);
		return;
	}
	
	LL* newl = new LL(data);
	newl->prev = temp;
	newl->next = temp->next;
	temp->next->prev = newl;
	temp->next = newl;
}

void deleteAtPos(LL* &head,LL* &tail,int pos){

	if(pos==0) {
		LL* oldl = head;
		head = head->next;
		oldl->next = NULL;
		oldl->prev = NULL;
		head->prev = NULL;
		delete oldl;
	}
	else {
		LL* temp = head; int cnt=1;
		while(cnt++<pos) temp = temp->next;
		
		LL* oldl = temp->next;
		temp->next = oldl->next;
		if(oldl->next == NULL) tail = temp;
		else {
			oldl->next->prev = temp;
			oldl->next = NULL;
		}
		oldl->prev = NULL;
		delete oldl;
	}
}

int main(){
	LL* l1 = new LL(10);
	LL* head = l1;
	LL* tail = l1;
	print(head);
	
	insertAtHead(head,5);
	print(head);
	
	insertAtTail(tail,9);
	print(head);

	cout << "Length=" << getLength(head) << endl;
	print(head);

	insertAtPos(head,tail,2,15);
	print(head);

	insertAtPos(head,tail,4,65);
	print(head);

	insertAtTail(tail,69);
	print(head);

	deleteAtPos(head,tail,5);
	print(head);

	deleteAtPos(head,tail,0);
	print(head);

	deleteAtPos(head,tail,2);
	print(head);

	insertAtHead(head,1);
	print(head);
	
	insertAtTail(tail,2);
	print(head);
	
	return 0;
}