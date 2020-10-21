#include "bits/stdc++.h"
using namespace std;
#define int long long
const int mod = 1000000007;
#define debug(x) cout << #x << " = " << x << endl;

// I am currently unable to figure out for the life of me why the commented part does not work, but the uncommented code works.
// it is a complete mystery to me at the moment, because they should be completely identical. I haven't messed with the modulo operation one bit

int32_t main() {
    int t = 1;
    cin >> t;
    int N = 1e5+7;
    vector <int> ans(N+1);
    ans[0] = 0; ans[1] = 1; ans[2] = 2;
    for (int i = 3; i <= N; i++) {
        ans[i] = 1;
        if (i % 2 == 0) {
            // ans[i] *= ans[i-1];
            // ans[i] *= i;
            ans[i] *= i/2 * i/2;
            ans[i] *= ans[i-2];
        }
        else {
            // ans[i] *= ans[i-1]/2;
            // ans[i] *= (i/2 + 1);
            ans[i] *= i/2 * (i/2+1);
            ans[i] *= ans[i-2];
        }
        // if (i < 18) debug(ans[i]);
        ans[i] %= mod;
    }
    while (t--) {
        int n;
        scanf("%lld", &n);
        printf("%lld\n", ans[n]);
    }
}