//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
#define MAX 1000
// } Driver Code Ends

class Solution{
  private:
    int largestHistogramArea(int* heights,int n) {
    
        stack<int> sn;
        sn.push(n);
        vector<int> nextSmallest(n);
        for(int i=n-1;i>=0;i--) {
            while(sn.top()!=n && heights[sn.top()]>=heights[i]) sn.pop();
            nextSmallest[i] = sn.top();
            sn.push(i);
        }
    
        stack<int> sp;
        sp.push(-1);
        vector<int> prevSmallest(n);
        for(int i=0;i<n;i++) {
            while(sp.top()!=-1 && heights[sp.top()]>=heights[i]) sp.pop();
            prevSmallest[i] = sp.top();
            sp.push(i);
        }
    
        int maxArea = 0;
        for(int i=0;i<n;i++){
            int ans = (nextSmallest[i]-prevSmallest[i]-1)*heights[i];
            maxArea = max(maxArea,ans);
        }
        return maxArea;
    }
    
  public:
    int maxRectangle1s(int M[MAX][MAX], int n, int m) {

        int maxArea = largestHistogramArea(M[0],m);
        
        for(int i=1;i<n;i++) {
            for(int j=0;j<m;j++) if(M[i][j]!=0) M[i][j]+=M[i-1][j];
            int area = largestHistogramArea(M[i],m);
            maxArea = max(area,maxArea);
        }
        return maxArea;
    }
};


//{ Driver Code Starts.
int main() {
    int T;
    cin >> T;

    int M[MAX][MAX];

    while (T--) {
        int n, m;
        cin >> n >> m;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> M[i][j];
            }
        }
        Solution obj;
        cout << obj.maxRectangle1s(M, n, m) << endl;
    }
}
// } Driver Code Ends