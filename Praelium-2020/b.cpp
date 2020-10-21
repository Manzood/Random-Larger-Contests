#include "bits/stdc++.h"
using namespace std;
#define int long long
const int mod = 1000000007;
#define debug(x) cout << #x << " = " << x << endl;

int32_t main() {
    int t = 1;
    cin >> t;
    int N = 1e5+7;
    vector <int> ans(N+1);
    ans[0] = 0; ans[1] = 1; ans[2] = 2;
    for (int i = 3; i <= N; i++) {
        ans[i] = 1;
        if (i % 2 == 0) {
            ans[i] = ((ans[i]) * (ans[i-1]));
            ans[i] = ((ans[i]) * (i));
        }
        else {
            ans[i] = ((ans[i]) * ((ans[i-1]/2)));
            ans[i] = ((ans[i]) * ((i/2 + 1)));
        }
        ans[i] %= mod;
    }
    while (t--) {
        int n;
        scanf("%lld", &n);
        printf("%lld\n", ans[n]);
    }
}