#include <bits/stdc++.h>
//Recursion Top-Down: O(2^n),O(2^n)
int solve(vector<int>& cost, int n) {
	if (n < 0)
        return 0;
	if (n==0 || n==1)
        return cost[n];

	return cost[n] + min(solve(cost, n-1), solve(cost, n-2));
}
int minCostClimbingStairs(vector<int>& cost) {
	int n = cost.size();
	return min(solve(cost, n-1), solve(cost, n-2));
}

//Recursion+Memoization Top-Down: O(n),O(n)
int solve(vector<int>& cost, vector<int> &dp, int n) {
	if (n < 0) 
        return 0;
	if (n==0 || n==1) 
        return cost[n];

    if (dp[n]!=-1) 
        return dp[n];

	dp[n] = cost[n] + min(solve(cost,dp,n-1), solve(cost,dp,n-2));
    return dp[n];
}
int minCostClimbingStairs(vector<int>& cost) {
	int n = cost.size();
    vector<int> dp(n+1, -1);
	return min(solve(cost,dp,n-1), solve(cost,dp,n-2));
}

//Tabular/Bottom-Up: O(n),O(n)
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    
    vector<int> dp(n+1);
    dp[0] = cost[0];
    dp[1] = cost[1];

    for(int i=2;i<n;i++) {
        dp[i] = min(dp[i-1],dp[i-2]) + cost[i];
    }
    return min(dp[n-1],dp[n-2]);
}

//Even more simplified: O(n),O(1)
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();

    prev1 = cost[0];
    prev2 = cost[1];

    for(int i=2;i<n;i++) {
        dp[i] = min(dp[i-1],dp[i-2]) + cost[i];
    }
    return min(prev1,prev2);
}