#include <bits/stdc++.h>
//Recursion TLE
int solve(int& n, int a[], int curr, int prev) {
    if(curr==n) return 0;
    
    int include = (a[curr]>a[prev] || prev==-1) ? 1 + solve(n,a,curr+1,curr) : 0;
    int exclude = 0 + solve(n,a,curr+1,prev);
    return max(include,exclude);
}
int longestSubsequence(int n, int a[]) {
    return solve(n, a, 0, -1);
}

//Recursion+Memoization O(N*N)+recursion stack,O(N*N) TLE
int solve(int& n, int a[], int curr, int prev, vector<vector<int>>& dp) {
    if(curr==n) return 0;
    if(dp[curr][prev+1]!=-1) return dp[curr][prev+1];
    
    int include = (a[curr]>a[prev] || prev==-1) ? 1 + solve(n,a,curr+1,curr,dp) : 0;
    int exclude = 0 + solve(n,a,curr+1,prev,dp);
    return dp[curr][prev+1] = max(include,exclude);
}
int longestSubsequence(int n, int a[]) {
    vector<vector<int>> dp(n, vector<int> (n+1, -1));
    return solve(n, a, 0, -1, dp);
}

//Tabular O(N*N),O(N*N) TLE
int longestSubsequence(int n, int a[]) {
    vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
    
    for(int curr=n-1;curr>=0;curr--) {
        for(int prev=curr-1;prev>=-1;prev--) {
            int include = (a[curr]>a[prev] || prev==-1) ? 1 + dp[curr+1][curr+1] : 0;
            int exclude = 0 + dp[curr+1][prev+1];
            dp[curr][prev+1] = max(include,exclude);
        }
    }
    return dp[0][0];
}

//Tabular SPACE OPTIMIZED O(N*N),O(N) TLE
int longestSubsequence(int n, int a[]) {
    vector<int> currentRow(n+1);
    vector<int> nextRow(n+1, 0);
    
    for(int curr=n-1;curr>=0;curr--) {
        for(int prev=curr-1;prev>=-1;prev--) {
            int include = (a[curr]>a[prev] || prev==-1) ? 1 + nextRow[curr+1] : 0;
            int exclude = 0 + nextRow[prev+1];
            currentRow[prev+1] = max(include,exclude);
        }
        nextRow = currentRow;
    }
    return nextRow[0];
}

//DP+Binary Search OPTIMAL O(NlogN),O(N)
int longestSubsequence(int n, int a[]) {
    if(n==0) return 0;
    
    vector<int> ans;
    ans.push_back(a[0]);
    
    for(int i=1;i<n;i++) {
        if(a[i]>ans.back())
            ans.push_back(a[i]);
        else {
            int index = lower_bound(ans.begin(),ans.end(),a[i]) - ans.begin();
            ans[index] = a[i];
        }
    }
    return ans.size();
}

//Russian Doll
static bool cmp(const vector<int>& a,const vector<int>& b){
    if(a[0]!=b[0]) return a[0]<b[0];
    else return a[1]>b[1];
}
int maxEnvelopes(vector<vector<int>>& envelopes) {
    sort(envelopes.begin(),envelopes.end(),cmp);
    
    vector<int> ans;

    ans.push_back(envelopes[0][1]);
    for(int i=1;i<envelopes.size();i++) {
        if(envelopes[i][1]>ans.back())
            ans.push_back(envelopes[i][1]);
        else {
            int index = lower_bound(ans.begin(),ans.end(),envelopes[i][1]) - ans.begin();
            ans[index] = envelopes[i][1];
        }
    }
    return ans.size();
}