#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 200005;

vector<pi> gph[MAXN];
int mtch[MAXN], rev[MAXN], ecnt, fcnt;
pi vtx[MAXN];
vector<int> pref[MAXN], suff[MAXN];
vector<int> rgph[3 * MAXN];



int cost[3 * MAXN], vis[3 * MAXN], dp[3 * MAXN], stk[3 * MAXN];

void dfs(int x){
    if(stk[x]){
        puts("Infinite");
        exit(0);
    }
    if(vis[x]) return;
    vis[x] = 1;
    stk[x] = 1;
    for(auto &i : rgph[x]) dfs(i);
    stk[x] = 0;
}

int f(int x){
    if(~dp[x]) return dp[x];
    int ret = 0;
    for(auto &i : rgph[x]) ret = max(ret, f(i));
    return dp[x] = ret+ cost[x];
}

int main(){
    int n, m;
    scanf("%d %d",&n,&m);
    for(int i=1; i<=m; i++){
        int s, e, x;
        scanf("%d %d %d",&s,&e,&x);
        if(x == 1){
            gph[s].push_back(pi(++ecnt, e));
            rev[ecnt] = gph[s].size() - 1;
            vtx[ecnt] = pi(s, e);
        }
        else{
            gph[e].push_back(pi(++ecnt, s));
            gph[s].push_back(pi(++ecnt, e));
            mtch[ecnt - 1] = ecnt;
            mtch[ecnt] = ecnt - 1;
            rev[ecnt - 1] = gph[e].size() - 1;
            rev[ecnt] = gph[s].size() - 1;
            vtx[ecnt - 1] = pi(e, s);
            vtx[ecnt] = pi(s, e);
        }
    }
    for(int i=1; i<=ecnt; i++) cost[i] = 1;
    fcnt = ecnt;
    for(int i=1; i<=n; i++){
        pref[i].resize(gph[i].size());
        suff[i].resize(gph[i].size());
        for(int j=0; j<gph[i].size(); j++){
            pref[i][j] = ++fcnt;
            suff[i][j] = ++fcnt;
            rgph[pref[i][j]].push_back(gph[i][j].first);
            rgph[suff[i][j]].push_back(gph[i][j].first);
        }
        for(int j=1; j<gph[i].size(); j++){
            rgph[pref[i][j]].push_back(pref[i][j-1]);
            rgph[suff[i][j-1]].push_back(suff[i][j]);
        }
    }
    for(int i=1; i<=ecnt; i++){
        if(mtch[i] == 0){
            if(gph[vtx[i].second].size()){
                rgph[i].push_back(pref[vtx[i].second].back());
            }
            continue;
        }
        else{
            int pos = rev[mtch[i]];
            int nxt = vtx[i].second;
            if(pos > 0) rgph[i].push_back(pref[nxt][pos - 1]);
            if(pos + 1 < suff[nxt].size()) rgph[i].push_back(suff[nxt][pos + 1]);
        }
    }
    for(int i=1; i<=fcnt; i++){
        if(!vis[i]) dfs(i);
    }
    memset(dp, -1, sizeof(dp));
    int ret = 0;
    for(int i=1; i<=fcnt; i++){
        ret = max(ret, f(i));
    }
    cout << ret << endl;
}