#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1000000007;

int main(){
    int t,n,m;
    long long out;
    cin >> t;
    for(int i=0;i<t;i++){
        cin >> n;    
        out=1;
        m=n/2;
        for(int i=2;i<=m;i++){
            out = (out*i)%N;
        }
        if (n%2==0)
            out = 2*(((out * out)%N))%N;
        else
            out = (((out * out)%N) * (m+1))%N;
        cout << out << endl;
    }
}