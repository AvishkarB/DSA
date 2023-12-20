//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;
// } Driver Code Ends

class Solution 
{
    public:
    int celebrity(vector<vector<int> >& M, int n) 
    {
        for(int i=0;i<n;i++) {
            int count = 0;
            for(int j=0;j<n;j++) {
                if(i==j) count++;
                else if(M[i][j]==0 && M[j][i]==1) count++;
                else break;
                }
            if(count==n) return i;
            }
            return -1;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////
class Solution 
{
    public:
    int celebrity(vector<vector<int> >& M, int n) 
    {
        stack<int> s;
        for(int i=0;i<n;i++) s.push(i);
        
        while(s.size()>1) {
            int a = s.top();
            s.pop();
            int b = s.top();
            s.pop();
            
            if(M[a][b]==1) s.push(b);
            else s.push(a);
        }
        
        int ans = s.top();
        
        for(int i=0;i<n;i++) if(M[ans][i]!=0) return -1;
        
        for(int i=0;i<n;i++) if(M[i][ans]!=1 && i!=ans) return -1;
        
        return ans;
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<vector<int> > M( n , vector<int> (n, 0));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cin>>M[i][j];
            }
        }
        Solution ob;
        cout<<ob.celebrity(M,n)<<endl;

    }
}
// } Driver Code Ends