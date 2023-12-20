#include <iostream>
#include <vector>
using namespace std;

void solve(vector<int>& nums, int idx, vector<int> output, vector<vector<int>>& ans){
        
        if(idx==nums.size()){
            ans.push_back(output);
            return;
        }

        //exclude
        solve(nums, idx+1, output, ans);

        //include
        output.push_back(nums[idx]);
        solve(nums, idx+1, output, ans);

        return;
    }

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> ans;
    vector<int> output;
    solve(nums, 0, output, ans);
    return ans;
}

int main(){

	vector<int> arr = {1,2,3,4,5};
	vector<vector<int>> ans = subsets(arr);

	for(int i=0;i<ans.size();i++) {
		cout << "[";
		for(int k=0;k<ans[i].size();k++) cout << ans[i][k];
		cout << "] ";
	}
	
	return 0;
}