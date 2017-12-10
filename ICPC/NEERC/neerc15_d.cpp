#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 50005;
typedef long long lint;

struct mat{
    int adj[3][3];
}spt[17][MAXN];

mat merge(mat s, mat e){
    mat x;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            x.adj[i][j] = 1e9;
            for(int k=0; k<3; k++){
                x.adj[i][j] = min(x.adj[i][j],s.adj[i][k] + e.adj[k][j]);
            }
        }
    }
    return x;
}

int n, q;
vector<int> gph[MAXN], tr[MAXN];
int num[MAXN][3], cnt;
int par[17][MAXN], dep[MAXN];

int lca(int s, int e){
    if(dep[s] < dep[e]) swap(s, e);
    int dx = dep[s] - dep[e];
    for(int i=0; i<17; i++){
        if((dx >> i) & 1) s = par[i][s];
    }
    for(int i=16; i>=0; i--){
        if(par[i][s] != par[i][e]){
            s = par[i][s];
            e = par[i][e];
        }
    }
    if(s != e) return par[0][s];
    return s;
}

mat init(){
    mat m;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            m.adj[i][j] = (i != j);
        }
    }
    return m;
}
mat path(int s, int e){
    int dx = dep[s] - dep[e];
    mat m = init();
    for(int i=0; i<17; i++){
        if((dx >> i) & 1){
            m = merge(m, spt[i][s]);
            s = par[i][s];
        }
    }
    return m;
}

int query(pi s, pi e){
    int l = lca(s.first, e.first);
    mat m = path(s.first, l);
    mat n = path(e.first, l);
    int ans = 1e9;
    for(int i=0; i<3; i++){
        ans = min(ans, m.adj[s.second][i] + n.adj[e.second][i]);
    }
    return ans;
}

void dfs(int x, int p){
    for(auto &i : tr[x]){
        if(i != p){
            par[0][i] = x;
            dep[i] = dep[x] + 1;
            dfs(i, x);
        }
    }
}

void build_structure(){
    dfs(1, 0);
    for(int i=2; i<=n-2; i++){
        set<pi> s;
        int p = par[0][i];
        mat m;
        for(int k=0; k<3; k++){
            for(int j=0; j<3; j++){
                if(k == j) continue;
                s.insert(pi(num[p][j], num[p][k]));
                s.insert(pi(num[i][j], num[i][k]));
            }
        }
        for(int j=0; j<3; j++){
            for(int k=0; k<3; k++){
                if(num[i][j] == num[p][k]) m.adj[j][k] = 0;
                else if(s.find(pi(num[i][j], num[p][k])) != s.end()){
                    m.adj[j][k] = 1;
                }
                else m.adj[j][k] = 2;
            }
        }
        spt[0][i] = m;
    }
    for(int i=1; i<17; i++){
        for(int j=1; j<=n-2; j++){
            par[i][j] = par[i-1][par[i-1][j]];
            spt[i][j] = merge(spt[i-1][j], spt[i-1][par[i-1][j]]);
        }
    }
}

set<int> sgph[MAXN];
pi cur[MAXN];

int main(){
    scanf("%d",&n);
    for(int i=0; i<n-3; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        gph[s].push_back(e);
        gph[e].push_back(s);
    }
    for(int i=0; i<n; i++){
        int s = i, e = (i+1)%n;
        gph[s+1].push_back(e+1);
        gph[e+1].push_back(s+1);
    }
    queue<int> que;
    for(int i=1; i<=n; i++){
        for(auto &j : gph[i]) sgph[i].insert(j);
        if(sgph[i].size() == 2) que.push(i);
    }
    while(!que.empty() && cnt < n - 2){
        int x = que.front();
        assert(sgph[x].size() == 2);
        que.pop();
        cnt++;
        num[cnt][0] = x;
        num[cnt][1] = *sgph[x].begin();
        num[cnt][2] = *sgph[x].rbegin();
        sgph[x].clear();
        for(int i=1; i<3; i++){
            sgph[num[cnt][i]].erase(x);
            if(sgph[num[cnt][i]].size() == 2) que.push(num[cnt][i]);
        }
    }
    vector<pair<pi, int>> emake;
    for(int i=1; i<=n-2; i++){
        for(int j=0; j<3; j++){
            pi x(num[i][j], num[i][(j+1)%3]);
            if(x.first > x.second) swap(x.first, x.second);
            emake.emplace_back(x, i);
        }
    }
    sort(emake.begin(), emake.end());
    for(int i=0; i+1<emake.size(); i++){
        if(emake[i].first == emake[i+1].first){
            int s = emake[i].second;
            int e = emake[i+1].second;
            tr[s].push_back(e);
            tr[e].push_back(s);
            i++;
        }
    }
    build_structure();
    for(int i=1; i<=n-2; i++){
        for(int j=0; j<3; j++){
            cur[num[i][j]] = pi(i, j);
        }
    }
    int q; scanf("%d",&q);
    while(q--){
        int s, e;
        scanf("%d %d",&s,&e);
        printf("%d\n", query(cur[s], cur[e]));
    }
}

