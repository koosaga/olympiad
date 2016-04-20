#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<long long,int> pi;
 
struct edge{int s,e,x;}a[200005];
 
long long dist[100005];
bool vis[100005];
vector<pi> graph[100005];
priority_queue<pi,vector<pi>,greater<pi> > pq;
 
int n,m,c;
 
void dijkstra(){
    pq.push(pi(0,1));
    while (!pq.empty()) {
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        dist[t.second] = t.first;
        for (int i=0; i<graph[t.second].size(); i++) {
            pi edg = graph[t.second][i];
            if(vis[edg.second]) continue;
            pq.push(pi(edg.first + t.first, edg.second));
        }
    }
}
 
vector<pi> cand;
 
int main(){
    scanf("%d %d %d",&n,&m,&c);
    for (int i=0; i<m; i++) {
        scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
        graph[a[i].s].push_back(pi(a[i].x,a[i].e));
        graph[a[i].e].push_back(pi(a[i].x,a[i].s));
    }
    dijkstra();
    for (int i=0; i<m; i++) {
        cand.push_back(pi(max(dist[a[i].s],dist[a[i].e]),a[i].x));
    }
    sort(cand.begin(),cand.end());
    long long cval = 0, ret = 1e18;
    for (int i=(int)cand.size()-1; i>=0; i--) {
        ret = min(ret,cand[i].first * c + cval);
        cval += cand[i].second;
    }
    ret = min(ret,cval);
    printf("%lld",ret);
}