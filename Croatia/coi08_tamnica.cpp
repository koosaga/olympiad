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
 
lint n, k;
 
int getsqrt(lint x){
    int t = (int)sqrt(x);
    while(1ll * (t+1) * (t+1) <= x) t++;
    return t;
}
 
lint f(lint x){
    int t = getsqrt(x-1);
    if(t%2 == 0) t--;
    return x - 4 * t + 3 - 2 * ((x - 1 - 1ll * t * t) / (t + 1));
}
 
vector<pi> edg;
vector<lint> v;
vector<pi> graph[200005];
bool vis[200005];
 
lint dijkstra(){
    priority_queue<pi, vector<pi>, greater<pi> > pq;
    pq.push(pi(0, 0));
    while(!pq.empty()){
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        if(v[t.second] == n) return t.first;
        for(auto &i : graph[t.second]){
            pq.push(pi(i.first + t.first, i.second));
        }
    }
    return 1e18;
}
 
int main(){
    cin >> n >> k;
    while(k--){
        lint b;
        scanf("%lld",&b);
        edg.push_back(pi(f(b), b));
    }
    for(auto &i : edg){
        v.push_back(i.first);
        v.push_back(i.second);
    }
    v.push_back(1);
    v.push_back(n);
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    for(auto &i : edg){
        int s = lower_bound(v.begin(), v.end(), i.first) - v.begin();
        int e = lower_bound(v.begin(), v.end(), i.second) - v.begin();
        graph[s].push_back(pi(1, e));
        graph[e].push_back(pi(1, s));
    }
    for(int i=1; i<v.size(); i++){
        graph[i].push_back(pi(v[i] - v[i-1], i-1));
        graph[i-1].push_back(pi(v[i] - v[i-1], i));
    }
    printf("%lld",dijkstra());
}
