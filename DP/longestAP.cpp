//Iterative TLE
int lengthOfLongestAP(int A[], int n) {
    if(n<=2) return n;
    
    int maxi = 0;
    for(int i=0;i<n-1;i++) {
        for(int j=i+1;j<n;j++) {
            int count = 2;
            int diff = A[j]-A[i];
            int last = A[i];
            for(int k=i-1;k>=0;k--) {
                if(last-A[k]==diff) {
                    count++;
                    last = A[k];
                }
            }
            maxi = max(maxi,count);
        }
    }
    return maxi;
}

//DP Unordered Map TLE
int lengthOfLongestAP(int A[], int n) {
    if(n<=2) return n;
    
    int maxi = 0;
    unordered_map<int,int> dp[n+1];
    
    for(int i=1;i<n;i++) {
        for(int j=0;j<i;j++) {
            int count = 1;
            int diff = A[i]-A[j];
            if(dp[j].count(diff))
                count = dp[j][diff];

            dp[i][diff] = 1 + count;
            maxi = max(maxi,dp[i][diff]);
        }
    }
    return maxi;
}

//DP 2D-array
int lengthOfLongestAP(int A[], int n) {
    if(n<=2) return n;
    
    int maxi = 0;
    vector<vector<int>> dp(n,vector<int>(A[n-1]-A[0]+1, 1));
    
    for(int i=1;i<n;i++) {
        for(int j=0;j<i;j++) {
            int diff = A[i]-A[j];
            dp[i][diff] = 1 + dp[j][diff];
            maxi = max(maxi,dp[i][diff]);
        }
    }
    return maxi;
}