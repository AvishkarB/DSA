#include <bits/stdc++.h>
int maxCoins(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int> (n,0));
    for(int l=1;l<=n;l++) {
        for(int i=0;i<=n-l;i++) {
            int j = i+l-1;
            for(int k=i;k<=j;k++) {
                int left = (k==i) ? 0 : dp[i][k-1];
                int right = (k==j) ? 0 : dp[k+1][j];
                int value = (i==0 ? 1 : nums[i-1]) * nums[k] * (j==n-1 ? 1 : nums[j+1]);
                dp[i][j] = max(dp[i][j], left+value+right);
            }
        }
    }
    return dp[0][n-1];
}