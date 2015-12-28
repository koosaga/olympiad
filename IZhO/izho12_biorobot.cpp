#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
 
int n,m,inp[200005];
int piv,sz[200005],a[200005];
vector<int> g[200005];
int root;
 
int dfs(int x){
    int num = ++piv;
    a[num] = inp[x];
    sz[num] = 1;
    for(int &i : g[x]) sz[num] += dfs(i);
    return sz[num];
}
 
int dp[2][200005];
int main(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        int p;
        scanf("%d %d",&p,&inp[i]);
        if(p) g[p].push_back(i);
        else root = i;
    }
    dfs(root);
    for (int i=1; i<=m; i++) {
        dp[i%2][n+1] = -1e9;
        for (int j=n; j; j--) {
            dp[i%2][j] = max(dp[i%2][j+1],dp[(i-1)%2][j+sz[j]] + a[j]);
        }
    }
    printf("%d",dp[m%2][1]);
}
