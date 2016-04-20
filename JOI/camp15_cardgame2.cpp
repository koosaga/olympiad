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
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int dp[505][505][505];
bool vis[505][505][505];
int n, c[505], a[505], v[505];
 
bool can(int q, int p){
    if(q > n) return 0;
    if(p == 0) return 1;
    return a[q] == a[p] || c[q] == c[p];
}
 
lint f(int s1, int s2, int pop, int peak){
    if(s2 + 1 == pop && vis[s1][s2][peak]) return dp[s1][s2][peak];
    else if(peak + 1 == pop && vis[s2][s1][peak]) return dp[s2][s1][peak];
    lint ret = 0;
    if(can(s1, peak)) ret = max(ret, v[s1] + f(s2, pop, pop+1, s1));
    if(can(pop, peak)) ret = max(ret, v[pop] + f(s1, s2, pop+1, pop));
    if(s2 + 1 == pop) dp[s1][s2][peak] = ret, vis[s1][s2][peak] = 1;
    if(peak + 1 == pop) dp[s2][s1][peak] = ret, vis[s2][s1][peak] = 1;
    return ret;
}
 
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d %d %d",&c[i],&a[i],&v[i]);
    }
    printf("%lld\n",f(1, 2, 3, 0));
}