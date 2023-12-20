#include <bits/stdc++.h>
//Recursion 
int solve(vector<int>& obstacles, int currpos, int currlane) {
    if(currpos==obstacles.size()-1) return 0; //base case

    if (obstacles[currpos+1]!=currlane) { //go straight
        return solve(obstacles,currpos+1,currlane);
    }
    else { //sideways jump
        int ans = INT_MAX; //we need min jumps
        for(int i=1;i<=3;i++) {
            if(currlane!=i && obstacles[currpos]!=i) //not jumping into same lane and lane is free of obstacles
                ans = min(ans, 1 + solve(obstacles,currpos,i));
        }
        return ans;
    }
}
int minSideJumps(vector<int>& obstacles) {
    return solve(obstacles,0,2);
}

//Recursion+Memoization
int solve(vector<int>& obstacles, int currpos, int currlane, vector<vector<int>>& dp) {
    if(currpos == obstacles.size()-1) return 0;
    if(dp[currlane][currpos]!=-1) return dp[currlane][currpos];

    if (obstacles[currpos+1]!=currlane) {
        return solve(obstacles,currpos+1,currlane,dp);
    }
    else {
        int ans = INT_MAX;
        for(int i=1;i<=3;i++) {
            if(currlane!=i && obstacles[currpos]!=i)
                ans = min(ans, 1 + solve(obstacles,currpos,i,dp));
        }
        dp[currlane][currpos] = ans;
        return dp[currlane][currpos];
    }
}
int minSideJumps(vector<int>& obstacles) {
    vector<vector<int>> dp(4, vector<int> (obstacles.size(),-1));
    return solve(obstacles,0,2,dp);
}

//Tabular
int minSideJumps(vector<int>& obstacles) {
    int n = obstacles.size()-1;
    vector<vector<int>> dp(4, vector<int> (n+1,0));
    // dp[1][n] = 0;
    // dp[2][n] = 0;
    // dp[3][n] = 0;

    for(int currpos=n-1;currpos>=0;currpos--) {
        for(int currlane=1;currlane<=3;currlane++) {
            if (obstacles[currpos+1]!=currlane) {
                dp[currlane][currpos] = dp[currlane][currpos+1];
            }
            else {
                int ans = INT_MAX;
                for(int i=1;i<=3;i++) {
                    if(currlane!=i && obstacles[currpos]!=i)
                        ans = min(ans, 1 + dp[i][currpos+1]);
                }
                dp[currlane][currpos] = ans;
            }
        }
    }
    return min(dp[2][0],min(1+dp[1][0],1+dp[3][0])); //starting point is (2,0), so we've to add 1 sidejump to (1,0) and (3,0)
}

//Tabular SPACE OPTIMIZED
int minSideJumps(vector<int>& obstacles) {
    int n = obstacles.size()-1;
    vector<int> curr(4);
    vector<int> next(4, 0);

    for(int currpos=n-1;currpos>=0;currpos--) {
        for(int currlane=1;currlane<=3;currlane++) {
            if (obstacles[currpos+1]!=currlane) {
                curr[currlane] = next[currlane];
            }
            else {
                int ans = INT_MAX;
                for(int i=1;i<=3;i++) {
                    if(currlane!=i && obstacles[currpos]!=i)
                        ans = min(ans, 1 + next[i]);
                }
                curr[currlane] = ans;
            }
        }
        next = curr;
    }
    return min(next[2],min(1+next[1],1+next[3]));
}