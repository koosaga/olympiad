#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 100005;
typedef long long lint;

void ass(bool p){
    if(p) return;
    puts("There is no route, Karl!");
    exit(0);
}

int n, m;
vector<int> gph[MAXN];
vector<int> dfn;
bool vis[MAXN];
int lbl[MAXN], cn, cm;
vector<int> chain[405];
int cs[405], ce[405];
int adj[22][22];

void dfs(int x){
    if(vis[x]) return;
    vis[x] = 1;
    dfn.push_back(x);
    dfs(gph[x][0]);
}

int dp[1<<20][20];

int f(int msk, int x){
    if(msk == (1<<cn) - 1){
        if(adj[x][0] <= 0) return -1e9;
        int ans = chain[adj[x][0]-1].size() - 1;
        return ans;
    }
    if(~dp[msk][x]) return dp[msk][x];
    int ans = -1e9;
    for(int i=0; i<cn; i++){
        if(adj[x][i] > 0 && (msk >> i) % 2 == 0){
            ans = max(ans, f(msk | (1<<i), i) + (int)chain[adj[x][i]-1].size() - 1);
        }
    }
    return dp[msk][x] = ans;
}

vector<int> trk;

void g(int msk, int x){
    if(msk == (1<<cn) - 1){
        trk.push_back(adj[x][0]);
        return;
    }
    int v1 = f(msk, x);
    for(int i=0; i<cn; i++){
        if(adj[x][i] > 0 && (msk >> i) % 2 == 0){
            if(f(msk | (1<<i), i) + (int)chain[adj[x][i]-1].size() - 1 == v1){
                trk.push_back(adj[x][i]);
                g(msk | (1<<i), i);
                return;
            }
        }
    }
}

int main(){
    scanf("%d %d",&n,&m);
    set<pi> edgs;
    for(int i=0; i<m; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        if(s == e) continue;
        if(edgs.find(pi(s, e)) != edgs.end()) continue;
        edgs.insert(pi(s, e));
        gph[s].push_back(e);
    }
    vector<int> v;
    for(int i=1; i<=n; i++){
        ass(gph[i].size());
        if(gph[i].size() > 1) v.push_back(i);
    }
    if(v.empty()){
        dfs(1);
        ass(dfn.size() == n);
        for(auto &i : dfn) printf("%d ", i);
        printf("1\n");
        return 0;
    }
    memset(lbl, -1, sizeof(lbl));
    for(auto &i : v) lbl[i] = cn++;
    for(auto &i : v){
        for(auto &j : gph[i]){
            vector<int> ch = {i, j};
            set<int> s;
            s.insert(j);
            bool bad = 0;
            for(int k=j; gph[k].size()==1; k=gph[k][0]){
                if(s.find(gph[k][0]) != s.end()){
                    bad = 1;
                    break;
                }
                s.insert(gph[k][0]);
                ch.push_back(gph[k][0]);
            }
            if(bad) continue;
            chain[cm] = ch;
            cs[cm] = lbl[ch.front()];
            ce[cm] = lbl[ch.back()];
            cm++;
        }
    }
    for(int i=0; i<cn; i++){
        for(int j=0; j<cn; j++){
            int cur = -1, curp = -1;
            for(int k=0; k<cm; k++){
                if(cs[k] == i && ce[k] == j){
                    if(curp < (int)chain[k].size()){
                        curp = chain[k].size();
                        cur = k;
                    }
                }
            }
            adj[i][j] = cur + 1;
        }
    }
    memset(dp, -1, sizeof(dp));
    ass(f(1, 0) == n);
    g(1, 0);
    vector<int> route;
    for(auto &i : trk){
    //  printf("%d ", i);
        for(int j=0; j<chain[i-1].size()-1; j++) route.push_back(chain[i-1][j]);
    }
    rotate(route.begin(), find(route.begin(), route.end(), 1), route.end());
    route.push_back(1);
    for(auto &i : route) printf("%d ", i);
}
