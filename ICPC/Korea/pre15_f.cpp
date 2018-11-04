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

int a[505], n;
int dp[505][505];

int f(int s, int e){
    if(s == e) return 0;
    if(~dp[s][e]) return dp[s][e];
    int ret = 1e9;
    for(int i=s; i<e; i++){
        ret = min(ret, f(s, i) + f(i+1, e) + a[e] - a[s-1]);
    }
    return dp[s][e] = ret;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
    memset(dp,-1,sizeof(dp));
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        a[i] += a[i-1];
    }
    printf("%d\n",f(1, n));
}
}