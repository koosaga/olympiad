#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m;
int adj[505][505];

const int MAXN = 505;
struct mincostflow{
    struct edg{int pos, cap, rev, cost;};
    vector<edg> graph[MAXN];
     
    int end;
    void init(int x){
        end = x;
        for(int i=0; i<MAXN; i++){
            graph[i].clear();
        }
    }
     
    void add_edge(int s, int e, int x, int c){
        graph[s].push_back({e,x,(int)graph[e].size(),c});
        graph[e].push_back({s,0,(int)graph[s].size()-1,-c});
    }
     
    int dist[MAXN], pa[MAXN], pe[MAXN];
     
    bool BF(){
        bool inque[MAXN] = {};
        memset(dist,0x3f,sizeof(dist));
        memset(pa,0,sizeof(pa));
        memset(pe,0,sizeof(pe));
        dist[0] = 0;
        queue<int> q;
        q.push(0);
        inque[0] = 1;
        while(!q.empty()){
            int i = q.front();
            q.pop();
            inque[i] = 0;
            for (int j=0; j<graph[i].size(); j++){
                edg x = graph[i][j];
                if(x.cap > 0 && dist[x.pos] > dist[i] + x.cost){
                    dist[x.pos] = dist[i] + x.cost;
                    pa[x.pos] = i;
                    pe[x.pos] = j;
                    if(!inque[x.pos]){
                        inque[x.pos] = 1;
                        q.push(x.pos);
                    }
                }
            }
        }
        return dist[end] < 1e9;
    }
     
    int mcmf(){
        int ret = 0;
        while(BF()){
            ret += dist[end];
            int pos = end;
            while (pos) {
                int rev = graph[pa[pos]][pe[pos]].rev;
                graph[pa[pos]][pe[pos]].cap--;
                graph[pos][rev].cap++;
                pos = pa[pos];
            }
        }
        return ret;
    }
}mcmf;

void solve(){
    memset(adj, 0x3f, sizeof(adj));
    cin >> n >> m;
    mcmf.init(n+1);
    for(int i=0; i<m; i++){
        int s, e;
        cin >> s >> e;
        adj[s][e] = adj[e][s] = 1;
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
            }
        }
    }
    int a[505], b[505];
    for(int i=1; i<=n; i++){
        cin >> a[i];
    }
    for(int i=1; i<=n; i++){
        cin >> b[i];
    }
    for(int i=1; i<=n; i++){
        if(a[i] == 1 && b[i] == 0) mcmf.add_edge(0, i, 1, 0);
        if(a[i] == 0 && b[i] == 1) mcmf.add_edge(i, n+1, 1, 0);
        for(int j=1; j<=n; j++){
            if(a[i] == 1 && b[i] == 0 && a[j] == 0 && b[j] == 1){
                mcmf.add_edge(i, j, 1, adj[i][j]);
            }
        }
    }
    cout << mcmf.mcmf() << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}