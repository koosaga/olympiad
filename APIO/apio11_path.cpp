#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
 
int n, sx, sy, ex, ey, x1[1005], x2[1005], _y1[1005], y2[1005];
int ban[2005][2005], ban2[2005][2005];
 
vector<int> vx, vy;
 
void input(){
    memset(ban,0,sizeof(ban));
    memset(ban2,0,sizeof(ban2));
    vx.clear();
    vy.clear();
    scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
    vx.push_back(sx);
    vy.push_back(sy);
    vx.push_back(ex);
    vy.push_back(ey);
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d %d %d",&x1[i],&_y1[i],&x2[i],&y2[i]);
        if(x1[i] > x2[i]) swap(x1[i],x2[i]);
        if(_y1[i] > y2[i]) swap(_y1[i],y2[i]);
        vx.push_back(x1[i]);
        vy.push_back(_y1[i]);
        vx.push_back(x2[i]);
        vy.push_back(y2[i]);
    }
    sort(vx.begin(),vx.end());
    sort(vy.begin(),vy.end());
    vx.resize(unique(vx.begin(),vx.end()) - vx.begin());
    vy.resize(unique(vy.begin(),vy.end()) - vy.begin());
    for (int i=0; i<n; i++) {
        x1[i] = (int)(lower_bound(vx.begin(),vx.end(),x1[i]) - vx.begin());
        _y1[i] = (int)(lower_bound(vy.begin(),vy.end(),_y1[i]) - vy.begin());
        x2[i] = (int)(lower_bound(vx.begin(),vx.end(),x2[i]) - vx.begin());
        y2[i] = (int)(lower_bound(vy.begin(),vy.end(),y2[i]) - vy.begin());
        for (int j=x1[i]; j<=x2[i]; j++) {
            ban[j][_y1[i]]++;
            ban[j][y2[i]]--;
        }
        for (int j=_y1[i]; j<=y2[i]; j++) {
            ban2[x1[i]][j]++;
            ban2[x2[i]][j]--;
        }
    }
    sx = (int)(lower_bound(vx.begin(),vx.end(),sx) - vx.begin());
    sy = (int)(lower_bound(vy.begin(),vy.end(),sy) - vy.begin());
    ex = (int)(lower_bound(vx.begin(),vx.end(),ex) - vx.begin());
    ey = (int)(lower_bound(vy.begin(),vy.end(),ey) - vy.begin());
}
 
struct edg{
    int x,y;
    long long dist;
};
bool operator<(edg a, edg b){return a.dist > b.dist;}
 
vector<edg> graph[2005][2005];
 
void add_edge(int sx, int sy, int ex, int ey){
 //   printf("[%d,%d] <-> [%d,%d]\n",vx[sx],vy[sy],vx[ex],vy[ey]);
    long long dist = 1ll * abs(vx[ex] - vx[sx]) + 1ll * abs(vy[sy] - vy[ey]);
    graph[sx][sy].push_back((edg){ex,ey,dist});
    graph[ex][ey].push_back((edg){sx,sy,dist});
}
 
void make_graph(){
    for (int i=0; i<2*n+2; i++){
        for (int j=0; j<2*n+2; j++) {
            graph[i][j].clear();
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=x1[i]; j<x2[i]; j++) {
            add_edge(j,_y1[i],j+1,_y1[i]);
            add_edge(j,y2[i],j+1,y2[i]);
        }
        for (int j=_y1[i]; j<y2[i]; j++) {
            add_edge(x1[i],j,x1[i],j+1);
            add_edge(x2[i],j,x2[i],j+1);
        }
    }
    for (int i=0; i<vx.size(); i++) {
        int pos = -1, mode = 0;
        for (int j=0; j<vy.size(); j++) {
            if((i == sx && j == sy) || (i == ex && j == ey)){
                if(pos != -1){
                    add_edge(i,pos,i,j);
                }
                pos = j;
            }
            if(ban[i][j] > 0 && mode == 0){
                if(pos != -1){
                    add_edge(i,pos,i,j);
                }
                pos = j;
            }
            if(mode && mode + ban[i][j] == 0){
                pos = j;
            }
            mode += ban[i][j];
        }
    }
    for (int i=0; i<vy.size(); i++) {
        int pos = -1, mode = 0;
        for (int j=0; j<vx.size(); j++) {
            if((i == sy && j == sx) || (i == ey && j == ex)){
                if(pos != -1){
                    add_edge(pos,i,j,i);
                }
                pos = j;
            }
            if(ban2[j][i] > 0 && mode == 0){
                if(pos != -1){
                    add_edge(pos,i,j,i);
                }
            }
            if(mode && mode + ban2[j][i] == 0){
                pos = j;
            }
            mode += ban2[j][i];
        }
    }
}
 
bool vis[2005][2005];
priority_queue<edg> pq;
 
void solve(){
    input();
    make_graph();
    memset(vis,0,sizeof(vis));
    while (!pq.empty()) {
        pq.pop();
    }
    pq.push({sx,sy,0});
    while (!pq.empty()) {
        edg t = pq.top();
        pq.pop();
        if(t.x == ex && t.y == ey){
            printf("%lld\n",t.dist);
            return;
        }
        if(vis[t.x][t.y]) continue;
        vis[t.x][t.y] = 1;
        for (int i=0; i<graph[t.x][t.y].size(); i++) {
            edg tmp = graph[t.x][t.y][i];
            if(vis[tmp.x][tmp.y]) continue;
            pq.push({tmp.x,tmp.y,tmp.dist + t.dist});
        }
    }
    puts("No Path");
}
 
int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        solve();
    }
}