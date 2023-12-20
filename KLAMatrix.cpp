#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main(){
    int n=5;

    vector<vector<int>> arr(n, vector<int> (n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> arr[i][j];
        }
    }

    int ch;
    cin >> ch;

    if(ch==1){
        int count = 0;
        for(int row=0;row<n;row++){
            for(int col=0;col<n;col++){
                if(arr[row][col]==1){
                    count++;
                    while(col<n && arr[row][col]==1){
                        arr[row][col++] = -1;
                    }
                }
            }
        }
        cout << count << endl;
    }

    else if(ch==2){
        int count = 0;
        for(int col=0;col<n;col++){
            for(int row=0;row<n;row++){
                if(arr[row][col]==1){
                    count++;
                    while(row<n && arr[row][col]==1){
                        arr[row++][col] = -1;
                    }
                }
            }
        }
        cout << count << endl;
    }

    else if(ch==3){
        int count = 0;
        stack<pair<int,int>> q;
        for(int row=0;row<n;row++){
            for(int col=0;col<n;col++){
                if(arr[row][col]==1){
                    count++;
                    q.push({row,col});
                    
                    while(!q.empty()){
                        int row = q.top().first;
                        int col = q.top().second;
                        q.pop();

                        arr[row][col] = -1;
                        if(row+1<n && col+1<n && arr[row+1][col+1]==1) q.push({row+1,col+1});
                        if(row+1<n && col-1>=0 &&  arr[row+1][col-1]==1) q.push({row+1,col-1});
                        if(row-1>=0 && col+1<n &&  arr[row-1][col+1]==1) q.push({row-1,col+1});
                        if(row-1>=0 && col-1>=0 &&  arr[row-1][col-1]==1) q.push({row-1,col-1});
                    }
                }
            }
        }
        cout << count << endl;
    }

    else if(ch==4){
        int count = 0;
        stack<pair<int,int>> q;
        for(int row=0;row<n;row++){
            for(int col=0;col<n;col++){
                if(arr[row][col]==1){
                    count++;
                    q.push({row,col});
                    
                    while(!q.empty()){
                        int row = q.top().first;
                        int col = q.top().second;
                        arr[row][col] = -1;
                        q.pop();
                        
                        if(col+1<n && arr[row][col+1]==1) q.push({row,col+1});
                        if(row+1<n && arr[row+1][col]==1) q.push({row+1,col});
						if(col-1>=0 && arr[row][col-1]==1) q.push({row,col-1});
                        if(row-1>=0 && arr[row-1][col]==1) q.push({row-1,col});
                    }
                }
            }
        }
        cout << count << endl;
    }

    else {
        int count = 0;
        stack<pair<int,int>> q;
        for(int row=0;row<n;row++){
            for(int col=0;col<n;col++){
                if(arr[row][col]==1){
                    count++;
                    q.push({row,col});
                    
                    while(!q.empty()){
                        int row = q.top().first;
                        int col = q.top().second;
                        q.pop();

                        arr[row][col] = -1;
                        if(row+1<n && col+1<n && arr[row+1][col+1]==1) q.push({row+1,col+1});
                        if(row+1<n && col-1>=0 &&  arr[row+1][col-1]==1) q.push({row+1,col-1});
                        if(row-1>=0 && col+1<n &&  arr[row-1][col+1]==1) q.push({row-1,col+1});
                        if(row-1>=0 && col-1>=0 &&  arr[row-1][col-1]==1) q.push({row-1,col-1});
                        if(col+1<n && arr[row][col+1]==1) q.push({row,col+1});
                        if(row+1<n && arr[row+1][col]==1) q.push({row+1,col});
                    }
                }
            }
        }
        cout << count << endl;
    }
}