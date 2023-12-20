#include <bits/stdc++.h>
using namepsace std;

bool check(int row, int column,vector<vector<int>> &board, int n) {
	//Row Check
	for(int j=column;j>=0;j--) if(board[row][j]==1) return false;

	//Diagonal Check
	for(int i=row,j=column;i>=0 && j>=0;i--,j--) if(board[i][j]==1) return false;
	for(int i=row,j=column;i<n && j>=0;i++,j--) if(board[i][j]==1) return false;

	return true;
}

void solve(int column, vector<vector<int>> &board, vector<vector<int>> &output, int n) {
	if(column==n) {
		vector<int> temp;
		for(int i=0;i<n;i++) for(int j=0;j<n;j++) temp.push_back(board[i][j]);
		output.push_back(temp);
		return;
	}

	for(int row=0;row<n;row++) {
		if(check(row,column,board,n)) {
			board[row][column]=1;
			solve(column+1,board,output,n);
			board[row][column]=0;
		}
	}
}

vector<vector<int>> nQueens(int n)
{
	vector<vector<int>> board(n,vector<int>(n,0));
	vector<vector<int>> output;
	int column = 0;
	solve(column,board,output,n);

	return output;
}