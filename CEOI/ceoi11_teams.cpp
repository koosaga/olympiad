#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n;
pi a[1000005];
int dp[1000005], ok[1000005], pref[1000005], opt[1000005], par[1000005];

int getans(int x){
    memset(ok, 0, sizeof(ok));
    ok[0] = 1;
    for(int i=1; i<=n; i++){
        if(i - a[i].first < 0){
            dp[i] = -1e9;
        }
        else{
            dp[i] = pref[i - a[i].first] + 1;
            if(opt[i - a[i].first] >= i - x) ok[i] = 1, par[i] = opt[i - a[i].first];
        }
        pref[i] = pref[i-1];
        opt[i] = opt[i-1];
        if(ok[i] && pref[i] <= dp[i]){
            opt[i] = i;
            pref[i] = dp[i];
        }
    }
    return ok[n];
}

void track(int x){
    if(x == 0) return;
    int p = par[x];
    track(p);
    printf("%d ",x - p);
    for(int j=p+1; j<=x; j++){
        printf("%d ",a[j].second);
    }
    puts("");
}

int main(){
    cin >> n;
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i].first);
        a[i].second = i;
    }
    sort(a+1, a+n+1);
    int s = 1, e = n;
    while(s != e){
        int m = (s+e)/2;
        if(getans(m)) e = m;
        else s = m+1;
    }
    getans(s);
    printf("%d\n",dp[n]);
    track(n);
}