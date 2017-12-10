#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int dp[51][51][105], adj[51][51];
int dp2[51][51];
int n, m, a, b, c;

int f(int s, int e, int x){
    if(x == 0) return s == e;
    if(~dp[s][e][x]) return dp[s][e][x];
    for(int i=1; i<=n; i++){
        if(adj[s][i] && f(i, e, x-1)){
            return dp[s][e][x] = 1;
        }
    }
    return dp[s][e][x] = 0;
}

int g(int s, int p){
    if(s == n) return 1;
    if(p == 0) return 0;
    if(~dp2[s][p]) return dp2[s][p];
    int pa = 0, pb = 0, pc = 0;
    for(int i=1; i<=n; i++){
        if(f(s, i, a) && g(i, p-1)) pa = 1;
        if(f(s, i, b) && g(i, p-1)) pb = 1;
        if(f(s, i, c) && g(i, p-1)) pc = 1;
    }
    return dp2[s][p] = (pa && pb && pc);
}

int main(){
    memset(dp, -1, sizeof(dp));
    memset(dp2, -1, sizeof(dp2));
    cin >> n >> m >> a >> b >> c;
    for(int i=0; i<m; i++){
        int s, e;
        cin >> s >> e;
        adj[s][e] = 1;
    }
    for(int i=1; i<=n; i++){
        if(g(1, i)){
            cout << i;
            return 0;
        }
    }
    cout  << "IMPOSSIBLE";
}