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
int a[505][2];
 
set<int> s;
 
pi pa[505][505];
int pe[505][505];
int dep[505][505];
bool vis[505][505];
 
struct edg{
    int x, y, l;
};
 
queue<pi> q;
vector<edg> graph[505][505];
 
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d %d",&a[i][0], &a[i][1]);
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            for(int k=0; k<2; k++){
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
        for(auto &e : graph[qf.first][qf.second]){
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
            printf("%c",cmds[i] + 'A');
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
    bool vis[505] = {};
    int pa2[505], pe2[505];
    while(!q.empty()){
        int qf = q.front();
        q.pop();
        if(qf == 1){
            break;
        }
        for(int i=0; i<2; i++){
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
        printf("%c",rev[i] + 'A');
    }
}