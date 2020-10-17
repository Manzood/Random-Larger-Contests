#include "bits/stdc++.h"
using namespace std;
#define debug(x) cout<<#x<<" = "<<x<<endl;
#define int long long

int32_t main() {
    int t = 1;
    cin >> t;
    while (t--) {
        int a, b;
        scanf("%lld%lld", &a, &b);
        if (a > b) swap(a, b);
        // first, find the path
        // then find the common parent
        // then find the actual distance
        int curr = 1;
        int num = 1;
        int count = 0;
        int dist = 0;
        vector <int> first_path;
        while (curr <= a) {
            dist = a - curr;
            count++;
            first_path.push_back(curr);
            curr += num;
            if (count % 2 == 1) 
                num *= 2;
            else 
                num *= 3;
        }
        vector <int> path_a;
        set <int> a_set;
        while (count > 0) {
            count--;
            path_a.push_back(first_path[count] + dist);
            a_set.insert(first_path[count] + dist);
            if (count % 2 == 1) {
                dist /= 2;
            }
            else {
                dist /= 3;
            }
        }

        // this is for b

        curr = 1;
        num = 1;
        count = 0;
        dist = 0;
        first_path.resize(0);
        while (curr <= b) {
            dist = b - curr;
            count++;
            first_path.push_back(curr);
            curr += num;
            if (count % 2 == 1) 
                num *= 2;
            else 
                num *= 3;
        }
        // now, to find the path
        vector <int> path_b;
        while (count > 0) {
            count--;
            path_b.push_back(first_path[count] + dist);
            if (count % 2 == 1) {
                dist /= 2;
            }
            else {
                dist /= 3;
            }
        }
        int val = 0;
        for (int i = 0; i <= (int)path_b.size()-1; i++) {
            if (a_set.count(path_b[i])) {
                val = path_b[i];
                break;
            }
        }
        int ans = 0;
        ans += (int)path_a.size()-1;
        bool found = false;
        for (int i = 0; i < (int)path_a.size(); i++) {
            // while it isn't found, keep looking
            if (path_a[i] == val) break;
            else {
                ans++;
            }
        }
        found = false;
        for (int i = (int)path_b.size() - 1; i >= 0; i--) {
            if (found) ans++;
            else {
                if (path_b[i] == val) {
                    found = true;
                }
            }
        }
        printf("%lld\n", ans);
        // for (int i = 0; i < (int)path_a.size(); i++) {
            // debug(path_a[i]);
        // }
        // for (int i = 0; i < (int)path_b.size(); i++) {
            // debug(path_b[i]);
        // }
    }
}