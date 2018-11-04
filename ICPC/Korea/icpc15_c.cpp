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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

const int MAXN = 2505;
struct maxflow{
    struct edg{int pos, cap, rev;};
    vector<edg> graph[MAXN];

    int end;

    void init(int x){
        end = x;
        for(int i=0; i<MAXN; i++){
            graph[i].clear();
        }
    }
     
    void add_edge(int s, int e, int x){
        graph[s].push_back({e, x, (int)graph[e].size()});
        graph[e].push_back({s, 0, (int)graph[s].size()-1});
    }
     
    bool vis[MAXN];
    int pa[MAXN], pe[MAXN];
     
    int dfs(int x){
        if(x == end) return 1;
        if(vis[x]) return 0;
        vis[x] = 1;
        for(int i=0; i<graph[x].size(); i++){
            edg e = graph[x][i];
            if(e.cap > 0 && dfs(e.pos)){
                pa[e.pos] = x;
                pe[e.pos] = i;
                return 1;
            }
        }
        return 0;
    }
    
    queue<int> q;
    int bfs(int x){
        q.push(x);
        vis[x] = 1;
        while(!q.empty()){
            x = q.front(); q.pop();
            for(int i=0; i<graph[x].size(); i++){
                edg e = graph[x][i];
                if(e.cap > 0 && !vis[e.pos]){
                    vis[e.pos] = 1;
                    pa[e.pos] = x;
                    pe[e.pos] = i;
                    q.push(e.pos);
                }
            }
        }
        return vis[end];
    }

    int match(){
        int ret = 0;
        while(bfs(0)){
            memset(vis,0,sizeof(vis));
            int minv = 1e9;
            for(int pos = end; pos; pos = pa[pos]){
                minv = min(minv, graph[pa[pos]][pe[pos]].cap);
            }
            for(int pos = end; pos; pos = pa[pos]){
                int rev = graph[pa[pos]][pe[pos]].rev;
                graph[pa[pos]][pe[pos]].cap -= minv;
                graph[pos][rev].cap += minv;
            }
            ret += minv;
        }
        memset(vis,0,sizeof(vis));
        return ret;
    }
}maxflow;

int n, m;
int a[55][55];

inline int get(int x, int y){
    return x * m + y + 1;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        cin >> n >> m;
        maxflow.init(n*m+1);
        int s = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                scanf("%d",&a[i][j]);
                s += a[i][j];
                if(i%2 != j%2) maxflow.add_edge(0, get(i, j), a[i][j]);
                else maxflow.add_edge(get(i, j), n*m+1, a[i][j]);
            }
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(i%2 != j%2){
                    if(j+1 < m) maxflow.add_edge(get(i, j), get(i, j+1), 1e9);
                    if(i+1 < n) maxflow.add_edge(get(i, j), get(i+1, j), 1e9);
                }
                else{
                    if(j+1 < m) maxflow.add_edge(get(i, j+1), get(i, j), 1e9);
                    if(i+1 < n) maxflow.add_edge(get(i+1, j), get(i, j), 1e9);
                }
            }
        }
        cout << s - maxflow.match() << endl;
    }
}