#include <cstdio>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
  
struct edg{int pos, dist, pen;};
bool operator<(edg a, edg b){return a.dist > b.dist;}
  
priority_queue<edg> pq;
vector<edg> graph[105];
int vis[105][10005];
  
int k,n,m;
  
int main(){
    scanf("%d %d %d",&k,&n,&m);
    for (int i=0; i<m; i++) {
        int a,b,c,d;
        scanf("%d %d %d %d",&a,&b,&c,&d);
        graph[a].push_back({b,c,d});
    }
    pq.push({1,0,k});
    while (!pq.empty()) {
        edg t = pq.top();
        pq.pop();
        if(vis[t.pos][t.pen]) continue;
        if(t.pos == n){
            printf("%d",t.dist);
            return 0;
        }
        vis[t.pos][t.pen] = 1;
        for (int i=0; i<graph[t.pos].size(); i++) {
            edg e = graph[t.pos][i];
            if(t.pen < e.pen) continue;
            pq.push({e.pos,t.dist + e.dist,t.pen - e.pen});
        }
    }
    puts("-1");
}