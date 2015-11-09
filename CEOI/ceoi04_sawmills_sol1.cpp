#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int cnt[20005], dist[20005], sum[20005];
int dp[3][20005];

struct cht{
    int la[20005], lb[20005], sz, p;
    void init(){ sz = p = 0; }
    double cross(int i, int j){
        return 1.0 * (lb[j] - lb[i]) / (la[i] - la[j]);
    }
    void insert(int p, int q){
        la[sz] = p;
        lb[sz] = q;
        while(sz - 2 >= p && cross(sz,sz-1) < cross(sz-1,sz-2)){
            la[sz-1] = la[sz];
            lb[sz-1] = lb[sz];
            sz--;
        }
        sz++;
    }
    int query(int x){
        if(sz == p) return 2e9;
        while(p + 1 < sz && cross(p,p+1) < x) p++;
        return la[p] * x + lb[p];
    }
}cht;

int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&cnt[i],&dist[i+1]);
        dist[i+1] += dist[i];
        sum[i] = sum[i-1] + dist[i] * cnt[i];
        cnt[i] += cnt[i-1];
        dp[0][i] = dist[i] * cnt[i] - sum[i];
    }
    sum[n+1] = sum[n];
    cnt[n+1] = cnt[n];
    for (int i=1; i<3; i++) {
        cht.init();
        for (int j=0; j<=n+1; j++) {
            dp[i][j] = cht.query(dist[j]);
            cht.insert(-cnt[j],dp[i-1][j] + sum[j]);
            dp[i][j] += dist[j] * cnt[j] - sum[j];
        }
    }
    printf("%d",dp[2][n+1]);
}