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
    set <string> companies;
    vector <string> storage;
    map <string, long long> minsalary;
    while (getline(cin, s)) {
        int pos = s.find(',');
        pos+=2;
        s = s.substr(pos);
        long long num = 0;
        int i = 0;
        while (s[i] != ',') {
            num += s[i] - '0';
            num *= 10;
            i++;
        }
        num /= 10;
        i++;
        s = s.substr(i);
        string company = s.substr(0, s.find(','));
        if (companies.count(company)) {
            minsalary[company] = min(minsalary[company], num);
        } else {
            minsalary[company] = num;
            companies.insert(company);
            storage.push_back(company);
        }
    }
    for (auto x: storage) {
        cout << x << " " << minsalary[x] << '\n';
    }
}