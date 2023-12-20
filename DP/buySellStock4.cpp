#include <bits/stdc++.h>
//Recursion TLE
int solve(vector<int>& prices, int index, bool buy, int limit) {
    if(index==prices.size() || limit==0) return 0;

    if(buy) {
        int profit1 = -prices[index] + solve(prices,index+1,false,limit);
        int profit2 = 0 + solve(prices,index+1,true,limit);
        return max(profit1,profit2); 
    }
    else {
        int profit1 = prices[index] + solve(prices,index+1,true,limit-1);
        int profit2 = 0 + solve(prices,index+1,false,limit);
        return max(profit1,profit2);
    }
}
int maxProfit(int k, vector<int>& prices) {
    return solve(prices,0,true,k);
}

//Recursion+Memoization O(2n*k)+recursion stack,O(2n*k)
int solve(vector<int>& prices, int index, bool buy, int limit, vector<vector<vector<int>>>& dp) {
    if(index==prices.size() || limit==0) return 0;
    if(dp[index][buy][limit]!=-1) return dp[index][buy][limit];

    if(buy) {
        int profit1 = -prices[index] + solve(prices,index+1,false,limit,dp);
        int profit2 = 0 + solve(prices,index+1,true,limit,dp);
        dp[index][buy][limit] = max(profit1,profit2); 
    }
    else {
        int profit1 = prices[index] + solve(prices,index+1,true,limit-1,dp);
        int profit2 = 0 + solve(prices,index+1,false,limit,dp);
        dp[index][buy][limit] = max(profit1,profit2);
    }
    return dp[index][buy][limit];
}
int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (k+1, -1)));
    return solve(prices,0,true,k,dp);
}

//Tabular O(n*2*k),O(n*2*k)
int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (2, vector<int> (k+1, 0)));

    for(int index=n-1;index>=0;index--) {
        for(int buy=0;buy<=1;buy++) {
            for(int limit=1;limit<=k;limit++) {
                if(buy) {
                    int profit1 = -prices[index] + dp[index+1][false][limit];
                    int profit2 = 0 + dp[index+1][true][limit];
                    dp[index][buy][limit] = max(profit1,profit2);
                }
                else {
                    int profit1 = prices[index] + dp[index+1][true][limit-1];
                    int profit2 = 0 + dp[index+1][false][limit];
                    dp[index][buy][limit] = max(profit1,profit2);
                }
            }
        }
    }
    return dp[0][true][k];
}

//Tabular SPACE OPTIMIZED O(n*2*k),O(1)
int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> curr(2, vector<int> (k+1));
    vector<vector<int>> next(2, vector<int> (k+1, 0));

    for(int index=n-1;index>=0;index--) {
        for(int buy=0;buy<=1;buy++) {
            for(int limit=1;limit<=k;limit++) {
                if(buy) {
                    int profit1 = -prices[index] + next[false][limit];
                    int profit2 = 0 + next[true][limit];
                    curr[buy][limit] = max(profit1,profit2);
                }
                else {
                    int profit1 = prices[index] + next[true][limit-1];
                    int profit2 = 0 + next[false][limit];
                    curr[buy][limit] = max(profit1,profit2);
                }
            }
        }
        next = curr;
    }
    return next[true][k];
}

/////////////////////////// USING NUMBER OF OPERATIONS- (LESSER SPACE as it uses 2D and 1D arrays, instead of 3D and 2D arrays) ///////////////////////////////////////////////

//Recursion TLE
int solve(int k, vector<int>& prices, int index, int operations) {
    if(index == prices.size() || operations==2*k) return 0;

    if(operations%2 == 0) {
        int profit1 = -prices[index] + solve(k,prices,index+1,operations+1);
        int profit2 = 0 + solve(k,prices,index+1,operations);
        return max(profit1,profit2);
    }
    else {
        int profit1 = prices[index] + solve(k,prices,index+1,operations+1);
        int profit2 = 0 + solve(k,prices,index+1,operations);
        return max(profit1,profit2);
    }
}
int maxProfit(int k, vector<int>& prices) {
    return solve(k,prices,0,0);
}

//Recursion+Memoization O(2nk)+recursion stack,O(2nk)
int solve(int k, vector<int>& prices, int index, int operations, vector<vector<int>>& dp) {
    if(index == prices.size() || operations==2*k) return 0;
    if(dp[index][operations]!=-1) return dp[index][operations];

    if(operations%2 == 0) {
        int profit1 = -prices[index] + solve(k,prices,index+1,operations+1,dp);
        int profit2 = 0 + solve(k,prices,index+1,operations,dp);
        return dp[index][operations] = max(profit1,profit2);
    }
    else {
        int profit1 = prices[index] + solve(k,prices,index+1,operations+1,dp);
        int profit2 = 0 + solve(k,prices,index+1,operations,dp);
        return dp[index][operations] = max(profit1,profit2);
    }
}
int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int> (2*k, -1));
    return solve(k,prices,0,0,dp);
}

//Tabular O(2nk),O(2nk)
int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n+1, vector<int> (2*k+1, 0));

    for(int index=n-1;index>=0;index--) {
        for(int operations=0;operations<2*k;operations++) {
            if(operations%2 == 0) {
                int profit1 = -prices[index] + dp[index+1][operations+1];
                int profit2 = 0 + dp[index+1][operations];
                dp[index][operations] = max(profit1,profit2);
            }
            else {
                int profit1 = prices[index] + dp[index+1][operations+1];
                int profit2 = 0 + dp[index+1][operations];
                dp[index][operations] = max(profit1,profit2);
            }
        }
    }
    return dp[0][0];
}

//Tabular SPACE OPTIMIZED
int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    vector<int> curr(2*k+1);
    vector<int> next(2*k+1, 0);

    for(int index=n-1;index>=0;index--) {
        for(int operations=0;operations<2*k;operations++) {
            if(operations%2 == 0) {
                int profit1 = -prices[index] + next[operations+1];
                int profit2 = 0 + next[operations];
                curr[operations] = max(profit1,profit2);
            }
            else {
                int profit1 = prices[index] + next[operations+1];
                int profit2 = 0 + next[operations];
                curr[operations] = max(profit1,profit2);
            }
        }
        next = curr;
    }
    return next[0];
}