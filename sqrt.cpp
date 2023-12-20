#include <iostream>
#include <cmath>

using namespace std;

double squareRoot(double n){
    double e = 0.01;

    if(n>=1) {
        double left = 1, right = n;
        while(true){
            double mid = (left + right)/2;
            if(abs(mid*mid-n)<=e) return mid;
            else if(mid*mid>n) right = mid;
            else left = mid;
        }
    }
    else {
        double left = n, right = 1;
        while(true){
            double mid = (left + right)/2;
            if(abs(mid*mid-n)<=e) return mid;
            else if(mid*mid>n) right = mid;
            else left = mid;
        }
    }
}

int main(){
    double n = 10000000000000;
    double sqrt = squareRoot(n);
    cout << sqrt;
    return 0;
}