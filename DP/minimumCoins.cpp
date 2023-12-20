#include <bits/stdc++.h>
//Recursion Top-Down: O(n^x),O(n^x) ig not sure
int solve(vector<int> &num, int x) {
    if(x==0) return 0;
    if(x<0) return INT_MAX;

    int mini = INT_MAX;
    for(int i=0;i<num.size();i++) {
        int ans = solve(num,x-num[i]);
        if(ans!=INT_MAX)
            mini = min(mini,ans+1);
    }
    return mini;
}
int minimumElements(vector<int> &num, int x)
{   
    int ans = solve(num,x);

    if(ans!=INT_MAX) return ans;
    else return -1;
}

//Recursion+Memoization Top-Down: O(n*x),O(x)
int solve(vector<int> &num, vector<int> &dp, int x) {
    if(x==0) return 0;
    if(x<0) return INT_MAX;
    if(dp[x]!=-1) return dp[x];

    int mini = INT_MAX;
    for(int i=0;i<num.size();i++) {
        int ans = solve(num,dp,x-num[i]);
        if(ans!=INT_MAX)
            mini = min(mini,ans+1);
    }
    dp[x] = mini;
    return dp[x];
}
int minimumElements(vector<int> &num, int x)
{   
    vector<int> dp(x+1, -1);
    dp[x] = solve(num,dp,x);

    if(dp[x]!=INT_MAX) return dp[x];
    else return -1;
}

//Tabular Bottom-Up: O(n*x),O(x)
int minimumElements(vector<int> &num, int x)
{   
    vector<int> dp(x+1, INT_MAX);
    dp[0] = 0;
    
    for(int j=1;j<=x;j++) {
        for(int i=0;i<num.size();i++) {
            if(j-num[i]>=0 && dp[j-num[i]]!=INT_MAX)
                dp[j] = min(dp[j],dp[j-num[i]]+1);
        }
    }

    if(dp[x]!=INT_MAX) return dp[x];
    else return -1;
}