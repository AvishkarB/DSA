#include <bits/stdc++.h>
//Recursion TLE
int solve(vector<int>& prices, int index, bool buy) {
    if(index==prices.size()) return 0;

    if(buy) {
        int profit1 = -prices[index] + solve(prices,index+1,false);
        int profit2 = 0 + solve(prices,index+1,true);
        return max(profit1,profit2); 
    }
    else {
        int profit1 = prices[index] + solve(prices,index+1,true);
        int profit2 = 0 + solve(prices,index+1,false);
        return max(profit1,profit2);
    }
}
int maxProfit(vector<int>& prices) {
    return solve(prices,0,true);
}

//Recursion+Memoization O(2n),O(2n)
int solve(vector<int>& prices, int index, bool buy, vector<vector <int>>& dp) {
    if(index==prices.size()) return 0;
    if(dp[index][buy]!=-1) return dp[index][buy];

    if(buy) {
        int profit1 = -prices[index] + solve(prices,index+1,false,dp);
        int profit2 = 0 + solve(prices,index+1,true,dp);
        dp[index][buy] = max(profit1,profit2); 
    }
    else {
        int profit1 = prices[index] + solve(prices,index+1,true,dp);
        int profit2 = 0 + solve(prices,index+1,false,dp);
        dp[index][buy] = max(profit1,profit2);
    }
    return dp[index][buy];
}
int maxProfit(vector<int>& prices) {
    vector<vector <int>> dp(prices.size(),vector<int> (2,-1));
    return solve(prices,0,true,dp);
}

//Tabular O(2n),O(2n)
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector <int>> dp(n+1,vector<int> (2,0));
    
    for(int index=n-1;index>=0;index--) {
        for(int buy=0;buy<=1;buy++) {
            if(buy) {
                int profit1 = -prices[index] + dp[index+1][false];
                int profit2 = 0 + dp[index+1][true];
                dp[index][buy] = max(profit1,profit2); 
            }
            else {
                int profit1 = prices[index] + dp[index+1][true];
                int profit2 = 0 + dp[index+1][false];
                dp[index][buy] = max(profit1,profit2);
            }
        }
    }
    return dp[0][1];
}

//Tabular SPACE OPTIMIZED O(2n),O(1)
int maxProfit(vector<int>& prices) {
    vector<int> curr(2);
    vector<int> next(2,0);

    for(int index=prices.size()-1;index>=0;index--) {
        for(int buy=0;buy<=1;buy++) {
            if(buy) {
                int profit1 = -prices[index] + next[false];
                int profit2 = 0 + next[true];
                curr[buy] = max(profit1,profit2); 
            }
            else {
                int profit1 = prices[index] + next[true];
                int profit2 = 0 + next[false];
                curr[buy] = max(profit1,profit2);
            }
        }
        next = curr;
    }
    return next[1];
}