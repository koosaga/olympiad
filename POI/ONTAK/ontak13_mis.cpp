// by hyea
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505050;
int N;
int cost[MAXN];
vector<int> conn[MAXN];
vector<int> ngm;
void dfs(int a, int pa, int c, int d)
{
    c = max(c, cost[a]+d);
    ngm.push_back(c);
    for(auto x: conn[a])
    {
        if(x==pa) continue;
        dfs(x, a, c, d+1);
    }
}
int main()
{
    scanf("%d", &N);
    for(int i=1; i<=N; ++i)
        scanf("%d", cost+i);
    for(int i=0; i<N-1; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        conn[u].push_back(v);
        conn[v].push_back(u);
    }
    dfs(1, 0, 0, 0);
    sort(ngm.rbegin(), ngm.rend());
    int ans = 0;
    for(int i=0; i<N; ++i)
    {
        ans = max(ans, ngm[i]+i);
        //printf("%d ", ngm[i]);
    }
    //puts("");
    printf("%d\n", ans);
    return 0;
}
