#include <bits/stdc++.h>
//Recursion
int solve(vector<int>& nums1, vector<int>& nums2, int index, bool swapped) {
    if(index==nums1.size()) return 0;

    int prev1 = nums1[index-1];
    int prev2 = nums2[index-1];

    if(swapped)
        swap(prev1,prev2);

    int ans = INT_MAX;
    if(nums1[index]>prev1 && nums2[index]>prev2)
        ans = min(ans, 0 + solve(nums1,nums2,index+1,0));
    
    if(nums1[index]>prev2 && nums2[index]>prev1)
        ans = min(ans, 1 + solve(nums1,nums2,index+1,1));
    
    return ans;
}
int minSwap(vector<int>& nums1, vector<int>& nums2) {
    nums1.insert(nums1.begin(),-1);
    nums2.insert(nums2.begin(),-1);
    bool swapped = 0;
    return solve(nums1,nums2,1,swapped);
}

//Recursion+Memo
int solve(vector<int>& nums1, vector<int>& nums2, int index, bool swapped, vector<vector<int>>& dp) {
    if(index==nums1.size()) return 0;
    if(dp[index][swapped]!=-1) return dp[index][swapped];

    int prev1 = nums1[index-1];
    int prev2 = nums2[index-1];

    if(swapped)
        swap(prev1,prev2);

    int ans = INT_MAX;
    if(nums1[index]>prev1 && nums2[index]>prev2) //no swap
        ans = min(ans, 0 + solve(nums1,nums2,index+1,0,dp));
    
    if(nums1[index]>prev2 && nums2[index]>prev1) //swap
        ans = min(ans, 1 + solve(nums1,nums2,index+1,1,dp));
    
    return dp[index][swapped] = ans;
}
int minSwap(vector<int>& nums1, vector<int>& nums2) {
    nums1.insert(nums1.begin(),-1);
    nums2.insert(nums2.begin(),-1);
    bool swapped = 0;
    vector<vector<int>> dp(nums1.size(), vector<int> (2, -1));
    return solve(nums1,nums2,1,swapped,dp);
}

//Tabular
int minSwap(vector<int>& nums1, vector<int>& nums2) {
    nums1.insert(nums1.begin(),-1);
    nums2.insert(nums2.begin(),-1);
    int n = nums1.size();

    vector<vector<int>> dp(n+1, vector<int> (2, 0));
    for(int index=n-1;index>=1;index--) {
        for(int swapped=1;swapped>=0;swapped--) {
            int prev1 = nums1[index-1];
            int prev2 = nums2[index-1];

            if(swapped)
                swap(prev1,prev2);

            int ans = INT_MAX;
            if(nums1[index]>prev1 && nums2[index]>prev2)
                ans = min(ans, 0 + dp[index+1][0]);
            
            if(nums1[index]>prev2 && nums2[index]>prev1)
                ans = min(ans, 1 + dp[index+1][1]);
            
            dp[index][swapped] = ans;
        }
    }
    return dp[1][0];
}

//Tabular SPACE OPTIMIZED
int minSwap(vector<int>& nums1, vector<int>& nums2) {
    nums1.insert(nums1.begin(),-1);
    nums2.insert(nums2.begin(),-1);
    int n = nums1.size();
    vector<int> curr(2);
    vector<int> next(2, 0);

    for(int index=n-1;index>=1;index--) {
        for(int swapped=1;swapped>=0;swapped--) {
            int prev1 = nums1[index-1];
            int prev2 = nums2[index-1];

            if(swapped)
                swap(prev1,prev2);

            int ans = INT_MAX;
            if(nums1[index]>prev1 && nums2[index]>prev2)
                ans = min(ans, 0 + next[0]);
            
            if(nums1[index]>prev2 && nums2[index]>prev1)
                ans = min(ans, 1 + next[1]);
            
            curr[swapped] = ans;
        }
        next = curr;
    }
    return next[0];
}