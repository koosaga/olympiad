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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
vector<pi> graph[100005];
int n, m;
 
int d1[100005], d2[100005];
 
void dijkstra(int* dist, int s){
    memset(dist, 0x3f, sizeof(&dist));
    dist[s] = 0;
    bool vis[100005] = {};
    priority_queue<pi, vector<pi>, greater<pi> > pq;
    pq.push(pi(0, s));
    while(!pq.empty()){
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        dist[t.second] = t.first;
        for(auto &i : graph[t.second]){
            pq.push(pi(i.first + t.first, i.second));
        }
    }
}
 
vector<pi> cl;
int dfn[100005], low[100005], piv;
 
void dfs(int x, int p){
    dfn[x] = low[x] = ++piv;
    for(auto &i : graph[x]){
        if(i.second == p) continue;
        if(!dfn[i.second]){
            dfs(i.second, x);
            low[x] = min(low[x], low[i.second]);
        }
        else{
            low[x] = min(low[x], dfn[i.second]);
        }
        if(low[i.second] > dfn[x]){
            cl.push_back(pi(i.second, x));
        }
    }
}
 
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<m; i++){
        int s, e, x;
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(pi(x, e));
        graph[e].push_back(pi(x, s));
    }
    int t1, t2;
    scanf("%d %d",&t1, &t2);
    dijkstra(d1, t1);
    dijkstra(d2, t2);
    dfs(1, 0);
    int ret = 1e9;
    for(auto &i : cl){
        ret = min(ret, max(d1[i.first], d2[i.second]));
        ret = min(ret, max(d1[i.second], d2[i.first]));
    }
    cout << ret;
}