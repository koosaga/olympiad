#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
 
int n;
vector<int> graph[100005];
vector<int> bycol[100005];
int dfn[100005], piv;
int par[100005][17];
int cut[100005], dep[100005];
map<pi, int> mp;
 
bool cmp(int i, int j){
    return dfn[i] < dfn[j];
}
 
void dfs(int x, int pa){
    dfn[x] = ++piv;
    par[x][0] = pa;
    for(int i=1; i<17; i++){
        par[x][i] = par[par[x][i-1]][i-1];
    }
    for(int i=0; i<graph[x].size(); i++){
        if(graph[x][i] == pa) continue;
        dep[graph[x][i]] = dep[x] + 1;
        dfs(graph[x][i], x);
    }
}
 
void input(){
    scanf("%d",&n);
    n -= 2;
    for(int i=1; i<=n; i++){
        int a, b, c, col;
        scanf("%d %d %d %d",&a,&b,&c,&col);
        bycol[col].push_back(i);
        pi t1(a,b), t2(b,c), t3(c,a);
        if(t1.first > t1.second) swap(t1.first, t1.second);
        if(t2.first > t2.second) swap(t2.first, t2.second);
        if(t3.first > t3.second) swap(t3.first, t3.second);
        if(mp.find(t1) != mp.end()){
            graph[mp[t1]].push_back(i);
            graph[i].push_back(mp[t1]);
        }
        else mp[t1] = i;
        if(mp.find(t2) != mp.end()){
            graph[mp[t2]].push_back(i);
            graph[i].push_back(mp[t2]);
        }
        else mp[t2] = i;
        if(mp.find(t3) != mp.end()){
            graph[mp[t3]].push_back(i);
            graph[i].push_back(mp[t3]);
        }
        else mp[t3] = i;
    }
}
 
void paint(int s, int e){
    cut[s]++;
    cut[e]++;
    if(dep[s] > dep[e]) swap(s,e);
    int dx = dep[e] - dep[s];
    for(int i=0; i<17; i++){
        if((dx >> i) & 1) e = par[e][i];
    }
    for(int i=16; i>=0; i--){
        if(par[s][i] != par[e][i]){
            s = par[s][i];
            e = par[e][i];
        }
    }
    if(s != e) s = par[s][0];
    cut[s]-=2;
}
 
void dfs2(int x, int pa){
    for(int i=0; i<graph[x].size(); i++){
        if(graph[x][i] == pa) continue;
        dfs2(graph[x][i], x);
        cut[x] += cut[graph[x][i]];
    }
}
 
int main(){
    input();
    dfs(1,0);
    for(int i=1; i<=n+2; i++){
        sort(bycol[i].begin(), bycol[i].end(), cmp);
        for(int j=1; j<bycol[i].size(); j++){
            paint(bycol[i][j-1], bycol[i][j]);
        }
    }
    dfs2(1,0);
    int ret = 0;
    for(int i=2; i<=n; i++){
        if(!cut[i]) ret++;
    }
    printf("%d",ret);
}