#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
 
struct edg{int pos, dist, cost;};
bool operator<(edg a, edg b){return a.dist > b.dist;}
 
vector<edg> graph[101];
priority_queue<edg> pq;
 
int high[101];
int n,m,s,e;
 
int main(){
    memset(high,0x3f,sizeof(high));
    scanf("%d %d %d %d",&n,&m,&s,&e);
    for (int i=0; i<m; i++) {
        int s,e,x,y;
        scanf("%d %d %d %d",&s,&e,&x,&y);
        graph[s].push_back({e,y,x});
        graph[e].push_back({s,y,x});
    }
    pq.push({s,0,0});
    int ret = 0, highp = 1e9;
    while (!pq.empty()) {
        edg t = pq.top();
        pq.pop();
        if(high[t.pos] <= t.cost) continue;
        high[t.pos] = t.cost;
        if(t.pos == e){
            if(highp == t.dist) continue;
            highp = t.dist;
            ret++;
        }
        for (auto &i : graph[t.pos]){
            pq.push({i.pos,t.dist + i.dist,t.cost + i.cost});
        }
    }
    printf("%d",ret);
}