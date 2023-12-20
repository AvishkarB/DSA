#include<bits/stdc++.h>
//Recursion: O(3^n),O(3^n)
int solve(int n, int &x, int &y, int &z) {
	if(n==0) return 0;
	if(n<0) return INT_MIN;

	int counta = solve(n-x,x,y,z) + 1;
	int countb = solve(n-y,x,y,z) + 1;
	int countc = solve(n-z,x,y,z) + 1;
	return max(counta,max(countb,countc));
}
int cutSegments(int n, int x, int y, int z) {
	int ans = solve(n,x,y,z);
	if(ans<0) return 0;
	return ans;
}

//Recursion+Memoization: O(n),O(n)
int solve(int n, int &x, int &y, int &z, vector<int> &dp) {
	if(n==0) return 0;
	if(n<0) return INT_MIN;
	if(dp[n]!=-1) return dp[n];

	int counta = solve(n-x,x,y,z,dp) + 1;
	int countb = solve(n-y,x,y,z,dp) + 1;
	int countc = solve(n-z,x,y,z,dp) + 1;
	dp[n] = max(counta,max(countb,countc));
	return dp[n];
}
int cutSegments(int n, int x, int y, int z) {
	vector<int> dp(n+1,-1);
	dp[n] = solve(n,x,y,z,dp);
	if(dp[n]<0) return 0;
	return dp[n];
}

//Tabular Bottom-Up: O(n),O(n)
int cutSegments(int n, int x, int y, int z) {
	vector<int> dp(n+1,-1);
	dp[0] = 0;
	for(int i=1;i<=n;i++) {
		int counta = (i>=x && dp[i-x]!=-1) ? dp[i-x]+1 : -1;
		int countb = (i>=y && dp[i-y]!=-1) ? dp[i-y]+1 : -1;
		int countc = (i>=z && dp[i-z]!=-1) ? dp[i-z]+1 : -1;
		dp[i] = max(counta,max(countb,countc));
	}
	if(dp[n]==-1) return 0;
	return dp[n];
}