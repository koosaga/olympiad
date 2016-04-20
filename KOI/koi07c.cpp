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
 
int n, m, k;
int a[305][305];
 
struct edg{
    int pos, cap, rev;
};
 
vector<edg> graph[605];
 
void add_edge(int s, int e){
    graph[s].push_back((edg){e, 1, (int)graph[e].size()});
    graph[e].push_back((edg){s, 0, (int)graph[s].size() - 1});
}
 
bool vis[605];
int pa[605], pe[605];
 
int dfs(int x){
    if(x == n + m + 1) return 1;
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
        int pos = n+m+1;
        while(pos){
            int rev = graph[pa[pos]][pe[pos]].rev;
            graph[pa[pos]][pe[pos]].cap--;
            graph[pos][rev].cap++;
            pos = pa[pos];
        }
        memset(vis,0,sizeof(vis));
        ret++;
    }
    memset(vis,0,sizeof(vis));
    return ret;
}
 
int trial(int x){
    for(int i=0; i<n+m+2; i++){
        graph[i].clear();
    }
    for(int i=1; i<=n; i++){
        add_edge(0, i);
    }
    for(int i=1; i<=m; i++){
        add_edge(i+n, n+m+1);
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(a[i][j] > x){
                add_edge(i, n+j);
            }
        }
    }
    return match();
}
 
int main(){
    scanf("%d %d %d",&n,&m,&k);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            scanf("%d",&a[i][j]);
        }
    }
    int s = 0, e = 500001;
    while(s != e){
        int m = (s+e)/2;
        if(trial(m) <= k) e = m;
        else s = m+1;
    }
    printf("%d\n",s);
    trial(s);
    dfs(0);
    vector<int> l, r;
    for(int i=1; i<=n; i++){
        if(!vis[i]) l.push_back(i);
    }
    for(int i=n+1; i<=n+m; i++){
        if(vis[i]) r.push_back(i-n);
    }
    int p = 1;
    while(l.size() + r.size() < k){
        while(vis[p] == 0) p++;
        l.push_back(p++);
    }
    sort(l.begin(), l.end());
    printf("%d",l.size());
    for(int i=0; i<l.size(); i++){
        printf(" %d",l[i]);
    }
    puts("");
    printf("%d",r.size());
    for(int i=0; i<r.size(); i++){
        printf(" %d",r[i]);
    }
}