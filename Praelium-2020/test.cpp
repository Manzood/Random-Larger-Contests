#include <iostream>
#include<bits/stdc++.h>
#include<vector>
#include<set>
#include<math.h>
#include<string.h>
#include<cstdlib>
#include<sstream>

typedef long long ll;

using namespace std;


ll search(ll a)
{
    ll level = 1, curmax = 1, nodes = 1;

    while(curmax < a)
    {
        if(level%2!=0)
        {
            curmax = curmax + nodes*2;
            nodes = nodes*2;
            level++;    
        }

        else
        {
            curmax = curmax + nodes*3;
            nodes = nodes*3;
            level++;
        }
    }
    return(level);    
}

int main()
{
    int t;

    cin >> t;

    while(t--)
    {
        ll a, b,first,second,level1,level2;

        cin >> a >> b;

        level1= search(a);
        level2 = search(b);
        first = level1 - 1;
        second = level2 - 1;    
    
        if((abs(a-b) <= 2) && (level1 == level2))
        {
            cout << min(first,second)+ 2 << "\n";
        }
        
        else
        {
            cout << min(2*first+second, first + 2*second) << "\n";
        }
            
    }
}