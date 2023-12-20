#include <bits/stdc++.h>
using namespace std;

bool check(vector<int>& arr, int& n, int& maxSum, vector<int>& output) {
	int l = output.size();
	int ans = 0;
	for(int i=0;i<l;i++) {
		ans += (output[i]+1)*l + arr[output[i]];
		if(ans>maxSum) return false;
	}
	return true;
}

int getMaxSubLen(vector<int>& arr, int& n, int& maxSum, int index, vector<int>& output) {
	if(index==n) {
		if(check(arr,n,maxSum,output)) {
			for(int i=0;i<output.size();i++)
				cout << output[i]+1 << "*" << output.size() << "+" << arr[output[i]] << "  ";
			cout << endl;
			return 0;
		}
		else return INT_MIN;
	}

	output.push_back(index);
	int include = 1 + getMaxSubLen(arr,n,maxSum,index+1,output);
	output.pop_back();
	int exclude = 0 + getMaxSubLen(arr,n,maxSum,index+1,output);

	return max(include,exclude);
}

int main(){
	int n,maxSum;
	cin >> n >> maxSum;

	vector<int> arr(n);
	for(int i=0;i<n;i++)
	cin >> arr[i];

	vector<int> output;
	cout << getMaxSubLen(arr,n,maxSum,0,output) << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int solve(vector<vector<int>>& adj, vector<int>& val, int node) {
	int left = (adj[node][0]!=-1) ? solve(adj,val,adj[node][0]) : 0;
	int right = (adj[node][1]!=-1) ? solve(adj,val,adj[node][1]) : 0;

	return val[node-1]+max(left,right);
}

int getMaxValueSum(int& n, vector<int>& val, vector<vector<int>>& edges) {
	vector<vector<int>> adj(n+1, vector<int>(2, -1));
	for(int i=0;i<n-1;i++) {
		if(adj[edges[i][0]][0]==-1)
			adj[edges[i][0]][0] = edges[i][1];
		else
			adj[edges[i][0]][1] = edges[i][1];
	}

	int left = solve(adj,val,adj[1][0]);
	int right = solve(adj,val,adj[1][1]);

	return left+val[0]+right;
}

int main(){
	int n;
	cin >> n;

	vector<int> val(n);
	for(int i=0;i<n;i++)
	cin >> val[i];

	vector<vector<int>> edges(n-1, vector<int> (2));
	for(int i=0;i<n-1;i++)
	cin >> edges[i][0] >> edges[i][1];

	cout << getMaxValueSum(n,val,edges) << endl;;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////