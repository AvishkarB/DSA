#include <bits/stdc++.h>
//Recursion: O(2^n),O(2^n)
int solve(vector<int> &nums, int x) {
    if(x==1 || x==0) return nums[x];
    if(x<0) return 0;
    return max(solve(nums,x-3),solve(nums,x-2))+nums[x];
}
int maximumNonAdjacentSum(vector<int> &nums){
    int x = nums.size()-1;
    return max(solve(nums,x-1),solve(nums,x));
}
//OR
int solve(vector<int> &nums, int n) {
    if(n<0) return 0;
    if(n==0) return nums[0];

    int incl = solve(nums,n-2) + nums[n];
    int excl = solve(nums,n-1) + 0;

    return max(incl,excl);
}
int maximumNonAdjacentSum(vector<int> &nums){
    int n = nums.size();
    int ans = solve(nums,n-1);
    return ans;
}

//Recursion+Memoization: O(2^n),O(n)
int solve(vector<int> &nums, vector<int> &dp, int x) {
    if(x==1 || x==0) return nums[x];
    if(x<0) return 0;
    if(dp[x]!=-1) return dp[x];

    dp[x] = max(solve(nums,dp,x-3),solve(nums,dp,x-2))+nums[x];
    return dp[x];
}
int maximumNonAdjacentSum(vector<int> &nums){
    int x = nums.size()-1;
    vector<int> dp(x+1,-1);
    
    dp[x] = solve(nums,dp,x);
    dp[x-1] = solve(nums,dp,x-1);
    return max(dp[x],dp[x-1]);
}
//OR
int solve(vector<int> &nums, vector<int> &dp, int n) {
    if(n<0) return 0;
    if(n==0) return nums[0];
    if(dp[n]!=-1) return dp[n];

    int incl = solve(nums,dp,n-2) + nums[n];
    int excl = solve(nums,dp,n-1) + 0;

    dp[n] = max(incl,excl);
    return dp[n];
}
int maximumNonAdjacentSum(vector<int> &nums){
    int n = nums.size();
    vector<int> dp(n,-1);
    return solve(nums,dp,n-1);;
}

//Tabular Bottom-Up: O(n),O(n)
int maximumNonAdjacentSum(vector<int> &nums){
    int n = nums.size();

    vector<int> dp(n+1,0);
    dp[1] = nums[0];
    if(1<n) dp[2] = nums[1];
    if(2<n) dp[3] = dp[1] + nums[2];

    for(int i=4;i<=n;i++) {
        dp[i] = max(dp[i-2],dp[i-3]) + nums[i-1];
    }
    return max(dp[n],dp[n-1]);
}
//OR
int maximumNonAdjacentSum(vector<int> &nums){
    int n = nums.size();
    vector<int> dp(n,0);
    dp[0] = nums[0];
    for(int i=1;i<n;i++) {
        int incl = (i>1) ? dp[i-2] + nums[i] : nums[i];
        int excl = dp[i-1] + 0;
        dp[i] = max(incl,excl);
    }
    return dp[n-1];
}

//Tabular Bottom-Up: O(n),O(1)
int maximumNonAdjacentSum(vector<int> &nums){
    int n = nums.size();
    if(n==1) return nums[0];

    int prev1 = nums[0];
    int prev2 = (1<n) ? nums[1] : 0;
    int prev3 = (2<n) ? prev1+nums[2] : 0;

    for(int i=4;i<=n;i++) {
        int curr = max(prev1,prev2) + nums[i-1];
        prev1 = prev2;
        prev2 = prev3;
        prev3 = curr;
    }
    return max(prev3,prev2);
}
//OR
int maximumNonAdjacentSum(vector<int> &nums){
    int n = nums.size();
    int prev1 = 0;
    int prev2 = nums[0];

    for(int i=1;i<n;i++) {
        int incl = prev1 + nums[i];
        int excl = prev2 + 0;
        int curr = max(incl,excl);
        prev1 = prev2;
        prev2 = curr;
    }
    return prev2;
}

//HOUSE ROBBER (First and Last are neighbours)
long long int houseRobber(vector<int>& valueInHouse)
{
    int n = valueInHouse.size();
    //from first to n-1 house
    long long int prev1 = 0;
    long long int prev2 = valueInHouse[0];
    for(int i=1;i<n-1;i++) { 
        long long int incl = prev1 + valueInHouse[i];
        long long int excl = prev2 + 0;
        long long int curr = max(incl,excl);
        prev1 = prev2;
        prev2 = curr;
    }
    long long int firstAns = prev2;

    //from second to n house
    prev1 = 0;
    prev2 = valueInHouse[1];
    for(int i=2;i<n;i++) { 
        long long int incl = prev1 + valueInHouse[i];
        long long int excl = prev2 + 0;
        long long int curr = max(incl,excl);
        prev1 = prev2;
        prev2 = curr;
    }
    long long int secondAns = prev2;

    return max(first,second);
}