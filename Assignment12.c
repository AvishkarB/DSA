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

bool isEmpty(struct Deque *d){
    return (d->isEmpty);
}

int get_first(struct Deque *d){
    return (d->arr[d->head]);
}

int get_last(struct Deque *d){
    return (d->arr[d->tail]);
}

void delete_deque(struct Deque *d){
    free(d->arr);
}

int main() {
    char* filename = "maze1.txt";
    FILE* file = fopen(filename,"r"); 
    
    char string[100];
    fgets(string,sizeof(string),file);
    
    int col = 0;
    while(string[col]=='#')
        col++;

    int row = 1;
    while (fgets(string,sizeof(string),file))
        row++;

    fclose(file);

    int** maze = (int**) malloc(row*sizeof(int*));
    for(int i=0;i<row;i++)
        maze[i] = (int*) malloc(col*sizeof(char));

    file = fopen(filename,"r");
    
    int i = 0;
    int startrow, startcol, endrow, endcol;
    while (fgets(string,sizeof(string),file)){
        for(int j=0;j<col;j++){
            maze[i][j] = string[j];
            if(string[j] == 'S') {
                startrow = i;
                startcol = j;
            }
            else if(string[j] == 'E') {
                endrow = i;
                endcol = j;
            }
        }
        i++;
    }
    fclose(file);

    struct Deque d;
    int sizeOfArray = row*col;
    initialise_deque(&d,sizeOfArray);
    add_first(&d, startrow*row + startcol);
    bool solved = false;

    while(!isEmpty(&d)) {
        int L = get_first(&d);
        remove_first(&d);
        int r = L/row;
        int c = mod(L,row);

        if(maze[r][c] == 'E') {
            solved = true;
            break;
        }
        
        if(maze[r][c] == '#' || maze[r][c] == '.')
            continue;
        else {
            maze[r][c] = '.';
            
            //LEFT RIGHT
            if(endcol > c) {
                add_first(&d, r*row + (c+1));
                add_last(&d, r*row + (c-1));
            }
            else if(endcol < c) {
                add_first(&d, r*row + (c-1));
                add_last(&d, r*row + (c+1));
            }
            else {
                add_last(&d, r*row + (c+1));
                add_last(&d, r*row + (c-1));
            }

            //UP DOWN
            if(endrow > r) {
                add_first(&d, (r-1)*row + c);
                add_last(&d, (r+1)*row + c);
            }
            else if(endrow < r) {
                add_first(&d, (r+1)*row + c);
                add_last(&d, (r-1)*row + c);
            }
            else {
                add_last(&d, (r-1)*row + c);
                add_last(&d, (r+1)*row + c);
            }
        }
    }

    if(solved) {
        printf("MAZE SOLVED!!! \n");
        printf("Here is your solved maze: \n");
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(i==startrow && j==startcol)
                    printf("S");
                else
                    printf("%s",maze[i][j]);
            }
            printf("\n");
        }
    }
    else printf("MAZE NOT SOLVED :( \n");


    for(int i=0;i<row;i++)
        free(maze[i]);
    free(maze);
    return 0;
}