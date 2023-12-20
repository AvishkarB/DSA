#include <bits/stdc++.h>
//Recursion Top-Down TLE
int solve(vector<int> &weight, vector<int> &value, int index, int maxWeight) {
	if(index==0) {
        if(weight[0]<=maxWeight) return value[0];
        else return 0;
    }

	int include = (weight[index]<=maxWeight) ? value[index] + solve(weight,value,index-1,maxWeight-weight[index]) : 0;
	int exclude = 0 + solve(weight,value,index-1,maxWeight);

	return max(include,exclude);
}
int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	int ans = solve(weight,value,n-1,maxWeight);
	return ans;
}

//Recursion+Memoization with 2D-Array O(n*maxWeight),O(n*maxWeight)
int solve(vector<int> &weight, vector<int> &value, vector<vector<int>> &dp, int index, int maxWeight) {
	if(index==0) {
        if(weight[0]<=maxWeight) return value[0];
        else return 0;
    }
	if(dp[index][maxWeight]!=-1) return dp[index][maxWeight];

	int include = (weight[index]<=maxWeight) ? value[index] + solve(weight,value,dp,index-1,maxWeight-weight[index]) : 0;
	int exclude = 0 + solve(weight,value,dp,index-1,maxWeight);

	dp[index][maxWeight] = max(include,exclude);
	return dp[index][maxWeight];
}
int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	vector<vector<int>> dp(n, vector<int>(maxWeight+1,-1));
	dp[n-1][maxWeight] = solve(weight,value,dp,n-1,maxWeight);
	return dp[n-1][maxWeight];
}

//Tabular Bottom-Up with 2D-Array O(n*maxWeight),O(n*maxWeight)
int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	vector<vector<int>> dp(n, vector<int>(maxWeight+1));
	//base case
	for(int wt=1;wt<=maxWeight;wt++) {
		if(weight[0]<=wt) dp[0][wt] = value[0];
		else dp[0][wt] = 0;
	}

	for(int index=1;index<=n-1;index++) {
		for(int wt=1;wt<=maxWeight;wt++) {
			int include = (weight[index]<=wt) ? value[index] + dp[index-1][wt-weight[index]] : 0;
			int exclude = 0 + dp[index-1][wt];
			dp[index][wt] = max(include,exclude);
		}
	}
	return dp[n-1][maxWeight];
}

//Tabular SPACE OPTIMIZED O(n*maxWeight),O(2*maxWeight)
int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	vector<int> prev(maxWeight+1);
	vector<int> curr(maxWeight+1);
	//base case
	for(int wt=1;wt<=maxWeight;wt++) {
		if(weight[0]<=wt) prev[wt] = value[0];
		else prev[wt] = 0;
	}

	for(int index=1;index<=n-1;index++) {
		for(int wt=1;wt<=maxWeight;wt++) {
			int include = (weight[index]<=wt) ? value[index] + prev[wt-weight[index]] : 0;
			int exclude = 0 + prev[wt];
			curr[wt] = max(include,exclude);
		}
		prev = curr;
	}
	return prev[maxWeight];
}

//Tabular EVEN MORE SPACE OPTIMIZED AND FASTEST O(n*maxWeight),O(maxWeight)
int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	vector<int> curr(maxWeight+1);
	//base case
	for(int wt=1;wt<=maxWeight;wt++) {
		if(weight[0]<=wt) curr[wt] = value[0];
		else curr[wt] = 0;
	}

	for(int index=1;index<=n-1;index++) {
		for(int wt=maxWeight;wt>=1;wt--) { //Right to Left traversal to avoid overwriting since curr[wt] depends only on curr[wt] (current value) and curr[wt-weight[index]] (previous values)
			int include = (weight[index]<=wt) ? value[index] + curr[wt-weight[index]] : 0;
			int exclude = 0 + curr[wt];
			curr[wt] = max(include,exclude);
		}
	}
	return curr[maxWeight];
}

// Similar 0/1 Questions:
// 1. 0/1 Knapsack
// 2. Equal Subset Sum Partition
// 3. Subset Sum
// 4. Minimum subset sum difference
// 5. Count of subset sum
// 6. Target Sum
