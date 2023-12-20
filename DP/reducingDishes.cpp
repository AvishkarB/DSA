#include <bits/stdc++.h>
//Greedy ig? Super easy and super fast lol
int maxSatisfaction(vector<int>& satisfaction) {
    int n = satisfaction.size();
    sort(satisfaction.begin(),satisfaction.end());

    int maxi = 0;
    for(int i=0;i<n;i++) {
        int sum = 0;
        for(int j=0;i+j<n;j++) {
            sum += satisfaction[j+i]*(j+1);
        }
        maxi = max(maxi,sum);
    }
    return maxi;
}

//Recursion
int solve(vector<int>& satisfaction, int index, int time) {
    if(index==satisfaction.size()) return 0;

    int include = satisfaction[index]*time + solve(satisfaction,index+1,time+1);
    int exclude = 0 + solve(satisfaction,index+1,time);

    return max(include,exclude);
}
int maxSatisfaction(vector<int>& satisfaction) {
    sort(satisfaction.begin(),satisfaction.end());
    return solve(satisfaction,0,1);
}

//Recursion+Memoization
int solve(vector<int>& satisfaction, int index, int time, vector<vector<int>> &dp) {
    if(index==satisfaction.size()) return 0;
    if(dp[index][time]!=-1) return dp[index][time]; 

    int include = satisfaction[index]*time + solve(satisfaction,index+1,time+1,dp);
    int exclude = 0 + solve(satisfaction,index+1,time,dp);

    return dp[index][time] = max(include,exclude);
}
int maxSatisfaction(vector<int>& satisfaction) {
    int n = satisfaction.size();
    sort(satisfaction.begin(),satisfaction.end());
    vector<vector<int>> dp(n, vector<int> (n+1, -1));
    return solve(satisfaction,0,1,dp);
}

//Tabular
int maxSatisfaction(vector<int>& satisfaction) {
    int n = satisfaction.size();
    sort(satisfaction.begin(),satisfaction.end());

    vector<vector<int>> dp(n+1, vector<int> (n+2, 0));
    for(int index=n-1;index>=0;index--) {
        for(int time=1;time<=n;time++) {
            int include = satisfaction[index]*time + dp[index+1][time+1];
            int exclude = 0 + dp[index+1][time];
            dp[index][time] = max(include,exclude);
        }
    }
    return dp[0][1];
}

//Tabular SPACE OPTIMIZED
int maxSatisfaction(vector<int>& satisfaction) {
    int n = satisfaction.size();
    sort(satisfaction.begin(),satisfaction.end());

    vector<int> curr(n+2);
    vector<int> next(n+2, 0);
    for(int index=n-1;index>=0;index--) {
        for(int time=1;time<=n;time++) {
            int include = satisfaction[index]*time + next[time+1];
            int exclude = 0 + next[time];
            curr[time] = max(include,exclude);
        }
        next = curr;
    }
    return next[1];
}