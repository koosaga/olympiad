#include <cstdio>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
int n,m,q;
vector<pi> graph[3005];
priority_queue<pi,vector<pi>,greater<pi> > pq;
 
struct edg{int s,e,x;}edg[100005];
int dist[3005], vis[3005];
 
int main(){
    scanf("%d %d %d",&n,&m,&q);
    for (int i=0; i<m; i++) {
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(pi(x,e));
        graph[e].push_back(pi(x,s));
        edg[i] = {s,e,x};
    }
    while (q--) {
        int t;
        scanf("%d",&t);
        pq.push(pi(0,t));
    }
    while (!pq.empty()) {
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        dist[t.second] = t.first;
        for (auto &i : graph[t.second]){
            pq.push(pi(i.first + t.first,i.second));
        }
    }
    int dmax = 0;
    for (int i=0; i<m; i++) {
        dmax = max(dmax,dist[edg[i].s] + dist[edg[i].e] + edg[i].x);
    }
    printf("%d",(dmax+1)/2);
}