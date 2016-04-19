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
 
vector<int> graph[5005];
int n, k, p, occu[5005], mark[5005], par[5005];
 
vector<int> v;
 
int bfs(int x){
    queue<int> que, dist;
    que.push(x);
    dist.push(0);
    int ret = 0;
    while(!que.empty()){
        x = que.front();
        int d = dist.front();
        que.pop();
        dist.pop();
        if(!mark[x] && !occu[x]){
            occu[x] = 1;
            ret += d;
            break;
        }
        for(auto &i : graph[x]){
            if(i == p) continue;
            que.push(i);
            dist.push(d+1);
        }
    }
    if(ret == 0) return 1e4;
    return ret;
}
 
int main(){
    cin >> n >> p >> k;
    for(int i=1; i<=n; i++){
        int t;
        cin >> t;
        graph[i].resize(t);
        for(int j=0; j<t; j++){
            cin >> graph[i][j];
            par[graph[i][j]] = i;
        }
    }
    while(k--){
        int x;
        cin >> x;
        occu[x] = 1;
    }
    for(int i=p; i!=1; i=par[i]){
        mark[i] = 1;
        if(occu[i]) v.push_back(i);
    }
    int ret = 0;
    for(auto &i : v){
        int t = bfs(i);
        if(t >= 1e4){
            cout << "ne postoji";
            return 0;
        }
        ret += t;
    }
    cout << ret;
}