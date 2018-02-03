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

const int mod = 9999991;
int dp[22][22];

int n, a[22];
lint f(int s, int e, int p){
    if(p == n) return 1;
    if(s <= a[p] && a[p] <= e){
        return (f(s, a[p]-1, p+1) * f(a[p]+1, e, p+1) % mod) * dp[e-s][a[p]-s] % mod;
    }
    else return f(s, e, p+1);
}
int main(){
    for(int i=0; i<=20; i++){
        dp[i][0] = 1;
        for(int j=1; j<=i; j++){
            dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
            dp[i][j] %= mod;
        }
    }
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0; i<n; i++){
            scanf("%d",&a[i]);
        }
        printf("%lld\n",f(1, n, 0));
    }
}