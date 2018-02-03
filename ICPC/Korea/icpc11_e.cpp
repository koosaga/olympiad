#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

const int MAXN = 605;
struct maxflow{
    struct edg{int pos, cap, rev;};
    vector<edg> gph[MAXN];

    void clear(){
        for(int i=0; i<MAXN; i++){
            gph[i].clear();
        }
    }

    void add_edge(int s, int e, int x){
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
                edg &e = gph[x][i];
                if(e.cap > 0 && !dis[e.pos]){
                    dis[e.pos] = dis[x] + 1;
                    que.push(e.pos);
                }
            }
        }
        return dis[sink] > 0;
    }

    int dfs(int x, int sink, int f){
        if(x == sink) return f;
        for(; pnt[x] < gph[x].size(); pnt[x]++){
            edg &e = gph[x][pnt[x]];
            if(e.cap > 0 && dis[e.pos] == dis[x] + 1){
                int w = dfs(e.pos, sink, min(f, e.cap));
                if(w){
                    e.cap -= w;
                    gph[e.pos][e.rev].cap += w;
                    return w;
                }
            }
        }
        return 0;
    }

    lint match(int src, int sink){
        lint ret = 0;
        while(bfs(src, sink)){
            int r;
            while((r = dfs(src, sink, 2e9))) ret += r;
        }
        return ret;
    }
}maxflow;

int m, n, s[105], w[105], d[105];

int main(){
    int t;
    cin >> t;
    while(t--){
        cin >> m >> n;
        maxflow.clear();
        int ret = 0;
        for(int i=0; i<n; i++){
            cin >> s[i] >> w[i] >> d[i];
            for(int j=s[i]; j<d[i]; j++){
                maxflow.add_edge(j, 501 + i, 1);
            }
            maxflow.add_edge(501 + i, 501 + n, w[i]);
            ret += w[i];
        }
        for(int i=1; i<=500; i++){
            maxflow.add_edge(0, i, m);
        }
        if(maxflow.match(0, 501 + n) != ret) puts("0");
        else{
            for(int i=501; i<501+n; i++){
                int chk[505] = {};
                int lst = 1e9;
                for(auto &j : maxflow.gph[i]){
                    if(j.pos == 501 + n) continue;
                    else if(j.cap > 0){
                        chk[j.pos] = 1;
                    }
                }
                vector<pi> v;
                for(int i=0; i<=502; i++){
                    if(chk[i] == 0){
                        if(lst < i) v.push_back(pi(lst, i));
                        lst = i+1;
                    }
                }
                printf("%d ", v.size());
                for(auto &i : v) printf("%d %d ", i.first, i.second);
                puts("");
            }
        }
    }
}

