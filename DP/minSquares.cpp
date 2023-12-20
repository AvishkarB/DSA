#include <bits/stdc++.h>
//Recursion
int solve(int n){
        if(n==0) return 0;
        if(n<0) return n;
        
        int ans = n;
        for(int i=1;i*i<=n;i++) {
            ans = min(solve(n-i*i)+1, ans);
        }
        return ans;
    }
int MinSquares(int n)
{
    return solve(n);
}

//Recursion+Memoization O(n^1.5)+O(n),O(n)
int solve(int n, vector<int> &dp){
        if(n==0) return 0;
        if(n<0) return n;
        if(dp[n]!=-1) return dp[n];
        
        int ans = n;
        for(int i=1;i*i<=n;i++) {
            ans = min(solve(n-i*i,dp)+1, ans);
        }
        dp[n] = ans;
        return dp[n];
    }
int MinSquares(int n)
{
    vector<int> dp(n+1,-1);
    return solve(n,dp);
}

//Tabular O(n^1.5),O(n)
int MinSquares(int n){
    vector<int> dp(n+1,0);
    dp[0] = 0;
    
    for(int i=1;i<=n;i++) {
        int ans = i;
        for(int j=1;j*j<=i;j++) {
            ans = (i-j*j>=0) ? min(dp[i-j*j]+1,ans) : n;
        }
        dp[i] = ans;
    }
    return dp[n];
}