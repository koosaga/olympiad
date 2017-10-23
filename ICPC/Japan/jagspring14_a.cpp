#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

vector<int> graph[100005];
vector<int> vis;

int n;
int pa[100005][17], dep[100005];

void bfs(){
    queue<int> q,d;
    q.push(1);
    d.push(0);
    while (!q.empty()) {
        int qf = q.front();
        int df = d.front();
        q.pop();
        d.pop();
        dep[qf] = df;
        vis.push_back(qf);
        for (int i=1; i<17; i++) {
            pa[qf][i] = pa[pa[qf][i-1]][i-1];
        }
        for (auto &i : graph[qf]){
            q.push(i);
            d.push(df+1);
        }
    }
}

int lca(int x, int y){
    if(dep[x] > dep[y]){
        swap(x,y);
    }
    int dx = dep[y] - dep[x];
    for (int i=0; (1<<i) <= dx; i++) {
        if((dx>>i)&1) y = pa[y][i];
    }
    for (int i=16; i>=0; i--) {
        if(pa[x][i] != pa[y][i]){
            x = pa[x][i];
            y = pa[y][i];
        }
    }
    if(x == y) return x;
    return pa[x][0];
}

int main(){
    scanf("%d",&n);
    for (int i=2; i<=n; i++) {
        scanf("%d",&pa[i][0]);
        graph[pa[i][0]].push_back(i);
    }
    bfs();
    long long ret = 0;
    for (int i=1; i<vis.size(); i++) {
        ret += dep[vis[i-1]] + dep[vis[i]] - 2 * dep[lca(vis[i-1],vis[i])];
    }
    printf("%lld",ret);
}