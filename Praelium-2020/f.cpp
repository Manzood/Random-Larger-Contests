#include "bits/stdc++.h"
using namespace std;
#define debug(x) cout<<#x<<" = "<<x<<endl;
#define int long long

int32_t main() {
    int t = 1;
    cin >> t;
    while (t--) {
        int n, m, x;
        scanf("%lld%lld%lld", &n, &m, &x);
        vector <int> a(n);
        vector <int> b(n, 0);
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (i > 0) b[i] = b[i-1] + b[i];
            if (b[i] + a[i] < x) {
                int temp = x - a[i] - b[i];
                ans += temp;
                b[i] += temp;
                if (i + m < n) b[i+m] -= temp;
            }
        }
        printf("%lld\n", ans);
    }
}