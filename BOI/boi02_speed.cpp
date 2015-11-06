#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
 
double dist[151][501];
int pa[151][501], pv[151][501], vis[151][501];
 
struct edg{
    int pos, vel;
    double dist;
};
 
bool operator<(edg a, edg b){return a.dist > b.dist;}
 
priority_queue<edg> pq;
vector<edg> graph[151];
 
int n,m,e;
 
void print(int pos, int p){
    if(pos != 0) print(pa[pos][p],pv[pos][p]);
    printf("%d ",pos);
}
 
int main(){
    scanf("%d %d %d",&n,&m,&e);
    for (int i=0; i<n; i++) {
        fill(dist[i],dist[i]+501,1e9);
    }
    for (int i=0; i<m; i++) {
        int s,e,x,y;
        scanf("%d %d %d %d",&s,&e,&x,&y);
        graph[s].push_back({e,x,1.0*y});
    }
    pq.push({0,70,0});
    dist[0][70] = 0;
    int p = 0;
    while (!pq.empty()) {
        edg t = pq.top();
        pq.pop();
        if(vis[t.pos][t.vel]) continue;
        vis[t.pos][t.vel] = 1;
        if(t.pos == e){
            p = t.vel;
            break;
        }
        for (auto &i : graph[t.pos]){
            if(i.vel == 0){
                if(dist[i.pos][t.vel] > dist[t.pos][t.vel] + i.dist / t.vel){
                    dist[i.pos][t.vel] = dist[t.pos][t.vel] + i.dist / t.vel;
                    pa[i.pos][t.vel] = t.pos;
                    pv[i.pos][t.vel] = t.vel;
                    pq.push({i.pos,t.vel,dist[i.pos][t.vel]});
                }
            }
            else{
                if(dist[i.pos][i.vel] > dist[t.pos][t.vel] + i.dist / i.vel){
                    dist[i.pos][i.vel] = dist[t.pos][t.vel]  + i.dist / i.vel;
                    pa[i.pos][i.vel] = t.pos;
                    pv[i.pos][i.vel] = t.vel;
                    pq.push({i.pos,i.vel,dist[i.pos][i.vel]});
                }
            }
        }
    }
    print(e,p);
}