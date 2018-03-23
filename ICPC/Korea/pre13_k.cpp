#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long lint;

int n;
lint dist[105], dp[105][105][2];

lint f(int s, int e, int route){
    if(s == 1 && e == n) return 0;
    if(s == 0 || e == n+1) return 1e18;
    if(~dp[s][e][route]) return dp[s][e][route];
    if(route == 1){
        lint ret1 = (dist[e+1] - dist[e]) * (n - e + s - 1) + f(s,e+1,1);
        lint ret2 = (dist[e] - dist[s-1]) * (n - e + s - 1) + f(s-1,e,0);
        return dp[s][e][route] = min(ret1,ret2);
    }
    else{
        lint ret1 = (dist[s] - dist[s-1]) * (n - e + s - 1) + f(s-1,e,0);
        lint ret2 = (dist[e+1] - dist[s]) * (n - e + s - 1) + f(s,e+1,1);
        return dp[s][e][route] = min(ret1,ret2);
    }
}

void solve(){
    memset(dp,-1,sizeof(dp));
    int s;
    scanf("%d %d",&n,&s);
    for (int i=2; i<=n; i++) {
        scanf("%lld",&dist[i]);
        dist[i] += dist[i-1];
    }
    printf("%lld\n",f(s,s,0));
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        solve();
    }
}