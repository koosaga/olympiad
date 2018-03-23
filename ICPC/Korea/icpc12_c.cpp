#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m, adj[105][105];
int dp[105][105][105];
int s1, s2, s3, t1, t2, t3;

int f(int a, int b, int c){
    if(a == s2 || a == s3 || b == s1 || b == s3 || c == s1 || c == s2) return -1e9;
    if(a > t1 || b > t2 || c > t3) return -1e9;
    if(a == t1 && b == t2 && c == t3) return 0;
    if(~dp[a][b][c]) return dp[a][b][c];
    int maxp = max(a,max(b,c)) + 1;
    int ret = -1e9;
    for(int i=maxp; i<=n; i++){
        if(adj[a][i] >= 0){
            ret = max(ret,adj[a][i] + f(i,b,c));
        }
        if(adj[b][i] >= 0){
            ret = max(ret,adj[b][i] + f(a,i,c));
        }
        if(adj[c][i] >= 0){
            ret = max(ret,adj[c][i] + f(a,b,i));
        }
    }
    return dp[a][b][c] = ret;
}

void solve(){
    scanf("%d %d",&n,&m);
    scanf("%d %d %d %d %d %d",&s1,&s2,&s3,&t1,&t2,&t3);
    memset(dp,-1,sizeof(dp));
    memset(adj,-1,sizeof(adj));
    adj[0][s1] = adj[0][s2] = adj[0][s3] = 0;
    for(int i=0; i<m; i++){
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        adj[s][e] = max(adj[s][e],x);
    }
    int ret = max(0,f(0,0,0));
    printf("%d\n", ret);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
}