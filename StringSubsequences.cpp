#include <vector>
#include <string>
using namespace std;

void solve(string str, int idx, string output, vector<string>& ans){
	if (idx==str.length()) {
		if(output.length()!=0) ans.push_back(output);
		return;
	}

	//exclude
	solve(str,idx+1,output,ans);
	//include
	output = output+str[idx];
	solve(str,idx+1,output,ans);

	return;
}

vector<string> subsequences(string str){
	
	vector<string> ans;
	string output;
	solve(str,0,output,ans);
	return ans;
	
}

int main(){
    subsequences("abcdde");
    return 0;
}