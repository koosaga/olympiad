#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
  
struct edge{int pos, cap, rev;};
vector<edge> graph[1005];
  
void add_edge(int s, int e){
    graph[s].push_back({e,1,(int)graph[e].size()});
    graph[e].push_back({s,0,(int)graph[s].size()-1});
}
  
int match(int end){
    int res = 0;
    while (1) {
        int v[1005] = {}, pa[1005] = {}, pb[1005] = {};
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int t = q.front();
            q.pop();
            if(t == end) break;
            for (int i=0; i<graph[t].size(); i++) {
                edge x = graph[t][i];
                if(!v[x.pos] && x.cap > 0){
                    q.push(x.pos);
                    v[x.pos] = 1;
                    pa[x.pos] = t;
                    pb[x.pos] = i;
                }
            }
        }
        if(!v[end]) break;
        res++;
        for (int i=end; i; i = pa[i]) {
            int rev = graph[pa[i]][pb[i]].rev;
            graph[pa[i]][pb[i]].cap--;
            graph[i][rev].cap++;
        }
    }
    return res;
}
  
int main(){
    int n,m;
    char str[501][501]={};
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        str[x][y] = 1;
    }
    for (int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) if(str[i][j]) add_edge(i,n+j);
    }
    for (int i=1; i<=n; i++) {
        add_edge(0,i);
        add_edge(i+n,2*n+1);
    }
    printf("%d",match(2*n+1));
}