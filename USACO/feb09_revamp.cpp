#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
typedef pair<int,int> pi;
 
struct edge{int dist, pos, used;};
bool operator<(edge a, edge b){return a.dist > b.dist; }
 
priority_queue<edge> pq;
vector<pi> graph[10005];
 
int v[10005][21];
int n,m,k;
 
int main(){
    scanf("%d %d %d",&n,&m,&k);
    for (int i=0; i<m; i++) {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        graph[x].push_back(pi(z,y));
        graph[y].push_back(pi(z,x));
    }
    pq.push({0,1,k});
    while (!pq.empty()) {
        edge x = pq.top();
        pq.pop();
        if(x.pos == n){
            printf("%d",x.dist);
            return 0;
        }
        if(v[x.pos][x.used]) continue;
        v[x.pos][x.used] = 1;
        for (int i=0; i<graph[x.pos].size(); i++) {
            pi e = graph[x.pos][i];
            if(x.used && !v[e.second][x.used-1]){
                pq.push({x.dist,e.second,x.used-1});
            }
            if(!v[e.second][x.used]){
                pq.push({x.dist + e.first,e.second,x.used});
            }
        }
    }
}