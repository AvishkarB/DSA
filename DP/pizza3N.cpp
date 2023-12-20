#include <bits/stdc++.h>
//Recursion TLE
int solve(int index, int end, vector<int>& slices, int slice) {
    if(slice==0 || index>=end)
        return 0;
    
    int eat = slices[index] + solve(index+2,end,slices,slice-1);
    int notEat = 0 + solve(index+1,end,slices,slice);
    return max(eat,notEat);
}
int maxSizeSlices(vector<int>& slices) {
    int n = slices.size();
    int ans1 = solve(0,n-1,slices,n/3);
    int ans2 = solve(1,n,slices,n/3);
    return max(ans1,ans2);
}

//Recursion+Memo
int solve(int index, int end, vector<int>& slices, int slice, vector<vector<int>>& dp) {
    if(slice==0 || index>=end) return 0;
    if(dp[index][slice]!=-1) return dp[index][slice];
    
    int eat = slices[index] + solve(index+2,end,slices,slice-1,dp);
    int notEat = 0 + solve(index+1,end,slices,slice,dp);
    return dp[index][slice] = max(eat,notEat);
}
int maxSizeSlices(vector<int>& slices) {
    int n = slices.size();
    vector<vector<int>> dp(n, vector<int>(n/3+1, -1));
    int ans1 = solve(0,n-1,slices,n/3,dp);
    vector<vector<int>> dp2(n, vector<int>(n/3+1, -1));
    int ans2 = solve(1,n,slices,n/3,dp2);

    return max(ans1,ans2);
}

//Tabular
int maxSizeSlices(vector<int>& slices) {
    int n = slices.size();

    vector<vector<int>> dp(n+1, vector<int>(n/3+1, 0));
    for(int index=n-2;index>=0;index--) {
        for(int slice=1;slice<=n/3;slice++) {
            int eat = slices[index] + dp[index+2][slice-1];
            int notEat = 0 + dp[index+1][slice];
            dp[index][slice] = max(eat,notEat);
        }
    }

    vector<vector<int>> dp2(n+2, vector<int>(n/3+1, 0));
    for(int index=n-1;index>=1;index--) {
        for(int slice=1;slice<=n/3;slice++) {
            int eat = slices[index] + dp2[index+2][slice-1];
            int notEat = 0 + dp2[index+1][slice];
            dp2[index][slice] = max(eat,notEat);
        }
    }
    
    return max(dp[0][n/3],dp2[1][n/3]);
}