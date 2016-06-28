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
#define cpp(b) for(int ii=0; ii<b.size(); ii++){ int i = b[ii];

int n, m, q;
int s[200005], e[200005];

vector<int> graph[100005];
int dist[100005], vis[100005];

int mark[200005], indeg[100005];
vector<int> dag[100005];
bool dis[100005];

set<pi> st;

int cnt;

void fill(int x){
    queue<int> q;
    q.push(x);
    while(!q.empty()){
        int x = q.front();
        q.pop();
        if(dis[x] == 0) cnt++;
        dis[x] = 1;
        cpp(dag[x])
            if(st.find(pi(x, i)) != st.end()) continue;
            st.insert(pi(x, i));
            indeg[i]--;
            if(indeg[i] == 0){
                q.push(i);
            }
        }
    }
}

void solve(){
    while(q--){
        int t;
        scanf("%d",&t);
        t--;
        if(mark[t] && st.find(pi(s[t], e[t])) == st.end()){
            st.insert(pi(s[t], e[t]));
            indeg[e[t]]--;
            if(indeg[e[t]] == 0){
                fill(e[t]);
            }
        }
        printf("%d\n",cnt);
    }
}

int main(){
    scanf("%d %d %d",&n,&m,&q);
    for(int i=0; i<m; i++){
        scanf("%d %d",&s[i],&e[i]);
        graph[s[i]].push_back(e[i]);
        graph[e[i]].push_back(s[i]);
    }
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while(!q.empty()){
        int t = q.front();
        q.pop();
        cpp(graph[t])
            if(!vis[i]){
                vis[i] = 1;
                dist[i] = dist[t] + 1;
                q.push(i);
            }
        }
    }
    for(int i=0; i<m; i++){
        if(dist[s[i]] == dist[e[i]] + 1){
            swap(s[i], e[i]);
        }
        if(dist[s[i]] + 1 == dist[e[i]]){
            dag[s[i]].push_back(e[i]);
            indeg[e[i]]++;
            mark[i] = 1;
        }
    }
    for(int i=1; i<=n; i++){
        sort(dag[i].begin(), dag[i].end());
    }
    solve();
}