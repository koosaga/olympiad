// remember! no guarantee for connected graph!

#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int,int> pi;

vector<int> graph[300005], rev[300005];
vector<int> dfn;
int comp[300005], piv, vis[300005];

vector<int> dag[300005];
pi seg[300005];

int n,m,a,b;
int x[300005], y[300005];
vector<int> endp;
vector<pi> print;

void dfs(int x){
    if(vis[x]) return;
    vis[x] = 1;
    for (int i=0; i<graph[x].size(); i++){
        dfs(graph[x][i]);
    }
    dfn.push_back(x);
}

void dfs2(int x, int p){
    if(vis[x]) return;
    vis[x] = 1;
    comp[x] = p;
    for (int i=0; i<rev[x].size(); i++){
        dfs2(rev[x][i],p);
    }
}

void input(){
    scanf("%d %d %d %d",&n,&m,&a,&b);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&x[i],&y[i]);
        if(x[i] == 0) print.push_back(pi(y[i],i));
    }
    for (int i=0; i<m; i++) {
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(e);
        rev[e].push_back(s);
        if(x == 2){
            graph[e].push_back(s);
            rev[s].push_back(e);
        }
    }
    for (int i=1; i<=n; i++) {
        if(!vis[i]) dfs(i);
    }
    memset(vis,0,sizeof(vis));
    for (int i=(int)dfn.size()-1; i>=0; i--) {
        if(!vis[dfn[i]]) dfs2(dfn[i],++piv);
    }
    for (int i=1; i<=piv; i++) {
        seg[i] = pi(1e9,-1e9);
    }
}

queue<int> q;

void make_end(){
    memset(vis,0,sizeof(vis));
    for (int i=0; i<print.size(); i++) {
        q.push(print[i].second);
        vis[print[i].second] = 1;
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i=0; i<graph[x].size(); i++) {
            if(!vis[graph[x][i]]){
                q.push(graph[x][i]);
                vis[graph[x][i]] = 1;
            }
        }
    }
    for (int i=1; i<=n; i++) {
        if(x[i] == a && vis[i]){
            endp.push_back(y[i]);
        }
    }
    sort(endp.begin(),endp.end());
}

int main(){
    input();
    make_end();
    sort(print.begin(),print.end());
    for (int i=1; i<=n; i++) {
        int pos = (int)(lower_bound(endp.begin(),endp.end(),y[i]) - endp.begin());
        if(x[i] == a && pos != endp.size() && endp[pos] == y[i]){
            seg[comp[i]].first = min(seg[comp[i]].first,pos);
            seg[comp[i]].second = max(seg[comp[i]].second,pos);
        }
        for (int j=0; j<graph[i].size(); j++) {
            if(comp[i] != comp[graph[i][j]]){
                dag[comp[i]].push_back(comp[graph[i][j]]);
            }
        }
    }
    for (int i=piv; i; i--) {
        for (int j=0; j<dag[i].size(); j++) {
            seg[i].first = min(seg[i].first,seg[dag[i][j]].first);
            seg[i].second = max(seg[i].second,seg[dag[i][j]].second);
        }
    }
    for (int i=(int)print.size()-1; i>=0; i--) {
        int pos = comp[print[i].second];
        printf("%d\n",max(0,seg[pos].second - seg[pos].first + 1));
    }
}