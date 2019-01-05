#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 205;
const double eps = 1e-11;

struct mc{
    struct edg{ int pos; double cap; int rev, cost; };
    vector<edg> gph[MAXN];
    void clear(){
        for(int i=0; i<MAXN; i++) gph[i].clear();
    }
    void add_edge(int s, int e, double x, int c){
    //  printf("%d %d %.10f %d\n", s, e, x, c);
        gph[s].push_back({e, x, (int)gph[e].size(), c});
        gph[e].push_back({s, 0, (int)gph[s].size()-1, -c});
    }
    int dist[MAXN], pa[MAXN], pe[MAXN];
    bool inque[MAXN];
    bool spfa(int src, int sink){
        memset(dist, 0x3f, sizeof(dist));
        memset(inque, 0, sizeof(inque));
        queue<int> que;
        dist[src] = 0;
        inque[src] = 1;
        que.push(src);
        bool ok = 0;
        while(!que.empty()){
            int x = que.front();
            que.pop();
            if(x == sink) ok = 1;
            inque[x] = 0;
            for(int i=0; i<gph[x].size(); i++){
                edg e = gph[x][i];
                if(e.cap > eps && dist[e.pos] > dist[x] + e.cost){
                    dist[e.pos] = dist[x] + e.cost;
                    pa[e.pos] = x;
                    pe[e.pos] = i;
                    if(!inque[e.pos]){
                        inque[e.pos] = 1;
                        que.push(e.pos);
                    }
                }
            }
        }
        return ok;
    }
    pair<double, double> match(int src, int sink){
        double flw = 0;
        double cst = 0;
        while(spfa(src, sink)){
            double cap = 1e9;
            for(int pos = sink; pos != src; pos = pa[pos]){
                cap = min(cap, gph[pa[pos]][pe[pos]].cap);
            }
            flw += cap;
            cst += dist[sink] * cap;
            for(int pos = sink; pos != src; pos = pa[pos]){
                int rev = gph[pa[pos]][pe[pos]].rev;
                gph[pa[pos]][pe[pos]].cap -= cap;
                gph[pos][rev].cap += cap;
            }
        }
        return make_pair(flw, cst);
    }
}mcmf;
    
int n, m, p, s, t;
vector<tuple<int, int, int, int> > v;

pair<double, double> trial(double t){
    mcmf.clear();
    for(auto &i : v){
        int s, e, x, y; tie(s, e, x, y) = i;
        mcmf.add_edge(s, e, t * y, x);
    }
    mcmf.add_edge(::t, n, 1, 0);
    auto ret = mcmf.match(s, n);
    ret.second += p * t;
//  printf("%.10f %.10f %.10f\n", t, ret.first, ret.second);
    return ret;
}

int main(){
    cin >> n >> m >> p >> s >> t;
    s--, t--;
    for(int i=0; i<m; i++){
        int s, e, x, y;
        cin >> s >> e >> x >> y;
        s--, e--;
        v.emplace_back(s, e, x, y);
    }
    double s = 0, e = 1;
    for(int i=0; i<50; i++){
        double m = (s + e) / 2;
        if(trial(m).first >= 1 - eps) e = m;
        else s = m;
    }
    e = 1;
    for(int i=0; i<50; i++){
        double m1 = (2 * s + e) / 3;
        double m2 = (s + 2 * e) / 3;
        if(trial(m1).second < trial(m2).second) e = m2;
        else s = m1;
    }
    printf("%.10f\n", trial(s).second);
}
