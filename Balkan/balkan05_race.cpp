#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<lint,lint> pi;
 
int n;
lint dist[705], w[1005], dp[1005][1005][2];
  
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
 
int main(){
    memset(dp,-1,sizeof(dp));
    int s = 0;
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%lld",&dist[i]);
    }
    sort(dist+1, dist+n+2);
    n++;
    s = lower_bound(dist + 1, dist + n + 1, s) - dist;
    printf("%lld",f(s,s,0));
}