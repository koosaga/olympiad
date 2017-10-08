#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, m, x[405], y[405], z[405], w[405];
vector<int> gph[405];

bool vis[405];
vector<int> comp[405];
int p, rev[405];

void dfs(int x, int h, vector<int> &v){
    if(vis[x]) return;
    vis[x] = 1;
    v.push_back(x);
    for(auto &i : gph[x]){
        if(z[i] <= h){
            dfs(i, h, v);
        }
    }
}

double wi[405];
double dist[405], fdist[405][405];

struct edg{
    int s, e;
    double x;
    bool operator<(const edg &e)const{
        return x < e.x;
    }
};

double solve(int h){
    memset(vis,0, sizeof(vis));
    p = 0;
    for(int i=1; i<=n; i++){
        if(!vis[i] && z[i] <= h){
            comp[p].clear();
            dfs(i, h, comp[p]);
            p++;
        }
    }
    for(int i=0; i<p; i++){
        wi[i] = 0;
        for(auto &j : comp[i]){
            rev[j] = i;
            wi[i] += w[j] * 0.5;
        }
    }
    vector<edg> lis[405];
    for(int i=0; i<p; i++){
        for(int j=0; j<p; j++){
            if(i == j) continue;
            vector<edg> tlis;
            for(auto &k : comp[i]){
                for(auto &l : comp[j]){
                    if(w[k] && w[l]){
                        tlis.push_back({k, l, fdist[k][l] - 1 + wi[j]});
                    }
                }
            }
            if(tlis.empty()) continue;
            auto mx = *min_element(tlis.begin(), tlis.end());
            lis[i].push_back(mx);
            edg mx2 = {0, 0, -1};
            edg mx3 = {0, 0, -1};
            for(int k=0; k<tlis.size(); k++){
                if(tlis[k].s != mx.s){
                    mx2 = min(mx2, tlis[k]);
                }
                if(tlis[k].e != mx.e){
                    mx3 = min(mx3, tlis[k]);
                }
            }
            if(mx2.s) lis[i].push_back(mx2);
            if(mx3.s) lis[i].push_back(mx3);
        }
    }
    fill(dist, dist + n + 1, 2e9);
    bool vis[405] = {};
    dist[1] = wi[rev[1]];
    while(1){
        int sk = -1;
        double ret = 1e9;
        for(int k=1; k<=n; k++){
            if(!vis[k] && ret > dist[k]){
                ret = dist[k];
                sk = k;
            }
        }
        if(sk == -1) break;
        vis[sk] = 1;
        if(rev[sk] == rev[n]){
            return ret;
        }
        for(auto &l : lis[rev[sk]]){
            if(l.s == sk && w[sk] == 1 && sk != 1) continue;
            dist[l.e] = min(dist[l.e], ret + l.x);
        }
    }
    return 1e9;
}

int main(){
    int p = 0;
    while(~scanf("%d %d",&n,&m)){
        for(int i=1; i<=n; i++){
            cin >> x[i] >> y[i] >> z[i] >> w[i];
            gph[i].clear();
        }
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                fdist[i][j] = hypot(x[j] - x[i], hypot(y[j] - y[i], z[j] - z[i]));
            }
        }
        vector<int> v;
        for(int i=0; i<m; i++){
            int s, e;
            scanf("%d %d",&s,&e);
            gph[s].push_back(e);
            gph[e].push_back(s);
        }
        for(int i=1; i<=n; i++){
            if(z[i] >= max(z[1], z[n])){
                v.push_back(z[i]);
            }
        }
        sort(v.begin(), v.end());
        v.resize(unique(v.begin(), v.end()) - v.begin());
        double ret = 1e9;
        for(int i=0; i<v.size(); i++){
            ret = min(ret, solve(v[i]));
        }
        if(ret > 1e8){
            printf("Case %d: impossible\n", ++p);
            continue;
        }
        printf("Case %d: %.4f\n", ++p,  ret);
    }
}
