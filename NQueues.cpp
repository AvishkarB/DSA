#include <bits/stdc++.h>

class NQueues
{   
    int* arr;
    int freespot;
    int* next;
    int* front;
    int* rear;

public:
    // Initialize your data structure.
    NQueues(int N, int S)
    {
        arr = new int[S];
        freespot = 0;

        next = new int[S];
        for(int i=0;i<S-1;i++) next[i]=i+1;
        next[S-1]=-1;

        front = new int[N];
        rear = new int[N];
        for(int i=0;i<N;i++) {
            front[i] = -1;
            rear[i] = -1;
        }
    }

    // Pushes 'X' into the Mth queue. Returns true if it gets pushed into the stack, and false otherwise.
    bool enqueue(int data, int m)
    {   
        if(freespot==-1) return false;

        int index = freespot;
        arr[index] = data;
        freespot = next[index];
        if(front[m-1]==-1) front[m-1] = index;
        else next[rear[m-1]] = index;
        rear[m-1] = index;
        next[index] = -1;

        return true;
    }

    // Pops top element from Mth queue. Returns -1 if the stack is empty, otherwise returns the popped element.
    int dequeue(int m)
    {
        if(front[m-1]==-1) return -1;

        int index = front[m-1];
        front[m-1] = next[index];
        next[index] = freespot;
        freespot = index;

        return arr[index];
    }
};