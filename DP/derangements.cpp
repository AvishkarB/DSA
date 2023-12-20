#include <bits/stdc++.h>
//Recursion Top-Down: O(2^N),O(2^N)
long long int countDerangements(int n) {
    if(n==2 || n==1) return n-1;
    return (n-1)*(countDerangements(n-1)+countDerangements(n-2));
}

//Recursion+Memoization O(N),O(N)
long long int solve(int n, vector<long long int> &dp){
    if(n==2 || n==1) return n-1;
    if(dp[n]!=-1) return dp[n];

    dp[n] = (n-1)*(solve(n-1)+solve(n-2));
    return dp[n];
}
long long int countDerangements(int n) {
    vector<long long int> dp(n+1,-1);
    return solve(n,dp);
}

//Tabular Bottom-Up: O(N),O(N)
long long int countDerangements(int n) {
    vector<long long int> dp(n+1,0);
    dp[1] = 0;
    dp[2] = 1;
    for(int i=3;i<=n;i++) {
        dp[i] = (i-1)*(dp[i-1]+dp[i-2]);
    }
    return dp[n];
}

//Tabular Space Optimised: O(N),O(1)
long long int countDerangements(int n) {
    long long int prev1 = 0;
    long long int prev2 = 1;
    for(int i=3;i<=n;i++) {
        long long int curr = ((i-1)%MOD*(prev1%MOD+prev2%MOD)%MOD)%MOD;
        prev1 = prev2;
        prev2 = curr;
    }
    return prev2;
}