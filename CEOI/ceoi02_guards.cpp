#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
  
struct edge{int pos, cap, rev;};
vector<edge> graph[50005];
 int r[205][205], l[205][205], rs, ls;
int a[205][205], n, m;
 
void add_edge(int s, int e){
    graph[s].push_back({e,1,(int)graph[e].size()});
    graph[e].push_back({s,0,(int)graph[s].size()-1});
}
 
bool vis[50005];
vector<int> dfn;
int pa[50005], pe[50005];
 
bool dfs(int x){
    if(x == ls+rs+1) return 1;
    if(vis[x]) return 0;
    vis[x] = 1;
    dfn.push_back(x);
    int p = 0;
    for(auto &i : graph[x]){
        if(i.cap > 0 && dfs(i.pos)){
            pa[i.pos] = x;
            pe[i.pos] = p++;
            return 1;
        }
        p++;
    }
    return 0;
}
 
int match(int end){
    int res = 0;
    while (1) {
        while(!dfn.empty()){
            vis[dfn.back()] = 0;
            dfn.pop_back();
        }
        if(!dfs(0)) break;
        res++;
        for (int i=end; i; i = pa[i]) {
            int rev = graph[pa[i]][pe[i]].rev;
            graph[pa[i]][pe[i]].cap--;
            graph[i][rev].cap++;
        }
    }
    return res;
}
   
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            scanf("%d",&a[i][j]);
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if(a[i][j] != 2){
                if(j == 0 || a[i][j-1] == 2) rs++;
                r[i][j] = rs;
            }
        }
    }
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if(a[j][i] != 2){
                if(j == 0 || a[j-1][i] == 2) ls++;
                l[j][i] = ls;
            }
        }
    }
    for (int i=1; i<=rs; i++) {
        add_edge(0,i);
    }
    for (int i=1; i<=ls; i++) {
        add_edge(rs+i,rs+ls+1);
    }
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++) {
            if(a[i][j] == 0){
                add_edge(r[i][j],l[i][j] + rs);
            }
        }
    }
    printf("%d\n",match(rs+ls+1));
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++) {
            if(a[i][j] == 0){
                for(auto &k : graph[r[i][j]]){
                    if(k.cap == 0 && k.pos == l[i][j] + rs){
                        printf("%d %d\n",i+1, j+1);
                    }
                }
            }
        }
    }
}