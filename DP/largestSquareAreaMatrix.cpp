#include <bits/stdc++.h>
//Recursion TLE
int solve(int n, int m, vector<vector<int>> &mat, int i, int j, int &maxi) {
        if(i>=n || j>=m) return 0;
        
        int right = solve(n,m,mat,i,j+1,maxi);
        int diag = solve(n,m,mat,i+1,j+1,maxi);
        int down = solve(n,m,mat,i+1,j,maxi);
        
        if(mat[i][j]==1) {
            int ans = 1+min(right, min(diag,down));
            maxi = max(ans,maxi);
            return ans;
        }
        else return 0;
    }
int maxSquare(int n, int m, vector<vector<int>> mat){
    int maxi = 0;
    int solve(n,m,mat,0,0,maxi);
}

//Recursion+Memoization Top-Down O(n*m),O(n*m)
int solve(int n, int m, vector<vector<int>> &mat, int i, int j, int &maxi, vector<vector<int>> &dp) {
        if(i>=n || j>=m) return 0;
        if(dp[i][j]!=-1) return dp[i][j];
        
        int right = solve(n,m,mat,i,j+1,maxi,dp);
        int diag = solve(n,m,mat,i+1,j+1,maxi,dp);
        int down = solve(n,m,mat,i+1,j,maxi,dp);
        
        if(mat[i][j]==1) {
            dp[i][j] = 1 + min(right, min(diag,down));
            maxi = max(dp[i][j], maxi);
            return dp[i][j];
        }
        else return dp[i][j] = 0;
    }
int maxSquare(int n, int m, vector<vector<int>> mat){
    int maxi = 0;
    vector<vector<int>> dp(n,vector<int> (m,-1));
    dp[0][0] = solve(n,m,mat,0,0,maxi,dp);
    return maxi;
}

//Tabular Bottom-Up O(n*m),O(n*m)
int maxSquare(int n, int m, vector<vector<int>> mat){
    int maxi = 0;
    vector<vector<int>> dp(n+1,vector<int> (m+1,0));

    for(int i=n-1;i>=0;i--) {
        for(int j=m-1;j>=0;j--) {
            int right = dp[i][j+1];
            int diag = dp[i+1][j+1];
            int down = dp[i+1][j];
            
            if(mat[i][j]==1) {
                dp[i][j] = 1 + min(right, min(diag,down));
                maxi = max(dp[i][j], maxi);
            }
            else dp[i][j] = 0;
        }
    }
    return maxi;
}

//Tabular SPACE OPTIMIZED O(n*m),O(m)
int maxSquare(int n, int m, vector<vector<int>> mat){
    int maxi = 0;
    vector<int> curr(m+1,0);
    vector<int> next(m+1,0);

    for(int i=n-1;i>=0;i--) {
        for(int j=m-1;j>=0;j--) {
            int right = curr[j+1];
            int diag = next[j+1];
            int down = next[j];
            
            if(mat[i][j]==1) {
                curr[j] = 1+min(right, min(diag,down));
                maxi = max(curr[j], maxi);
            }
            else curr[j] = 0;
        }
        next = curr;
    }
    return maxi;
}

//Tabular FULLY SPACE OPTIMIZED O(n*m),O(1)
//initialise and with max element in the last row for edge cases.
//then check from n-2th row and m-2th col for the max ans.
int maxSquare(int n, int m, vector<vector<int>> mat){
    int ans = *max_element(mat[n-1].begin(), mat[n-1].end()); //edge case
    for(int i=n-2; i>=0; i--) {
        for(int j=m-2; j>=0; j--){
            if(mat[i][j]==1){
                mat[i][j] = 1 + min(mat[i][j+1], min(mat[i+1][j], mat[i+1][j+1]));
                ans = max(ans, mat[i][j]);
            }
        }
    }
    return ans;
}