#include "bits/stdc++.h"
using namespace std;
#define int long long
const int mod = 1000000007;

vector<string> vec_splitter(string s) {
    s += ','; vector<string> res;
    while(!s.empty()) {
        res.push_back(s.substr(0, s.find(',')));
        s = s.substr(s.find(',') + 1);
    }
    return res;
}

void debug_out( vector<string> __attribute__ ((unused)) args, __attribute__ ((unused)) int idx, __attribute__ ((unused)) int LINE_NUM) { cerr << endl; } 
template <typename Head, typename... Tail>

void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
    if(idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
    stringstream ss; ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, LINE_NUM, T...);
}

#ifdef local 
    #define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else 
    #define debug(...) 42
#endif


int32_t main() {
    int t = 1;
    cin >> t;
    int N = 1e5+7;
    vector <int> ans(N+1);
    ans[0] = 0; ans[1] = 1; ans[2] = 2;
    for (int i = 3; i <= N; i++) {
        ans[i] = 1;
        if (i % 2 == 0) {
            ans[i] *= ans[i-1];
            ans[i] *= i;
        }
        else {
            ans[i] *= ans[i-1]/2;
            ans[i] *= i/2 + 1;
        }
        ans[i] %= mod;
        if (i < 18) {
            debug(i, ans[i]);
        }
    }
    while (t--) {
        int n;
        scanf("%lld", &n);
        printf("%lld\n", ans[n]);
    }
}