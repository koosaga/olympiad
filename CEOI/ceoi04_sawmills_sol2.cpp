#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int cnt[20005], dist[20005], cum[20005];
long long dp[3][20005];

inline long long cost(int i, int j){
    return (1ll * dist[j] * cnt[j] - cum[j]) + cum[i] - (1ll * dist[j] * cnt[i]);
}

void solve(long long *p, long long *q, int s, int e, int ps, int pe){
    if(s > e) return;
    int m = (s+e)/2;
    q[m] = 1e10;
    int opt = -1;
    for (int i=ps; i<=pe && i < m; i++){
        if(q[m] > p[i] + cost(i,m)){
            opt = i;
            q[m] = p[i] + cost(i,m);
        }
    }
    solve(p,q,s,m-1,ps,opt);
    solve(p,q,m+1,e,opt,pe);
}

int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&cnt[i],&dist[i+1]);
        dist[i+1] += dist[i];
        cum[i] = cum[i-1] + dist[i] * cnt[i];
        cnt[i] += cnt[i-1];
        dp[0][i] = cost(0,i);
    }
    cum[n+1] = cum[n];
    cnt[n+1] = cnt[n];
    for (int i=1; i<3; i++) {
        solve(dp[i-1],dp[i],0,n+1,0,n+1);
    }
    printf("%lld",dp[2][n+1]);
}