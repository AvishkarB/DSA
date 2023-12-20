#include <bits/stdc++.h>
using namespace std;

bool check(int x, int y, vector<vector<int>> &arr, int n) {
    if((x>=0 && x<n) && (y>=0 && y<n) && arr[x][y]==1) return true;
    else return false;
}

void solve(int x, int y, vector<vector<int>> &arr, int n, string ans, vector<string> &output) {

    if(x==n-1 && y==n-1) {
        output.push_back(ans);
        return;
    }

    arr[x][y] = -1; //marking as visited

    if(check(x+1,y,arr,n)) solve(x+1,y,arr,n,ans+"D",output);
    if(check(x,y-1,arr,n)) solve(x,y-1,arr,n,ans+"L",output);
    if(check(x,y+1,arr,n)) solve(x,y+1,arr,n,ans+"R",output);
    if(check(x-1,y,arr,n)) solve(x-1,y,arr,n,ans+"U",output);

    arr[x][y] = 1; //backtracking
}

vector<string> searchMaze(vector<vector<int>> &arr, int n) {
    string ans = "";
    vector<string> output;
    int x=0,y=0;
    if(arr[x][y]==0) return output;

    solve(x,y,arr,n,ans,output);

    return output;
}