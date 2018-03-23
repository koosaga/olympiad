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

struct edg{int pos, cap, rev;};

int n, m;
vector<edg> graph[2005];

void add_edge(int s, int e){
    graph[s].push_back({e, 1, (int)graph[e].size()});
    graph[e].push_back({s, 0, (int)graph[s].size()-1});
}

bool vis[2005];
int pa[2005], pe[2005];

int dfs(int x){
    if(x == 2*n+1) return 1;
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

int match(){
    int ret = 0;
    while(dfs(0)){
        memset(vis,0,sizeof(vis));
        int pos = 2 * n + 1;
        while(pos){
            int rev = graph[pa[pos]][pe[pos]].rev;
            graph[pa[pos]][pe[pos]].cap--;
            graph[pos][rev].cap++;
            pos = pa[pos];
        }
        ret++;
    }
    memset(vis,0,sizeof(vis));
    return ret;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m);
        for(int i=0; i<m; i++){
            int s, e;
            scanf("%d %d",&s,&e);
            s++;
            e++;
            add_edge(s, e+n);
        }
        for(int i=1; i<=n; i++){
            add_edge(0, i);
            add_edge(i+n, 2*n+1);
        }
        printf("%d\n",match());
        for(int i=0; i<2*n+2; i++){
            graph[i].clear();
        }
    }
}