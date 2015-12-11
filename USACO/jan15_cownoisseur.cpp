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
 
vector<int> graph[100005], rev[100005];
int n, m;
 
bool vis[100005];
vector<int> dfn;
int comp[100005], csize[100005], piv;
 
void dfs(int x){
    if(vis[x]) return;
    vis[x] = 1;
    for(auto &i : graph[x]){
        dfs(i);
    }
    dfn.push_back(x);
}
 
void rdfs(int x, int p){
    if(vis[x]) return;
    vis[x] = 1;
    comp[x] = p;
    csize[p]++;
    for(auto &i : rev[x]){
        rdfs(i, p);
    }
}
 
vector<int> dag[100005], rdag[100005];
int dp1[100005], dp2[100005];
 
int f1(int x){
    if(x == comp[1]) return csize[x];
    if(~dp1[x]) return dp1[x];
    int ret = -1e9;
    for(auto &i : dag[x]){
        ret = max(ret, f1(i));
    }
    return dp1[x] = ret + csize[x];
}
 
int f2(int x){
    if(x == comp[1]) return csize[x];
    if(~dp2[x]) return dp2[x];
    int ret = -1e9;
    for(auto &i : rdag[x]){
        ret = max(ret, f2(i));
    }
    return dp2[x] = ret + csize[x];
}
 
int main(){
    memset(dp1,-1,sizeof(dp1));
    memset(dp2,-1,sizeof(dp2));
    scanf("%d %d",&n,&m);
    for(int i=0; i<m; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        graph[s].push_back(e);
        rev[e].push_back(s);
    }
    for(int i=1; i<=n; i++){
        if(!vis[i]){
            dfs(i);
        }
    }
    memset(vis,0,sizeof(vis));
    reverse(dfn.begin(), dfn.end());
    for(auto &i : dfn){
        if(!vis[i]){
            rdfs(i, ++piv);
        }
    }
    for(int i=1; i<=n; i++){
        for(auto &j : graph[i]){
            if(comp[i] != comp[j]){
                dag[comp[i]].push_back(comp[j]);
                rdag[comp[j]].push_back(comp[i]);
            }
        }
    }
    int ret = 0;
    for(int i=1; i<=n; i++){
        for(auto &j : graph[i]){
            ret = max(ret, f1(comp[i]) + f2(comp[j]) - csize[comp[1]]);
        }
    }
    printf("%d",ret);
}