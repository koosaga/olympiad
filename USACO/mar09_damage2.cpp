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
 
struct edg{
    int pos, cap, rev;
};
 
vector<edg> graph[6005];
 
void add_edge(int s, int e, int x){
    graph[s].push_back({e, x, (int)graph[e].size()});
    graph[e].push_back({s, 0, (int)graph[s].size()-1});
}
 
int n, m, c;
bool vis[6005];
int pa[6005], pe[6005];
  
bool dfs(int s, int e){
    if(s == e) return 1;
    if(vis[s]) return 0;
    vis[s] = 1;
    int p = 0;
    for(auto &i : graph[s]){
        if(i.cap > 0 && dfs(i.pos, e)){
            pa[i.pos] = s;
            pe[i.pos] = p;
            return 1;
        }
        p++;
    }
    return 0;
}
 
int flow(int s, int e){
    int ret = 0;
    while(dfs(s, e)){
        memset(vis,0,sizeof(vis));
        int pos = e;
        while(pos != s){
            int rev = graph[pa[pos]][pe[pos]].rev;
            graph[pa[pos]][pe[pos]].cap--;
            graph[pos][rev].cap++;
            pos = pa[pos];
        }
        ret++;
    }
    return ret;
}
 
int main(){
    scanf("%d %d %d",&n,&m,&c);
    for(int i=0; i<m; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        add_edge(2*s, 2*e-1, 1e9);
        add_edge(2*e, 2*s-1, 1e9);
    }
    for(int i=1; i<=n; i++){
        add_edge(2*i-1, 2*i, 1);
    }
    for(int i=1; i<=c; i++){
        int t;
        scanf("%d",&t);
        add_edge(2*t-1, 0, 1e9);
    }
    printf("%d",flow(2, 0));
}