#include <bits/stdc++.h>
using namespace std;

bool check(int row, int col, int k, vector<vector<int>>& sudoku, int size){
    for(int i=0;i<size;i++) {
        if(sudoku[row][i]==k) return false;
        if(sudoku[i][col]==k) return false;
        if(sudoku[3*(row/3)+i/3][3*(col/3)+i%3]==k) return false;
    }
    return true;
}

bool solve(vector<vector<int>>& sudoku, int size) {
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            if(sudoku[i][j]==0) {
                for(int k=1;k<=size;k++) {
                    if(check(i,j,k,sudoku,size)) {
                        sudoku[i][j]=k;
                        bool possible = solve(sudoku,size);
                        if(possible) return true;
                        else sudoku[i][j]=0;
                    }
                }
                return false;
            }
        }
    }
}

void solveSudoku(vector<vector<int>>& sudoku)
{
    int size = sudoku.size();
	bool solver = solve(sudoku,size);
}