#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef pair<int, int> pi;

int n, m, chk[MAXN], vis[MAXN];
int s[MAXN], e[MAXN];
vector<pi> gph[MAXN], rev[MAXN];

void dfs2(int x){
    vis[x] = 1;
    for(auto &i : rev[x]){
        if(!vis[i.second]){
            chk[i.first] = 1;
            dfs2(i.second);
        }
    }
}

void dfs1(int x){
    vis[x] = 1;
    for(auto &i : gph[x]){
        if(!vis[i.second]){
            chk[i.first] = 1;
            dfs1(i.second);
        }
    }
}

int main(){
    int tc;
    scanf("%d",&tc);
    while(tc--){
        scanf("%d %d",&n,&m);
        for(int i=1; i<=m; i++){
            scanf("%d %d",&s[i],&e[i]);
            gph[s[i]].push_back(pi(i, e[i]));
            rev[e[i]].push_back(pi(i, s[i]));
            chk[i] = 0;
        }
        fill(vis, vis + n + 1, 0);
        dfs1(1);
        fill(vis, vis + n + 1, 0);
        dfs2(1);
        vector<int> ans;
        for(int i=1; i<=m; i++){
            if(!chk[i]) ans.push_back(i);
        }
        while(ans.size() > m - 2 * n) ans.pop_back();
        for(auto &i : ans) printf("%d %d\n", s[i], e[i]);
        puts("");
        for(int i=1; i<=n; i++){
            gph[i].clear();
            rev[i].clear();
        }
    }
}