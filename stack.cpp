#include <iostream>
#include <stack>
using namespace std;

class Stack{
    public:
    int top;
    int size;
    int* arr;

    Stack(int size){
        this->size = size;
        arr = new int[size];
        top = -1;
    }

    void push(int data){
        if(top==size-1) cout<<"Stack Overflow"<<endl;
        else arr[++top] = data;
    }

    void pop(){
        if(top==-1) cout<<"Stack Underflow"<<endl;
        else top--;
    }

    int peek(){
        return arr[top];
    }

    bool isEmpty(){
        if(top==-1) return true;
        else return false;
    }
};

void sortedInsert(stack<int> &stack, int num) {
	if(stack.empty() || stack.top()<=num) {
		stack.push(num);
		return;
	}

	int num2 = stack.top();
	stack.pop();
	sortedInsert(stack,num);
	stack.push(num2);
}

void sortStack(stack<int> &stack) { 
	if(stack.empty()) return;

	int num = stack.top();
	stack.pop();
	sortStack(stack);
	sortedInsert(stack,num);
	return;
}

int main(){
    Stack s(5);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.push(6);
    s.pop();
    s.pop();
    cout << s.peek() << endl;
    s.pop();
    cout << s.isEmpty() << endl;
    s.pop();
    s.pop();
    s.pop();
    cout << s.isEmpty() << endl;
    return 0;
}