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
const int mod = 1e6;
 
int n, a[1005];
int dp[1005][1005][2];
 
int f(int s, int e, int p){
    if(s == 0 && e == n-1) return 0;
    if(~dp[s][e][p]) return dp[s][e][p];
    int ret = 1e9;
    if(p == 0){
        if(s) ret = min(ret, f(s-1, e, 0) + (a[s] - a[s-1]) * (n - 1 - e + s));
        if(e+1 != n) ret = min(ret, f(s, e+1, 1) + (a[e+1] - a[s]) * (n - 1 - e + s));
    }
    if(p == 1){
        if(s) ret = min(ret, f(s-1, e, 0) + (a[e] - a[s-1]) * (n - 1 - e + s));
        if(e+1 != n) ret = min(ret, f(s, e+1, 1) + (a[e+1] - a[e]) * (n - 1 - e + s));
    }
    return dp[s][e][p] = ret;
}
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    n++;
    sort(a,a+n);
    int p = 0;
    for(int i=0; i<n; i++){
        if(a[i] == 0) p = i;
    }
    memset(dp,-1,sizeof(dp));
    printf("%d",f(p, p, 0));
}