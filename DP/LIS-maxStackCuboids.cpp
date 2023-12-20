#include <bits/stdc++.h>

bool check(vector<int>& base, vector<int>& newBox) {
    if(newBox[0]<=base[0] && newBox[1]<=base[1] && newBox[2]<=base[2])
        return true;
    else
        return false;
}

int maxHeight(vector<vector<int>>& cuboids) {
    int n = cuboids.size();
    for(int i=0;i<n;i++) {
        sort(cuboids[i].begin(),cuboids[i].end());
    }
    sort(cuboids.begin(),cuboids.end());

    vector<int> currRow(n+1);
    vector<int> nextRow(n+1, 0);
    
    for(int curr=n-1;curr>=0;curr--) {
        for(int prev=curr-1;prev>=-1;prev--) {
            int include = 0;
            if (prev==-1 || check(cuboids[curr],cuboids[prev]))
                include = cuboids[curr][2] + nextRow[curr+1];
            int exclude = 0 + nextRow[prev+1];
            currRow[prev+1] = max(include,exclude);
        }
        nextRow = currRow;
    }
    return nextRow[0];
}