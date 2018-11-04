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

int n, a[1005];
int dp[1005][1005];

int f2(int s, int e);

int f1(int s, int e){
    if(s > e) return 0;
    if(~dp[e][s]) return dp[e][s];
    return dp[e][s] = max(f2(s+1, e) + a[s], f2(s, e-1) + a[e]);
}

int f2(int s, int e){
    if(s > e) return 0;
    if(~dp[s][e]) return dp[s][e];
    return dp[s][e] = min(f1(s+1, e), f1(s, e-1));
}

int main(){
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        for(int i=0; i<n; i++){
            scanf("%d",&a[i]);
        }
        memset(dp,-1,sizeof(dp));
        printf("%d\n",f1(0,n-1));
    }
}
