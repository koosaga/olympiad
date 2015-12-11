#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int,int> pi;
 
int cnt;
long long ret;
 
int n, m, k, q;
vector<pi> graph[20005];
 
int hubs[205], hnum[20005];
int dist[205][20005];
bool vis[20005];
 
priority_queue<pi,vector<pi>,greater<pi> > pq;
 
void dijkstra(int st, int* d){
    memset(vis,0,sizeof(vis));
    pq.push(pi(0,st));
    while(!pq.empty()){
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        d[t.second] = t.first;
        for (auto &i : graph[t.second]){
            if(vis[i.second]) continue;
            pq.push(pi(i.first + t.first, i.second));
        }
    }
}
 
int main(){
    memset(dist,0x3f,sizeof(dist));
    scanf("%d %d %d %d",&n,&m,&k,&q);
    for(int i=0; i<m; i++){
        int u, v, d;
        scanf("%d %d %d",&u,&v,&d);
        graph[u].push_back(pi(d,v));
    }
    for(int i=1; i<=k; i++){
        scanf("%d",&hubs[i]);
        hnum[hubs[i]] = i;
        dijkstra(hubs[i],dist[i]);
    }
    while(q--){
        int s, t;
        scanf("%d %d",&s,&t);
        if(hnum[s] != 0){
            if(dist[hnum[s]][t] > 1e9){
                continue;
            }
            else{
                cnt++;
                ret += dist[hnum[s]][t];
            }
        }
        else{
            int rets = 2e9;
            for(auto &i : graph[s]){
                rets = min(rets, dist[hnum[i.second]][t] + i.first);
            }
            if(rets > 1e9) continue;
            else{
                ret += rets;
                cnt++;
            }
        }
    }
    printf("%d\n%lld",cnt,ret);
}