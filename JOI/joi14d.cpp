#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef long long lint;
typedef pair<lint,int> pi;
 
vector<pi> graph[100005];
 
int n,m,x,h[100005];
int vis[100005];
 
priority_queue<pi,vector<pi>,greater<pi> > pq;
 
int main(){
    scanf("%d %d %d",&n,&m,&x);
    for (int i=1; i<=n; i++) {
        scanf("%d",&h[i]);
    }
    for (int i=0; i<m; i++) {
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(pi(x,e));
        graph[e].push_back(pi(x,s));
    }
    pq.push(pi(0,1));
    while (!pq.empty()) {
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        int spot = (int)max(0ll,x - t.first);
        if(spot > h[t.second]){
            t.first += spot - h[t.second];
            spot = h[t.second];
        }
        if(t.second == n){
            printf("%lld",h[n] - spot + t.first);
            return 0;
        }
        for (int i=0; i<graph[t.second].size(); i++) {
            pi e = graph[t.second][i];
            if(vis[e.second]) continue;
            if(e.first > h[t.second]) continue;
            pq.push(pi(t.first + max(0ll,e.first - spot) + e.first,e.second));
        }
    }
    puts("-1");
}