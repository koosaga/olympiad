#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m;
int sx[205], sy[205], ex[205], ey[205], w[205];

struct edg{
    int pos, cap, rev, cost;
};

vector<edg> graph[405];

void add_edge(int s, int e, int x){
    graph[s].push_back({e, 1, (int)graph[e].size(), x});
    graph[e].push_back({s, 0, (int)graph[s].size() - 1, -x});
}

bool mid(int s, int x, int e){
    if(s > e) return mid(e, x, s);
    return s <= x && x <= e;
}

int dist[405], pa[405], pe[405];

void solve(){
    int flow = 0, cost = 0;
    while(1){
        bool in_que[405] = {}, vis[405] = {};
        memset(dist,0x3f,sizeof(dist));
        dist[0] = 0;
        queue<int> q;
        q.push(0);
        in_que[0] = 1;
        while(!q.empty()){
            int qf = q.front();
            q.pop();
            in_que[qf] = 0;
            vis[qf] = 1;
            for(int i=0; i<graph[qf].size(); i++){
                edg e = graph[qf][i];
                if(e.cap > 0 && dist[e.pos] > dist[qf] - e.cost){
                    dist[e.pos] = dist[qf] - e.cost;
                    pa[e.pos] = qf;
                    pe[e.pos] = i;
                    if(!in_que[e.pos]){
                        in_que[e.pos] = 1;
                        q.push(e.pos);
                    }
                }
            }
        }
        if(!vis[n+m+1]) break;
        int pos = n + m + 1;
        while(pos){
            int rev = graph[pa[pos]][pe[pos]].rev;
            graph[pa[pos]][pe[pos]].cap--;
            graph[pos][rev].cap++;
            pos = pa[pos];
        }
        flow++;
        cost -= dist[n+m+1];
    }
    printf("%d %d\n",flow, cost);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m);
        for(int i=1; i<=n; i++){
            scanf("%d %d %d %d %d",&sx[i],&sy[i],&ex[i],&ey[i],&w[i]);
            add_edge(0, i, 0);
        }
        for(int i=1; i<=m; i++){
            add_edge(i + n, m + n + 1, 0);
            int px, py, qx, qy, c;
            scanf("%d %d %d %d %d",&px,&py,&qx,&qy,&c);
            for(int j=1; j<=n; j++){
                if(mid(py, sy[j], qy) && mid(sx[j], px, ex[j])){
                    add_edge(j, i + n, c * w[j]);
                }
            }
        }
        solve();
        for(int i=0; i<n+m+2; i++){
            graph[i].clear();
        }
    }
}