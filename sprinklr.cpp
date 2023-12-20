#include<iostream>
using namespace std;

class ArrStack{
    public:
    int N;
    int* arr;
    int head1;
    int head2;

    public:
    ArrStack(int n){
        this->N = n;
        this->arr = new int[N];
        this->head1 = 0;
        this->head2 = N-1;
    }

    public:
    void push(int element, int num){
        if(num==1){
            arr[head1]=element;
            head1++;
        }
        else if(num==2){
            arr[head2]=element;
            head2--;
        }
        if(head1==head2){
            cout << "Stack Overflow" << endl;
        }
    }

    void pop(int num){
        if(num==1){
            head1--;
            if(head1<0)
                cout << "Stack Underflow" << endl;
        }
        else if(num==2){
            head2++;
            if(head2>=N)
                cout << "Stack Underflow" << endl;
        }
    }
};


int main(){
    int n = 15;
    ArrStack* A = new ArrStack(n);
    
    int ch;
    cin >> ch;
    if(ch==1){
        int elem, num;
        cin >> elem >> num;
        A->push(elem,num);
    }
    if(ch==2){
        int num;
        cin >> num;
        A->pop(num);
    }
    return 0;
}