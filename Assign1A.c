#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Deque{
    int* arr;
    int size;
    int head;
    int tail;
    bool isEmpty;
    bool isFull;
};

int mod(int a, int b){
    return (a+b)%b;
}

void initialise_deque(struct Deque *d, int size){
    d->size = size;
    d->arr = (int*) calloc(d->size,sizeof(int));
    d->head = 0;
    d->tail = 0;
    d->isEmpty = true;
    d->isFull = false;
}

void add_first(struct Deque *d, int elem){
    if(d->isFull) {
        printf("Array Overflow\n");
    }
    else if(d->isEmpty) {
        d->isEmpty = false;
        d->arr[d->head] = elem;
    }
    else {
        d->head = mod(d->head-1,d->size);
        d->arr[d->head] = elem;

        if(mod(d->head-1,d->size) == d->tail)
            d->isFull = true;
    }
}

void add_last(struct Deque *d, int elem){
    if(d->isFull) {
        printf("Array Overflow\n");
    }
    else if(d->isEmpty) {
        d->isEmpty = false;
        d->arr[d->tail] = elem;
    }
    else {
        d->tail = mod(d->tail+1,d->size);
        d->arr[d->tail] = elem;

        if(mod(d->tail+1,d->size) == d->head)
            d->isFull = true;
    }
}

void remove_first(struct Deque *d){
    if(d->isEmpty)
        printf("Array Underflow\n");
    else {
        if(d->head == d->tail){
            d->isEmpty = true;
            d->isFull = false;
        }
        else {
            d->head = mod(d->head+1,d->size);
            if(d->isFull)
                d->isFull = false;
        }
    }
}

void remove_last(struct Deque *d){
    if(d->isEmpty)
        printf("Array Underflow\n");
    else {
        if(d->head == d->tail){
            d->isEmpty = true;
            d->isFull = false;
        }
        else {
            d->tail = mod(d->tail-1,d->size);
            if(d->isFull)
                d->isFull = false;
        }
    }
}

void get_first(struct Deque *d){
    if(d->isEmpty)
        printf("Deque is Empty\n");
    else
        printf("%d\n",d->arr[d->head]);
}

void get_last(struct Deque *d){
    if(d->isEmpty)
        printf("Deque is Empty\n");
    else
        printf("%d\n",d->arr[d->tail]);
}

void print_deque(struct Deque *d){
    if(d->isEmpty)
        printf("Deque is Empty\n");
    else {
        for(int i=d->head;i!=d->tail;i=mod(i+1,d->size)){
            printf("%d ", d->arr[i]);
        }
        printf("%d\n",d->arr[d->tail]);
    }
}

void delete_deque(struct Deque *d){
    free(d->arr);
}

int main(){
    struct Deque d;
    int sizeOfArray = 10;
    initialise_deque(&d,sizeOfArray);
    
    add_first(&d,2);
    print_deque(&d);
    add_first(&d,12);
    print_deque(&d);
    add_first(&d,22);
    print_deque(&d);
    add_first(&d,32);
    print_deque(&d);
    add_last(&d,42);
    print_deque(&d);
    add_first(&d,49);
    print_deque(&d);
    add_last(&d,44);
    print_deque(&d);

    remove_first(&d);
    print_deque(&d);
    remove_first(&d);
    print_deque(&d);
    remove_first(&d);
    print_deque(&d);
    add_first(&d,100);
    print_deque(&d);
    remove_first(&d);
    print_deque(&d);
    remove_last(&d);
    print_deque(&d);
    remove_first(&d);
    print_deque(&d);
    remove_first(&d);
    print_deque(&d);
    remove_first(&d);
    print_deque(&d);
    remove_first(&d);
    print_deque(&d);

    add_first(&d,200);
    print_deque(&d);
    add_last(&d,400);
    print_deque(&d);
    add_last(&d,500);
    print_deque(&d);
    add_last(&d,600);
    print_deque(&d);
    add_last(&d,700);
    print_deque(&d);
    add_last(&d,800);
    print_deque(&d);
    add_last(&d,900);
    print_deque(&d);

    remove_last(&d);
    print_deque(&d);
    remove_last(&d);
    print_deque(&d);
    remove_first(&d);
    print_deque(&d);
    remove_last(&d);
    print_deque(&d);
    remove_first(&d);
    print_deque(&d);
    add_first(&d,100);
    print_deque(&d);
    add_last(&d,69);
    print_deque(&d);
    remove_first(&d);
    print_deque(&d);
    remove_last(&d);
    print_deque(&d);
    remove_first(&d);
    print_deque(&d);
    remove_last(&d);
    print_deque(&d);
    remove_first(&d);
    print_deque(&d);

    delete_deque(&d);
    return 0;
}