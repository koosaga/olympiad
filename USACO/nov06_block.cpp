#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int,int> pi;

vector<pi> graph[5005];
priority_queue<pi,vector<pi>,greater<pi> > pq;

int n,dist[5005],dist2[5005];

int main(){
    int m,s,e,x;
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(pi(x,e));
        graph[e].push_back(pi(x,s));
    }
    memset(dist,0x3f,sizeof(dist));
    memset(dist2,0x3f,sizeof(dist2));
    dist[1] = 0;
    pq.push(pi(0,1));
    while (!pq.empty()) {
        pi x = pq.top();
        pq.pop();
        if(dist2[x.second] < x.first) continue;
        for (int i=0; i<graph[x.second].size(); i++) {
            int r = x.first + graph[x.second][i].first;
            int pos = graph[x.second][i].second;
            if(dist[pos] > r){
                swap(dist[pos],r);
                pq.push(pi(dist[pos],pos));
            }
            if(dist2[pos] > r && dist[pos] < r){
                dist2[pos] = r;
                pq.push(pi(r,pos));
            }
        }
    }
    printf("%d",dist2[n]);
}