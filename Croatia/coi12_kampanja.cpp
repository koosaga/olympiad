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
typedef pair<lint, lint> pi;
 
int adj[105][105];
int n, m;
 
struct edg{
    int x, y, v;
    bool operator<(const edg &q)const{
        return v > q.v;
    }
};
 
priority_queue<edg> pq;
 
bool vis[105][105];
 
int main(){
    scanf("%d %d",&n,&m);
    memset(adj, 0x3f, sizeof(adj));
    for(int i=0; i<m; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        adj[s][e] = 1;
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
            }
        }
    }
    pq.push({1, 1, 1});
    while(!pq.empty()){
        edg t = pq.top();
        pq.pop();
        if(vis[t.x][t.y]) continue;
        vis[t.x][t.y] = 1;
        if(t.x == 2 && t.y == 2){
            printf("%d\n",t.v);
            return 0;
        }
        if(!vis[t.y][t.x]){
            pq.push({t.y, t.x, t.v + adj[t.x][t.y] - 1});
        }
        for(int k=1; k<=n; k++){
            pq.push({k, t.y, t.v + adj[t.x][k] - (t.y == k)});
            pq.push({t.x, k, t.v + adj[k][t.y] - (t.x == k)});
        }
    }
}