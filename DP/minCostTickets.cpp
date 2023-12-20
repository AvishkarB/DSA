#include <bits/stdc++.h>
//Recursion Top-Down O(3^n),O(3^n)
int solve(int n, vector<int> &days, vector<int> &cost, int index) {
    if(index==n) return 0;

    int cost1 = solve(n,days,cost,index+1) + cost[0];

    int i;
    for(i=index+1;i<n && days[i]-days[index]<7;i++);
    int cost2 = solve(n,days,cost,i) + cost[1];

    int j;
    for(j=index+1;j<n && days[j]-days[index]<30;j++);
    int cost3 = solve(n,days,cost,j) + cost[2];

    return min(cost1,min(cost2,cost3));
}
int minimumCoins(int n, vector<int> days, vector<int> cost) {
    return solve(n,days,cost,0);
}

//Recursion+Memoization Top-Down O(n),O(n) but n<=365 so we can say O(1),O(1)
int solve(int n, vector<int> &days, vector<int> &cost, int index, vector<int> &dp) {
    if(index==n) return 0;
    if(dp[index]!=-1) return dp[index];

    int cost1 = solve(n,days,cost,index+1,dp) + cost[0];

    int i;
    for(i=index+1;i<n && days[i]-days[index]<7;i++);
    int cost2 = solve(n,days,cost,i,dp) + cost[1];

    int j;
    for(j=index+1;j<n && days[j]-days[index]<30;j++);
    int cost3 = solve(n,days,cost,j,dp) + cost[2];

    dp[index] = min(cost1,min(cost2,cost3));
    return dp[index];
}
int minimumCoins(int n, vector<int> days, vector<int> cost) {
    vector<int> dp(n,-1);
    dp[0] = solve(n,days,cost,0,dp);
    return dp[0];
}

//Tabular Bottom-Up O(n),O(n) but n<=365 so we can say O(1),O(1)
int minimumCoins(int n, vector<int> days, vector<int> cost) {
    vector<int> dp(n+1,INT_MAX);
    dp[n] = 0;
    for(int i=n-1;i>=0;i--) {
        int cost1 = dp[i+1] + cost[0];

        int k;
        for(k=i+1;k<n && days[k]-days[i]<7;k++);
        int cost2 = dp[k] + cost[1];

        int j;
        for(j=i+1;j<n && days[j]-days[i]<30;j++);
        int cost3 = dp[j] + cost[2];

        dp[i] = min(cost1,min(cost2,cost3));
    }
    return dp[0];
}

//Tabular FULLY OPTIMIZED USING QUEUE O(n),O(1)
int minimumCoins(int n, vector<int> days, vector<int> cost)
{
    queue<pair<int,int>> week;
    queue<pair<int,int>> month;
    int ans = 0;

    for (auto day:days) {
        while(!week.empty() && week.front().first+7 <= day) week.pop();
        while(!month.empty() && month.front().first+30 <= day) month.pop();

        week.push({day,ans+cost[1]});
        month.push({day,ans+cost[2]});

        ans = min(ans+cost[0],min(week.front().second,month.front().second));
    }
    return ans;
}