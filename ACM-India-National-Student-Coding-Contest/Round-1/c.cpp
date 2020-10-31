#include<algorithm>
#include<cstdio>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
using namespace std;
#define debug(x) cout<<#x<<" = "<<x<<endl;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string s;
    string ceo = "";
    map <string, string> findmanager;
    map <string, int> level;
    map <string, int> lowest;
    map <string, string> ans;
    while (getline(cin, s)) {
        int pos = s.find(',');
        string name = s.substr(0, pos);
        s = s.substr(pos+2);
        s = s.substr(s.find(',') + 2);
        if (s == "NOBODY") {
            ceo = name;
            level[name] = 0;
            findmanager[name] = name;
            lowest[name] = 0;
        } else {
            findmanager[name] = findmanager[s];
            string current = findmanager[name];
            level[name] = level[s] + 1;
            if (level[name] > lowest[current]) {
                lowest[current] = level[name];
                ans[current] = name;
            }
        }
    }
    for (auto x: ans) {
        cout << x.first << ": " << x.second << "\n";
    }
}