#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const double eps = 1e-9;
const int MAXN = 105;

struct maxflow{
    struct edg{int pos;
        double cap;
        int rev;};
    vector<edg> gph[MAXN];

    void clear(){
        for(int i=0; i<MAXN; i++){
            gph[i].clear();
        }
    }

    void add_edge(int s, int e, double x){
        gph[s].push_back({e, x, (int)gph[e].size()});
        gph[e].push_back({s, 0, (int)gph[s].size()-1});
    }

    int dis[MAXN], pnt[MAXN];

    bool bfs(int src, int sink){
        memset(dis, 0, sizeof(dis));
        memset(pnt, 0, sizeof(pnt));
        queue<int> que;
        que.push(src);
        dis[src] = 1;
        while(!que.empty()){
            int x = que.front();
            que.pop();
            for(int i=0; i<gph[x].size(); i++){
                edg e = gph[x][i];
                if(e.cap > eps && !dis[e.pos]){
                    dis[e.pos] = dis[x] + 1;
                    que.push(e.pos);
                }
            }
        }
        return dis[sink] > 0;
    }

    double dfs(int x, int sink, double f){
        if(x == sink) return f;
        for(; pnt[x] < gph[x].size(); pnt[x]++){
            edg e = gph[x][pnt[x]];
            if(e.cap > 0 && dis[e.pos] == dis[x] + 1){
                double w = dfs(e.pos, sink, min(f, e.cap));
                if(w > 0){
                    gph[x][pnt[x]].cap -= w;
                    gph[e.pos][e.rev].cap += w;
                    return w;
                }
            }
        }
        return 0;
    }

    double match(int src, int sink){
        double ret = 0;
        while(bfs(src, sink)){
            double r = 0;
            while((r = dfs(src, sink, 2e9)) > eps){
                ret += r;
            }
        }
        return ret;
    }

    bool vis[105];
    void dfs2(int x){
        if(vis[x]) return;
        vis[x] = 1;
        for(auto &i : gph[x]){
            if(i.cap > 1e-7) dfs2(i.pos);
        }
    }

    void get_cut(int src, int sink){
        dfs2(src);
        vector<int> v;
        for(int i=src+1; i<sink; i++){
            if(!vis[i]) v.push_back(i);
        }
        printf("%d\n", v.size());
        for(auto &i : v) printf("%d\n", i);
    }
}mf;

int n, m, s[1005], e[1005], deg[105];

bool trial(double x, int t){
    mf.clear();
    for(int i=1; i<=n; i++){
        mf.add_edge(0, i, x);
        mf.add_edge(i, n+1, 0.5 * deg[i]);
    }
    for(int i=0; i<m; i++){
        mf.add_edge(s[i], e[i], 0.5);
        mf.add_edge(e[i], s[i], 0.5);
    }
    bool ret = mf.match(0, n+1) < m - eps;
    if(t == 1) mf.get_cut(0, n+1);
    return ret;
}

int main(){
    cin >> n >> m;
    for(int i=0; i<m; i++){
        cin >> s[i] >> e[i];
        deg[s[i]]++;
        deg[e[i]]++;
    }
    double s = 0, e = 100;
    for(int i=0; i<100; i++){
        double m = (s+e)/2;
        if(trial(m, 0)) s = m;
        else e = m;
    }
    trial(s, 1);
}
