#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> pi;
 
struct disj{
    int pa[50005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p;
        return 1;
    }
}disj;
 
int n, m;
int s[100005], e[100005];
int out[100005];
 
vector<pi> graph[50005];
bool vis[50005];
 
int dfs(int x){
    int ret = 0;
    vis[x] = 1;
    for(int i=0; i<graph[x].size(); i++){
        if(vis[graph[x][i].second]) continue;
        if(dfs(graph[x][i].second)){
            ret++;
            out[graph[x][i].first] = 1;
        }
    }
    return (ret % 2 == graph[x].size() % 2);
}
 
int main(){
    scanf("%d %d",&n,&m);
    disj.init(n);
    for(int i=0; i<m; i++){
        scanf("%d %d",&s[i],&e[i]);
        if(!disj.uni(s[i], e[i])) out[i] = 1;
        else{
            graph[s[i]].push_back(pi(i, e[i]));
            graph[e[i]].push_back(pi(i, s[i]));
        }
    }
    for(int i=1; i<=n; i++){
        if(!vis[i] && dfs(i)){
            puts("-1");
            return 0;
        }
    }
    printf("%d\n",count(out, out + m, 0));
    for(int i=0; i<m; i++){
        if(out[i] == 0) printf("%d\n",i+1);
    }
}