#include <bits/stdc++.h>
//Recursion
int solve(int &N, int arr[], int index, long long int sum) {
    if(sum==0) return 1;
    if(index>=N || sum<0) return 0;
    
    int include = solve(N,arr,index+1,sum-arr[index]);
    int exclude = solve(N,arr,index+1,sum);
    return (include||exclude);
}
int equalPartition(int N, int arr[]) {   
    long long int Totalsum = 0;
    for(int i=0;i<N;i++) Totalsum+=arr[i];

    if(Totalsum%2) return 0; //odd sum cannot be partitioned
    return solve(N,arr,0,Totalsum/2);
}

//Recursion+Memo
int solve(int &N, int arr[], int index, long long int sum, vector<vector<int>>& dp) {
    if(sum==0) return 1;
    if(index>=N || sum<0) return 0;
    if(dp[index][sum]!=-1) return dp[index][sum]; 
    
    int include = solve(N,arr,index+1,sum-arr[index],dp);
    int exclude = solve(N,arr,index+1,sum,dp);
    
    return dp[index][sum] = (include||exclude);
}
int equalPartition(int N, int arr[])
{   
    long long int Totalsum = 0;
    for(int i=0;i<N;i++) Totalsum+=arr[i];

    if(Totalsum%2) return 0;

    vector<vector<int>> dp(N, vector<int>(Totalsum/2+1,-1));
    return solve(N,arr,0,Totalsum/2,dp);
}

//Tabular
int equalPartition(int N, int arr[]) {   
    long long int Totalsum = 0;
    for(int i=0;i<N;i++)
        Totalsum+=arr[i];

    if(Totalsum%2) return 0;
    
    vector<vector<int>> dp(N+1, vector<int>(Totalsum/2+1,0));
    for(int i=0;i<N;i++) dp[i][0] = 1;
    
    for(int index=N-1;index>=0;index--) {
        for(int sum=1;sum<=Totalsum/2;sum++) {
            int include = (sum-arr[index]>=0) ? dp[index+1][sum-arr[index]] : 0;
            int exclude = dp[index+1][sum];
            dp[index][sum] = (include||exclude);
        }
    }
    return dp[0][Totalsum/2];
}

//Tabular SPACE OPTIMIZED
int equalPartition(int N, int arr[]) {   
    long long int Totalsum = 0;
    for(int i=0;i<N;i++)
        Totalsum+=arr[i];

    if(Totalsum%2) return 0;
    
    vector<int> curr(Totalsum/2+1);
    vector<int> next(Totalsum/2+1,0);
    next[0] = 1;
    
    for(int index=N-1;index>=0;index--) {
        for(int sum=1;sum<=Totalsum/2;sum++) {
            int include = 0;
            if(sum-arr[index]>=0) 
                include = next[sum-arr[index]];
            int exclude = next[sum];
            curr[sum] = (include||exclude);
        }
        next = curr;
    }
    return next[Totalsum/2];
}