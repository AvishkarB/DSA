#include <bits/stdc++.h>
//Recursion Top-Down O(2^n), O(2^n)
int solve(vector<int>& values, int start, int end) {
    if(start+1==end) return 0;

    int ans = INT_MAX;
    for(int i=start+1;i<end;i++) {
        ans = min(ans, values[start]*values[i]*values[end] + solve(values,start,i) + solve(values,i,end));
    }
    return ans;
}
int minScoreTriangulation(vector<int>& values) { 
    return solve(values,0,values.size()-1);
}

//Recursion+Memoization O(n*n*n),O(n*n)
int solve(vector<int>& values, int start, int end, vector<vector<int>> &dp) {
    if(start+1==end) return 0;
    if(dp[start][end]!=-1) return dp[start][end];

    int ans = INT_MAX;
    for(int i=start+1;i<end;i++) {
        ans = min(ans, values[start]*values[i]*values[end] + solve(values,start,i,dp) + solve(values,i,end,dp));
    }
    dp[start][end] = ans;
    return dp[start][end];
}
int minScoreTriangulation(vector<int>& values) {
    int n = values.size();
    vector<vector<int>> dp(n, vector<int> (n,-1));
    return solve(values,0,n-1,dp);
}

//Tabular O(n*n*n),O(n*n)
int minScoreTriangulation(vector<int>& values) {
    int n = values.size();
    vector<vector<int>> dp(n, vector<int> (n,0));

    for(int i=n-1;i>=0;i--) {
        for(int j=i+2;j<n;j++) { //j=i means same point-->no triangle, j=i+1 means a line-->no triangle, hence j=i+2 --> triangle formed
            int ans = INT_MAX;
            for(int k=i+1;k<j;k++) {
                ans = min(ans, values[i]*values[k]*values[j] + dp[i][k] + dp[k][j]);
            }
            dp[i][j] = ans;
        }
    }
    return dp[0][n-1];
}