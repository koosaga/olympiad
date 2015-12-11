#include <cstdio>
#include <vector>
using namespace std;
 
int n,c[100005],k;
int dp[100005][21];
 
vector<int> graph[100005];
int pa[100005];
 
void dfs(int x, int p){
    dp[x][0] = c[x];
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == p) continue;
        pa[graph[x][i]] = x;
        dfs(graph[x][i],x);
        for (int j=1; j<=k; j++) {
            dp[x][j] += dp[graph[x][i]][j-1];
        }
    }
}
int main(){
    scanf("%d %d",&n,&k);
    for (int i=0; i<n-1; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    for (int i=1; i<=n; i++) {
        scanf("%d",&c[i]);
    }
    dfs(1,0);
    for (int i=1; i<=n; i++) {
        int r = 0, x = k;
        int p = i;
        while (p) {
            r += dp[p][x];
            if(x == 0) break;
            r += dp[p][--x];
            p = pa[p];
        }
        while (x) {
            r += dp[1][--x];
        }
        printf("%d\n",r);
    }
}