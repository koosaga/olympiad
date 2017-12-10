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
 
vector<int> grp[100005], gph[100005];
int c[100005], cache[100005];
int r[100005];
int n, m;
 
vector<int> lis[100005];
 
struct disj{
    int pa[100005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x :find(pa[x]));
    }
    void uni(int p, int q){
        pa[find(p)] = find(q);
    }
}disj;
 
void solve(){
    cin >> n;
    for(int i=1; i<=n; i++){
        scanf("%d",&c[i]);
    }
    cin >> m;
    for(int i=0; i<m; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        gph[s].push_back(e);
        gph[e].push_back(s);
    }
    disj.init(n);
    for(int i=1; i<=n; i++){
        sort(gph[i].begin(), gph[i].end(), [&](const int &a, const int &b){
            return c[a] < c[b];
        });
        for(int j=0; j<gph[i].size(); j++){
            if(c[i] == c[gph[i][j]]) disj.uni(i, gph[i][j]);
            if(j && c[gph[i][j]] == c[gph[i][j-1]]) disj.uni(gph[i][j], gph[i][j-1]);
        }
    }
    for(int i=1; i<=n; i++){
        lis[c[i]].push_back(i);
        grp[disj.find(i)].push_back(i);
    }
    for(int i=1; i<=100000; i++){
        map<int, int> mp;
        for(auto &j : lis[i]){
            int ret = cache[j];
            for(auto &k : gph[j]){
                ret = max(ret, cache[k]);
            }
            mp[disj.find(j)] = max(mp[disj.find(j)], ret + 1);
        }
        for(auto &j : lis[i]){
            r[j] = mp[disj.find(j)];
        }
        for(auto &j : lis[i]){
            cache[j] = max(cache[j], r[j]);
            for(auto &k : gph[j]){
                cache[k] = max(cache[k], r[j]);
            }
        }
    }
    lint ret = 0;
    for(int i=1; i<=n; i++){
        ret += r[disj.find(i)];
    }
    cout << ret << endl;
}
 
int main(){
        solve();
}
