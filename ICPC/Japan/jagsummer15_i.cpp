#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
 
struct s1{
    int t, p, f;
}a[4005];
 
int n, m;
lint dp[4005][4005];
 
struct cht{
    vector<pi> v;
    int p;
    lint query(int x){
        if(v.empty()) return -1e13;
        while(p+1 < v.size() && v[p].first * x + v[p].second < v[p+1].first * x + v[p+1].second) p++;
        return v[p].first * x + v[p].second;
    }
    bool chk(pi a, pi b, pi c){
        return 1ll * (b.first - a.first) * (b.second - c.second) < (c.first - b.first) * (a.second - b.second);
    }
    void add(int x, lint y){
        if(!v.empty() && v.back().first == x){
            if(v.back().second > y) return;
            v.pop_back();
        }
        while(v.size() >= p + 2 && chk(v[v.size()-2], v.back(), pi(x, y))){
            v.pop_back();
        }
        v.emplace_back(x, y);
    }
}cht[4005];
 
int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        cin >> a[i].t >> a[i].p >> a[i].f;
    }
    sort(a, a+n, [&](const s1 &a, const s1 &b){
        return a.f < b.f;
    });
    lint ret = 0;
    for(int i=0; i<n; i++){
        for(int j=1; j<=m; j++){
            dp[i][j] = -1e13;
            if(j < a[i].t) continue;
            if(j == a[i].t){
                dp[i][j] = a[i].p;
                continue;
            }
            dp[i][j] = cht[j - a[i].t].query(2 * a[i].f);
            dp[i][j] += a[i].p - a[i].f * a[i].f;
        }
        for(int j=1; j<=m; j++){
            ret = max(ret, dp[i][j]);
            cht[j].add(a[i].f, dp[i][j] - a[i].f * a[i].f);
        }
    }
    cout << ret << endl;
}