#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
int n;
vector<pi> graph[100005];
int depth[100005];
int pa[100005][17], minv[100005][17], maxv[100005][17];
 
void dfs(int x, int p, int e, int d){
    if(x != 1){
        pa[x][0] = p;
        minv[x][0] = e;
        maxv[x][0] = e;
        depth[x] = d;
        for (int i=1; (1<<i) <= d; i++) {
            pa[x][i] = pa[pa[x][i-1]][i-1];
            minv[x][i] = min(minv[pa[x][i-1]][i-1],minv[x][i-1]);
            maxv[x][i] = max(maxv[pa[x][i-1]][i-1],maxv[x][i-1]);
        }
    }
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i].second == p) continue;
        dfs(graph[x][i].second,x,graph[x][i].first,d+1);
    }
}
 
inline void query(int a, int b){
    int diff = depth[b] - depth[a];
    int minr = 1e9, maxr = 0;
    for (int i=0; diff; i++) {
        if(diff&1){
            minr = min(minr,minv[b][i]);
            maxr = max(maxr,maxv[b][i]);
            b = pa[b][i];
        }
        diff >>= 1;
    }
    for (int i=16; i>=0; i--) {
        if(pa[a][i] != pa[b][i]){
            minr = min(minr,minv[a][i]);
            maxr = max(maxr,maxv[a][i]);
            minr = min(minr,minv[b][i]);
            maxr = max(maxr,maxv[b][i]);
            a = pa[a][i];
            b = pa[b][i];
        }
    }
    if(a != b){
        minr = min(minr,minv[a][0]);
        maxr = max(maxr,maxv[a][0]);
        minr = min(minr,minv[b][0]);
        maxr = max(maxr,maxv[b][0]);
    }
    printf("%d %d\n",minr,maxr);
}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n-1; i++) {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        graph[a].push_back(pi(c,b));
        graph[b].push_back(pi(c,a));
    }
    dfs(1,0,0,0);
    int q;
    scanf("%d",&q);
    while (q--) {
        int a,b;
        scanf("%d %d",&a,&b);
        if(depth[a] > depth[b]) swap(a,b);
        query(a,b);
    }
}