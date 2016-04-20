#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
using namespace std;
 
int n;
int x1[3005], y1[3005], x2[3005], y2[3005];
 
vector<int> graph[6005], rev[6005];
 
inline int NOT(int x){
    if(x >= 3*n) return x - 3*n;
    else return x + 3*n;
}
 
inline void add_edge(int x, int y){
    graph[x].push_back(y);
    rev[y].push_back(x);
    graph[NOT(y)].push_back(NOT(x));
    rev[NOT(x)].push_back(NOT(y));
}
 
inline int ccw(int a, int b, int c, int d, int e, int f){
    int dx1 = c - a, dy1 = d - b, dx2 = e - a, dy2 = f - b;
    return dx1 * dy2 > dy1 * dx2 ? 1 : -1;
}
 
inline bool cross(int i, int j){
    int p1 = ccw(x1[i],y1[i],x2[i],y2[i],x1[j],y1[j]) * ccw(x1[i],y1[i],x2[i],y2[i],x2[j],y2[j]);
    int p2 = ccw(x1[j],y1[j],x2[j],y2[j],x1[i],y1[i]) * ccw(x1[j],y1[j],x2[j],y2[j],x2[i],y2[i]);
    return p1 < 0 && p2 < 0;
}
 
vector<int> out;
 
int vis[6005];
int comp[6005], piv;
 
void dfs(int x){
    vis[x] = 1;
    for (int i=0; i<graph[x].size(); i++) {
        if(!vis[graph[x][i]]){
            dfs(graph[x][i]);
        }
    }
    out.push_back(x);
}
 
void rdfs(int x, int c){
    vis[x] = 1;
    comp[x] = c;
    for (int i=0; i<rev[x].size(); i++) {
        if(!vis[rev[x][i]]){
            rdfs(rev[x][i],c);
        }
    }
}
 
void scc(){
    for (int i=0; i<6*n; i++) {
        if(!vis[i]) dfs(i);
    }
    memset(vis,0,sizeof(vis));
    for (int i=(int)out.size()-1; i>=0; i--) {
        if(!vis[out[i]]) rdfs(out[i],++piv);
    }
    for (int i=0; i<3*n; i++) {
        if(comp[i] == comp[NOT(i)]){
            puts("-1");
            exit(0);
        }
    }
}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<3*n; i++) {
        scanf("%d %d %d %d",&x1[i],&y1[i],&x2[i],&y2[i]);
    }
    for (int i=0; i<n; i++) {
        add_edge(3*i,NOT(3*i+1));
        add_edge(3*i,NOT(3*i+2));
        add_edge(3*i+1,NOT(3*i));
        add_edge(3*i+1,NOT(3*i+2));
        add_edge(3*i+2,NOT(3*i));
        add_edge(3*i+2,NOT(3*i+1));
    }
    for (int i=0; i<3*n; i++) {
        for (int j=i+1; j<3*n; j++) {
            if(cross(i,j)) add_edge(NOT(i),j);
        }
    }
    scc();
    vector<int> ret;
    for (int i=0; i<3*n; i++) {
        if(comp[i] > comp[NOT(i)]){
            ret.push_back(i);
        }
    }
    printf("%d\n",ret.size());
    for (int i=0; i<ret.size(); i++) {
        printf("%d ",ret[i]+1);
    }
}