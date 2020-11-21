#include<algorithm>
#include<cstdio>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
using namespace std;
#define debug(x) cout<<#x<<" = "<<x<<endl;

int checkdiff (string &a, string &b) {
    int len = a.size();
    int retval = 0;
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) retval++;
        if (retval > 1) return retval;
    }
    return retval;
}

int checkless (string &a, string &b) {
    int retval = 0;
    int skip = 0;
    if ((int)a.size() > (int)b.size()) {
        int len = a.size();
        for (int i = 0; i < len; i++) {
            if (a[i+skip] != b[i]) {
                if (!skip) skip++;
                retval++;
            }
            if (retval > 1) return retval;
        }
    } else {
        int len = b.size();
        for (int i = 0; i < len; i++) {
            if (b[i+skip] != a[i]) {
                if (!skip) skip++;
                retval++;
            }
            if (retval > 1) return retval;
        }
    }
    return retval;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    vector <vector <string> > customers;
    string s;
    vector <string> temp;
    while (getline(cin, s)) {
        if (s == "--") {
            if ((int)temp.size() == 3) customers.push_back(temp);
            temp.resize(0);
        } else {
            string s2;
            char prev = 'a';
            for (auto cur : s) {
                if (prev == ' ' && cur == ' ');
                else s2 += cur;
                prev = cur;
            }
            temp.push_back(s2);
        }
    }
    if ((int)temp.size() == 3) customers.push_back(temp);
    int n = customers.size();
    int duplicates = 0;
    vector <bool> counted (n, false);
    for (int i = 0; i < n; i++) {
        bool found_duplicate = false;
        for (int j = i+1; j < n; j++) {
            int checktotal = 0;
            bool is_duplicate = true;
            for (int k = 0; k < 3 && is_duplicate; k++) {
                int check = 0;
                if ((int)customers[i][k].size() == (int)customers[j][k].size()) {
                    check = checkdiff(customers[i][k], customers[j][k]);

                    int len = customers[i][k].size();
                    for (int tempi = 0; tempi < len; tempi++) {
                        if (customers[i][k][tempi] != customers[j][k][tempi]) check++;
                        if (check > 1) break;
                    }

                    if (check > 1) is_duplicate = false;
                    else {
                        checktotal += check;
                    }
                    if (checktotal > 2) is_duplicate = false;
                } else {
                    if (abs((int)customers[i][k].size() - (int)customers[j][k].size()) == 1) {
                        // check = checkless(customers[i][k], customers[j][k]);

                        int skip = 0;
                        if ((int)customers[i][k].size() > (int)customers[j][k].size()) {
                            int len = customers[i][k].size();
                            for (int tempi = 0; tempi < len; tempi++) {
                                if (customers[i][k][tempi+skip] != customers[j][k][tempi]) {
                                    if (!skip) skip++;
                                    check++;
                                }
                                if (check > 1) break;
                            }
                        } else {
                            int len = customers[j][k].size();
                            for (int tempi = 0; tempi < len; tempi++) {
                                if (customers[j][k][tempi+skip] != customers[i][k][tempi]) {
                                    if (!skip) skip++;
                                    check++;
                                }
                                if (check > 1) break;
                            }
                        }

                        if (check > 1) is_duplicate = false;
                        else checktotal += check;
                        if (checktotal > 2) is_duplicate = false;
                    } else {
                        is_duplicate = false;
                    }
                }
            }
            if (is_duplicate && !counted[j]) {
                duplicates++;
                found_duplicate = true;
                counted[j] = true;
            }
        }
        if (found_duplicate && !counted[i]) {
            duplicates++;
            counted[i] = true;
        }
    }
    printf("%d\n", duplicates);
}