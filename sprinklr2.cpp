#include <cstring>

void solve(obj* O, vector<vector<string>>& data){
    for(auto it:O){
        data[O.first].push_back(O.second);
    }
}

void print(vector<string>& label, vector<vector<string>>& data){
    for(int i=0;i<label.size()){
        cout << label[i] << ":";
        for(int j=0;j<data[i].size();j++){
            cout << data[i][j] << ",";
        }
        cout << endl;
    }
}

void blackbox(vector<obj*> variable1){
    int n = variable1.size();
    int m = variable1[0].size();
    vector<string> label(n);
    vector<vector<string>> data(n, vector<string> (m,""));

    for(auto it:variable1[0]){
        for(int i=0;i<variable1[0].size();i++){
            label[i] = variable[0][i];
        }
    }

    for(auto it:variable1){
        solve(it,data);
    }

    print(label,data);
}