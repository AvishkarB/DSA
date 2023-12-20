//Recursion Top-Down: O(2^N),)(2^N)
long long int numberOfWays(int n, int k) {
    if(n==1) return k;
    if(n==2) return k+k*(k-1); //or k*k

    return (k-1)*(numberOfWays(n-1,k)+numberOfWays(n-2,k));
}

//Tabular Space Optimized: O(N),O(1)
long long int numberOfWays(int n, int k) {
    long long int prev1 = k;
    long long int prev2 = k+k*(k-1); //or k*k

    for(int i=3;i<=n;i++) {
        long long int curr = (k-1)*(prev1+prev2);
        prev1 = prev2;
        prev2 = curr;
    }
    return prev2;
}