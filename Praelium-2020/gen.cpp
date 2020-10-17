#include "bits/stdc++.h"
using namespace std;
#define debug(x) cout<<#x<<" = "<<x<<endl;

int rand (int a, int b) {
    return (rand() % (b-a+1)) + a;
}

int main(int argc, char *argv[]) {
    srand(atoi(argv[1]));
    int t;
    t = rand(1, 1);
    printf("%d\n", t);
    while (t--) {
        int n = rand(1, 99);
        printf("%d\n", n);
    }
}
