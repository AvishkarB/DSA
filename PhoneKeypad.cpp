#include <string>
#include <vector>
using namespace std;

class Solution {
private:
    void solve(string digits, int idx, string output, vector<string>& ans, string map[]){
        if(idx==digits.length()){
            ans.push_back(output);
            return;
        }

        string value = map[digits[idx]-'0'];
        for(int i=0;i<value.length();i++){
            output = output+value[i];
            solve(digits,idx+1,output,ans,map);
            output.pop_back();
        }
        return;
    }

public:
    vector<string> letterCombinations(string digits) {
        vector<string> ans;
        if(digits.length()==0) return ans;
        string output;
        string map[10] = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        solve(digits,0,output,ans,map);
        return ans;
    }
};