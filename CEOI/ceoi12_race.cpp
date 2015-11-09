#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int adj[505][505],n,k;
int dp[505][505][2];
int dp2[505][505][2];

inline int M(int x){
    if(x > n) return x - n;
    else if(x <= 0) return x + n;
    return x;
}

inline int I(int x){
    return x == n ? 1 : (x+1);
}

inline int D(int x){
    return x == 1 ? n : (x-1);
}

int f(int s, int e, int lview){
    if(~dp[s][e][lview]) return dp[s][e][lview];
    int ret = 0;
    if(lview){
        for (int i=M(e+1); i != s; i = I(i)) {
            if(adj[e][i]){
                int ret1 = f(e,i,0);
                int ret2 = f(s,i,1);
                ret = max(ret,max(ret1,ret2)+1);
            }
        }
    }
    else if(!lview){
        for (int i=M(s+1); i != e; i = I(i)) {
            if(adj[e][i]){
                int ret1 = f(e,i,1);
                int ret2 = f(s,i,0);
                ret = max(ret,max(ret1,ret2)+1);
            }
        }
    }
    return dp[s][e][lview] = ret;
}

int f2(int s, int e, int lview){
    if(s == e) return 0;
    if(~dp2[s][e][lview]) return dp2[s][e][lview];
    int ret = adj[s][e] ? 0 : -1e9;
    if(lview){
        for (int i=M(e+1); i != s; i = I(i)) {
            if(adj[s][i]) ret = max(ret,f2(i,e,1));
        }
    }
    else{
        for (int i=M(s+1); i != e; i = I(i)) {
            if(adj[s][i]) ret = max(ret,f2(i,e,0));
        }
    }
    return dp2[s][e][lview] = ret + 1;
}

int opt[505];
int adj_max1[505][505];
int adj_max2[505][505];

void set_table(int i){
    memset(adj_max1,0,sizeof(adj_max1));
    memset(adj_max2,0,sizeof(adj_max2));
    for (int j=M(i+1); j != i; j = I(j)) {
        for (int k=M(j+2); k != i; k = I(k)) {
            adj_max1[j][k] = max((adj[i][D(k)] ? (1 + f(j,D(k),0)) : 0),adj_max1[j][D(k)]);
        }
    }
    for (int k=M(i-1); k != i; k = D(k)) {
        for (int j=M(k-2); j != i; j = D(j)) {
            adj_max2[j][k] = max((adj[i][I(j)] ? (1 + f(k,I(j),1)) : 0), adj_max2[I(j)][k]);
        }
    }
}

void solve(){
    for (int j=1; j<=n; j++) {
        set_table(j);
        for (int x=M(j+1); x != M(j-2); x = I(x)) {
            for (int i=M(x+2); i != j; i = I(i)) {
                if(!adj[x][i]) continue;
                opt[x] = max(opt[x],1 + f2(i,j,0) + adj_max1[x][i]);
                opt[x] = max(opt[x],1 + f2(i,j,0) + adj_max2[x][i]);
            }
        }
        for (int i=M(j+1); i != M(j-2); i = I(i)) {
            for (int x=M(i+2); x != j; x = I(x)) {
                if(!adj[x][i]) continue;
                opt[x] = max(opt[x],1 + f2(i,j,1) + adj_max1[i][x]);
                opt[x] = max(opt[x],1 + f2(i,j,1) + adj_max2[i][x]);
            }
        }
    }
}

int main(){
    memset(dp,-1,sizeof(dp));
    memset(dp2,-1,sizeof(dp2));
    scanf("%d %d",&n,&k);
    for (int i=1; i<=n; i++) {
        int t;
        while(1){
            scanf("%d",&t);
            if(t == 0) break;
            else adj[i][t] = 1;
        }
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            if(!adj[i][j]) continue;
            for (int k=0; k<2; k++) {
                opt[i] = max(opt[i],f(i,j,k) + 1);
            }
        }
    }
    if(k == 1){
        solve();
    }
    int p = (int)(max_element(opt+1,opt+n+1) - opt);
    printf("%d\n%d",opt[p],p);
}