#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int,int> >> adj(N);
    for(int i = 0; i < M; i++){
        int u, v;
        int t;
        cin >> u >> v >> t;
        u--; v--;
        adj[u].push_back({v, t});
        adj[v].push_back({u, t});
    }
    vector<int> par(N);
    int INF = 1e9;
    vector<int> dist(N, INF);
    using pq_t = pair<int,int>;
    {
        priority_queue<pq_t, vector<pq_t>, greater<pq_t>> pq;
        dist[0] = 0;
        vector<int> vis(N, 0);
        pq.push({dist[0], 0});
        while(!pq.empty()){
            auto [d, v] = pq.top();
            pq.pop();
            if(vis[v]) continue;
            vis[v] = 1;
            for(auto [w, l] : adj[v]){
                if(l + dist[v] < dist[w]){
                    dist[w] = l + dist[v];
                    par[w] = v;
                    pq.push({dist[w], w});
                }
            }
        }
    }
    vector<int> dist2(N, INF);
    {
        priority_queue<pq_t, vector<pq_t>, greater<pq_t>> pq;
        dist2[N-1] = 0;
        vector<int> vis(N, 0);
        pq.push({dist2[N-1], N-1});
        while(!pq.empty()){
            auto [d, v] = pq.top();
            pq.pop();
            if(vis[v]) continue;
            vis[v] = 1;
            for(auto [w, l] : adj[v]){
                if(l + dist2[v] < dist2[w]){
                    dist2[w] = l + dist2[v];
                    pq.push({dist2[w], w});
                }
            }
        }
    }

    if(dist[N-1] >= INF){
        cout << -1 << '\n';
        exit(0);
    }
    set<pair<int,int> > used;
    int c = N-1;
    while(c != 0){
        int p = par[c];
        used.insert({c, p});
        used.insert({p, c});
        c = p;
    }
    int path = dist[N-1];
    int path2 = INF;
    for(int v = 0; v < N; v++){
        for(auto [w, l] : adj[v]){
            if(used.count({v, w})) continue;
            path2 = min(path2, dist[v] + dist2[w] + l);
        }
    }
    if(path2 >= INF){
        cout << -1 << '\n';
        exit(0);
    }
    cout << (path + path2) << '\n';
}
