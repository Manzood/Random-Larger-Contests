#include<algorithm>
#include<cstdio>
#include<iostream>
#include<vector>
#include<set>
#include<string>
using namespace std;
#define debug(x) cout<<#x<<" = "<<x<<endl;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string s;
    long long sum = 0;
    while (getline(cin, s)) {
        int i = 0;
        while (s[i++] != ',');
        i++;
        long long num = 0;
        while (s[i] != ',') {
            num += s[i] - '0';
            num *= 10;
            i++;
        }
        num /= 10;
        sum += num;
    }
    printf("%lld\n", sum);
}