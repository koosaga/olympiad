#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
 
struct bang{int x,y,n;}a[200005];
struct edge{
    long long dist;
    int dir, pos;
};
 
int n,m,k;
int graph[200005][4], len[200005][4];
int no_switch;
 
bool cmp1(bang a, bang b){
    return a.x == b.x ? (a.y < b.y) : (a.x < b.x);
}
 
bool cmp2(bang a, bang b){
    return a.y == b.y ? (a.x < b.x) : (a.y < b.y);
}
 
bool operator<(edge a, edge b){
    return a.dist > b.dist;
}
 
int vis[200005][2];
priority_queue<edge> pq;
long long ret = 1e18;
 
void dijkstra(){
    pq.push({0,0,0});
    while (!pq.empty()) {
        edge t = pq.top();
        pq.pop();
        if(vis[t.pos][t.dir]) continue;
        vis[t.pos][t.dir] = 1;
        if(t.pos == k+1) ret = min(ret,t.dist);
        for (int i=0; i<4; i++) {
            if(i == 2 && t.pos == 0 && no_switch) break;
            if(graph[t.pos][i] == -1) continue;
            int dir_change = (i/2 != t.dir);
            pq.push({t.dist + len[t.pos][i] + dir_change,t.dir ^ dir_change, graph[t.pos][i]});
        }
    }
}
 
int main(){
    memset(graph,-1,sizeof(graph));
    scanf("%d %d %d",&n,&m,&k);
    a[0] = {1,1,0};
    no_switch = 1;
    for (int i=1; i<=k; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        if(x == 1 && y == 1) no_switch = 0;
        else if(x == n && y == m){
            k--;
            i--;
            continue;
        }
        else a[i] = {x,y,i};
    }
    a[k+1] = {n,m,k+1};
    sort(a,a+k+2,cmp1);
    for (int i=0; i<=k+1; i++) {
        int e = i;
        while (e <= k+1 && a[i].x == a[e].x) e++;
        for (int j=i; j<e-1; j++) {
            graph[a[j].n][0] = a[j+1].n;
            len[a[j].n][0] = a[j+1].y - a[j].y;
        }
        for (int j=i+1; j<e; j++) {
            graph[a[j].n][1] = a[j-1].n;
            len[a[j].n][1] = a[j].y - a[j-1].y;
        }
        i = e-1;
    }
    sort(a,a+k+2,cmp2);
    for (int i=0; i<=k+1; i++) {
        int e = i;
        while (e <= k+1 && a[i].y == a[e].y) e++;
        for (int j=i; j<e-1; j++) {
            graph[a[j].n][2] = a[j+1].n;
            len[a[j].n][2] = a[j+1].x - a[j].x;
        }
        for (int j=i+1; j<e; j++) {
            graph[a[j].n][3] = a[j-1].n;
            len[a[j].n][3] = a[j].x - a[j-1].x;
        }
        i = e-1;
    }
    dijkstra();
    if(ret > 1e17) puts("-1");
    else printf("%lld",ret);
}