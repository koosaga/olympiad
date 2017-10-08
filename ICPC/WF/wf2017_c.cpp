#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int n, m, a[105][105];
int w[105], h[105];

const int MAXN = 205;
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
        gph[e].push_back({s, 0, (int)gph[s].size() - 1});
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
            edg e = gph[x][pnt[x]];
            if(e.cap > 0 && dis[e.pos] == dis[x] + 1){
                int w = dfs(e.pos, sink, min(f, e.cap));
                if(w){
                    gph[x][pnt[x]].cap -= w;
                    gph[e.pos][e.rev].cap += w;
                    return w;
                }
            }
        }
        return 0;
    }

    lint match(int src, int sink){
        int ret = 0;
        while(bfs(src, sink)){
            int r;
            while((r = dfs(src, sink, 2e9))) ret += r;
        }
        return ret;
    }
}mf;

int solve(int t){
    int cw[105], ch[105], p = 0;
    int th = 0;
    for(int i=0; i<n; i++){
        if(w[i] == t) cw[i] = ++p;
    }
    th = p;
    for(int i=0; i<m; i++){
        if(h[i] == t) ch[i] = ++p;
    }
    int sum[205] = {};
    int cnt = 0;
    mf.clear();
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j] == 0) continue;
            if(w[i] == t && h[j] == t){
                mf.add_edge(cw[i], ch[j], 1);
                sum[cw[i]]++;
                sum[ch[j]]++;
                cnt++;
            }
            else if(w[i] == t && h[j] > t){
                mf.add_edge(cw[i], p + 1, 1);
                sum[cw[i]]++;
                cnt++;
            }
            else if(h[j] == t && w[i] > t){
                mf.add_edge(0, ch[j], 1);
                sum[ch[j]]++;
                cnt++;
            }
        }
    }
    for(int i=1; i<=th; i++) mf.add_edge(0, i, sum[i] - 1);
    for(int i=th+1; i<=p; i++) mf.add_edge(i, p + 1, sum[i] - 1);
    return cnt - mf.match(0, p+1);
}
int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> a[i][j];
            w[i] = max(w[i], a[i][j]);
            h[j] = max(h[j], a[i][j]);
        }
    }
    vector<int> ev;
    for(int i=0; i<n; i++) ev.push_back(w[i]);
    for(int i=0; i<m; i++) ev.push_back(h[i]);
    sort(ev.begin(), ev.end());
    ev.resize(unique(ev.begin(), ev.end()) - ev.begin());
    reverse(ev.begin(), ev.end());
    lint ret = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) ret += a[i][j];
    }
    int cnt = 0;
    for(auto &i : ev){
        int k = solve(i);
        cnt -= k;
        if(i != 0) ret -= 1ll * i * solve(i);
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j]) cnt++;
        }
    }
    cout << ret - cnt;
}

