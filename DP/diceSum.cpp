#include <bits/stdc++.h>
//Recursion
long long solve(int& M, int& N, int X, int diceNo) {
    if(X==0 && diceNo==N) return 1;
    if(X<0 || diceNo>N) return 0;
    
    long long int count = 0;
    for(int i=1;i<=M;i++)
        count = count + solve(M,N,X-i,diceNo+1);
    return count;
}
long long noOfWays(int M , int N , int X) {
    return solve(M,N,X,0);
}

//Recursion+Memo
long long solve(int& M, int& N, int X, int diceNo, vector<vector<long long int>>& dp) {
    if(X==0 && diceNo==N) return 1;
    if(X<0 || diceNo>N) return 0;
    if(dp[X][diceNo]!=-1) return dp[X][diceNo];
    
    long long int count = 0;
    for(int i=1;i<=M;i++) {
        count = count + solve(M,N,X-i,diceNo+1,dp);
    }
    return dp[X][diceNo] = count;
}
long long noOfWays(int M , int N , int X) {
    vector<vector<long long int>> dp(X+1, vector<long long int>(N+1, -1));
    return solve(M,N,X,0,dp);
}

//Tabular
long long noOfWays(int M , int N , int X) {
    vector<vector<long long int>> dp(X+1, vector<long long int>(N+1, 0));
    dp[0][N]=1;
    
    for(int x=1;x<=X;x++) {
        for(int diceNo = N-1; diceNo>=0; diceNo--) {
            long long int count = 0;
            for(int j=1;j<=M;j++) {
                if(x-j>=0)
                    count = count + dp[x-j][diceNo+1];
            }
            dp[x][diceNo] = count;
        }
    }
    return dp[X][0];
}