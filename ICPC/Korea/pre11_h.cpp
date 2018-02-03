#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int c, d, e; // d + ex

int a[105], sa, b[105], sb;
int dp[105][105][2][2];

int f(int x, int y, int h1, int h2){
    if(x == 0 && y == 0) return 0;
    if(~dp[x][y][h1][h2]) return dp[x][y][h1][h2];
    int ret = 123556;
    if(x && y && a[x] == b[y]) ret = min(ret, f(x-1, y-1, 1, 1) + c);
    if(x && y && a[x] != b[y]) ret = min(ret, f(x-1, y-1, 1, 1) + 2 * c);
    if(h1) for(int i=0; i<x; i++){
        ret = min(ret, f(i, y, 0, 1) + (c + e) * (x - i) + d);
    }
    if(h2) for(int i=0; i<y; i++){
        ret = min(ret, f(x, i, 1, 0) + (c + e) * (y - i) + d);
    }
    return dp[x][y][h1][h2] = ret;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        sa = 0, sb = 0;
        cin >> c >> d >> e;
        while(1){
            cin >> a[++sa];
            if(a[sa] == 0){
                sa--;
                break;
            }
        }
        while(1){
            cin >> b[++sb];
            if(b[sb] == 0){
                sb--;
                break;
            }
        }
        memset(dp, -1, sizeof(dp));
        cout << f(sa, sb, 1, 1) << endl;
    }
}