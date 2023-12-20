int main(){
    for(int i=1,i<input1;i++){
        int include = abs(input[i]-input[i-1]);
        int exclude = abs(input[i]-input[i-3]);

        arr[i] = min(include,exclude);
    }
}