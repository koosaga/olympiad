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

lint dp[20005];
int a[20005];
int n, m, k;

int main(){
    scanf("%d %d %d",&n,&m,&k);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
    }
    for(int i=1; i<=n; i++){
        dp[i] = 1e18;
        int pmax = -1e9, pmin = 1e9;
        for(int j=i; j>max(0, i-m); j--){
            pmax = max(pmax, a[j]);
            pmin = min(pmin, a[j]);
            dp[i] = min(dp[i], dp[j-1] + 1ll * (pmax - pmin) * (i - j+ 1) + k);
        }
    }
    printf("%lld",dp[n]);
}