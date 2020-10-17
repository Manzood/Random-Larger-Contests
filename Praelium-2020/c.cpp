#include "bits/stdc++.h"
using namespace std;
#define debug(x) cout<<#x<<" = "<<x<<endl;
#define int long long
const int mod = 1000000007;

int32_t main() {
    int n;
    scanf("%lld", &n);
    vector <int> a(n);
    vector <long long> ans(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0) ans[i] = 0;
        else {
            ans[i] += (long long)(sum * a[i]);
            ans[i] += ans[i-1];
        }
        sum += a[i];
        ans[i] %= mod;
    }
    printf("%lld\n", ans[n-1]);
}