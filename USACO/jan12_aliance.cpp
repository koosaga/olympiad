#include <cstdio>
#include <vector>
using namespace std;
 
vector<int> graph[100005];
 
int v,e,vis[100005];
 
void dfs(int x){
    if(vis[x]) return;
    vis[x] = 1;
    e += graph[x].size();
    v++;
    for (int i=0; i<graph[x].size(); i++) {
        dfs(graph[x][i]);
    }
}
 
int main(){
    int n,m;
    long long res = 1;
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    for (int i=1; i<=n; i++) {
        if(vis[i]) continue;
        v = e = 0;
        dfs(i);
        e /= 2;
        if(v == e) res *= 2;
        else res *= v;
        res %= 1000000007;
    }
    printf("%lld",res);
}