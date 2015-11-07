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
 
int n, m;
int a[205][205];
 
set<int> s;
 
pi pa[205][205];
int pe[205][205];
int dep[205][205];
bool vis[205][205];
 
struct edg{
    int x, y, l;
};
 
queue<pi> q;
vector<edg> graph[205][205];
 
int main(){
    scanf("%d %d",&n,&m);
    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            scanf("%d",&a[j][i]);
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=m; k++){
                graph[a[i][k]][a[j][k]].push_back((edg){i, j, k});
            }
        }
    }
    for(int j=1; j<=n; j++){
        s.insert(j);
        vis[j][j] = 1;
        q.push(pi(j, j));
    }
    while(!q.empty()){
        pi qf = q.front();
        q.pop();
        for(int i=0; i<graph[qf.first][qf.second].size(); i++){
            edg e = graph[qf.first][qf.second][i];
            if(vis[e.x][e.y]) continue;
            vis[e.x][e.y] = 1;
            dep[e.x][e.y] = dep[qf.first][qf.second] + 1;
            pa[e.x][e.y] = qf;
            pe[e.x][e.y] = e.l;
            q.push(pi(e.x, e.y));
        }
    }
    while(s.size() > 1){
        int front1 = *s.begin();
        s.erase(s.begin());
        int front2 = *s.begin();
        s.erase(s.begin());
        vector<int> cmds, v;
        pi cur = pi(front1, front2);
        while(dep[cur.first][cur.second]){
            cmds.push_back(pe[cur.first][cur.second]);
            cur = pa[cur.first][cur.second];
        }
        while(!s.empty()){
            v.push_back(*s.begin());
            s.erase(s.begin());
        }
        s.insert(cur.first);
        for(int i=0; i<cmds.size(); i++){
            printf("%d\n",cmds[i]);
            for(int j=0; j<v.size(); j++){
                v[j] = a[v[j]][cmds[i]];
            }
        }
        for(int i=0; i<v.size(); i++){
            s.insert(v[i]);
        }
    }
    int pk = *s.begin();
    queue<int> q;
    q.push(pk);
    bool vis[205] = {};
    int pa2[205], pe2[205];
    while(!q.empty()){
        int qf = q.front();
        q.pop();
        if(qf == 1){
            break;
        }
        for(int i=1; i<=m; i++){
            if(!vis[a[qf][i]]){
                vis[a[qf][i]] = 1;
                pa2[a[qf][i]] = qf;
                pe2[a[qf][i]] = i;
                q.push(a[qf][i]);
            }
        }
    }
    vector<int> rev;
    int pos = 1;
    while(pos != pk){
        rev.push_back(pe2[pos]);
        pos = pa2[pos];
    }
    reverse(rev.begin(), rev.end());
    for(int i=0; i<rev.size(); i++){
        printf("%d\n",rev[i]);
    }
}