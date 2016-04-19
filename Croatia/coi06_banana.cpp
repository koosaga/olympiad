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
const int mod = 1e9 + 7;
 
struct edg{
    int pos, cur, lim;
};
 
int n, k;
vector<edg> graph[100005];
 
int dep[100005], mdep[100005];
 
void dfs1(int x, int p){
    mdep[x] = dep[x];
    for(auto &i : graph[x]){
        if(i.pos == p) continue;
        dep[i.pos] = dep[x] + i.cur;
        dfs1(i.pos, x);
        mdep[x] = max(mdep[i.pos], mdep[x]);
    }
}
 
int limit;
 
int dfs2(int x, int p, int e){
    if(limit < dep[x] - e) return k + 1;
    int ret = 0;
    for(auto &i : graph[x]){
        if(i.pos == p) continue;
        int dx = max(mdep[i.pos] - e - limit, 0);
        dx = min(dx, i.cur - i.lim);
        ret += dfs2(i.pos, x, e + dx) + dx;
        ret = min(ret, k+1);
    }
    return ret;
}
 
bool trial(int x){
    limit = x;
    return dfs2(1, 0, 0) <= k;
}
 
int main(){
    cin >> n >> k;
    for(int i=0; i<n-1; i++){
        int s, e, x, y;
        scanf("%d %d %d %d",&s,&e,&x,&y);
        graph[s].push_back({e, x, y});
        graph[e].push_back({s, x, y});
    }
    dfs1(1, 0);
    int s = 0, e = 1e9;
    while(s != e){
        int m = (s+e)/2;
        if(trial(m)) e = m;
        else s = m+1;
    }
    cout << s;
}