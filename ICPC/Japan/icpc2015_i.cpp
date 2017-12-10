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

int n, m, c[44], ret = 1e9;
vector<int> graph[44];

int par[44], vis[44];

void dfs(int x){
    if(x == n){
        bool mark[44] = {};
        for(int i=n; i; i=par[i]){
            for(auto &j : graph[i]){
                mark[j] = 1;
            }
        }
        int cret = 0;
        for(int i=1; i<=n; i++){
            if(mark[i]) cret += c[i];
        }
        ret = min(ret, cret);
        return;
    }
    for(auto &i : graph[x]){
        vis[i]++;
    }
    for(auto &i : graph[x]){
        if(vis[i] == 1){
            par[i] = x;
            dfs(i);
        }
    }
    for(auto &i : graph[x]){
        vis[i]--;
    }
}

int main(){
    cin >> n >> m;
    for(int i=1; i<=n; i++) cin >> c[i];
    for(int i=0; i<m; i++){
        int s, e;
        cin >> s >> e;
        graph[s].push_back(e);
        graph[e].push_back(s);
    }
    vis[1] = 1;
    dfs(1);
    cout << ret;
}