#include <iostream>
using namespace std;

class LL {
public:
int data;
LL* next;

LL(int data){
	this->data = data;
	this->next = this;
}

~LL(){
	delete next;
	this->next = NULL;
}
};

void print(LL* &head){
	if(head == NULL) {
		cout << "Empty Linked List" << endl;
		return;
	}
	cout << head->data << " ";
	LL* temp = head->next;
	while(temp!=head){
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}

void insertAtPos(LL* &head,int pos, int data){
	if(pos==0) {
		LL* temp = head;
		while(temp->next!=head) temp = temp->next;
		
		LL* newl = new LL(data);
		newl->next = head;
		temp->next = newl;
		head = newl;
		return;
	}
	
	LL* temp = head; int cnt=1;
	while(cnt++<pos) temp = temp->next;
	
	LL* newl = new LL(data);
	newl->next = temp->next;
	temp->next = newl;
}

void deleteAtPos(LL* &head,int pos){

	if(pos==0) {
		if(head == NULL || head->next == head) {
			head=NULL;
			return;
		}
		
		LL* temp = head;
		while(temp->next!=head) temp = temp->next;
		
		LL* oldl = head;
		temp->next = head->next;
		head = head->next;
		oldl->next = NULL;
		delete oldl;
	}
	else {
		LL* temp = head; int cnt=1;
		while(cnt++<pos) temp = temp->next;
		
		LL* oldl = temp->next;
		temp->next = oldl->next;
		oldl->next = NULL;
		delete oldl;
	}
}

int main(){
	LL* l1 = new LL(7);
	LL* head = l1;
	print(head);

	insertAtPos(head,1,10);
	print(head);

	insertAtPos(head,0,65);
	print(head);

	insertAtPos(head,3,69);
	print(head);

	insertAtPos(head,3,34.5);
	print(head);
	
	deleteAtPos(head,4);
	print(head);

	deleteAtPos(head,0);
	print(head);

	deleteAtPos(head,1);
	print(head);

	deleteAtPos(head,0);
	print(head);
	
	deleteAtPos(head,0);
	print(head);
	
	deleteAtPos(head,0);
	print(head);
	
	return 0;
}