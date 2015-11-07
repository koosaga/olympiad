#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
 
struct edge{int pos, cap, rev;};
vector<edge> graph[2505];
 
void add_edge(int s, int e){
    graph[s].push_back({e,1,(int)graph[e].size()});
    graph[e].push_back({s,0,(int)graph[s].size()-1});
}
 
int match(int end){
    int res = 0;
    while (1) {
        int v[2505] = {}, pa[2505] = {}, pb[2505] = {};
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
 
int r[51][51], l[51][51], rs, ls;
 
int main(){
    int n,m;
    char str[51][51];
    scanf("%d %d",&n,&m);
    for (int i=0; i<n; i++) {
        scanf("%s",str[i]);
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if(str[i][j] == '*'){
                if(j == 0 || str[i][j-1] == '.') rs++;
                r[i][j] = rs;
            }
        }
    }
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if(str[j][i] == '*'){
                if(j == 0 || str[j-1][i] == '.') ls++;
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
            if(r[i][j]){
                add_edge(r[i][j],l[i][j] + rs);
            }
        }
    }
    printf("%d",match(rs+ls+1));
}