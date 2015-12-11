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
 
// perstree query -> [dfn, dfn + size - 1] 구간에서 dep이 어느정도 이하인 애들이 얼마인지
 
struct node{
    node *ls, *rs;
    int sum;
    node(){
        ls = rs = NULL;
        sum = 0;
    }
}*root[200005];
 
void init(int s, int e, node *p){
    if(s == e) return;
    p->ls = new node();
    p->rs = new node();
    int m = (s+e)/2;
    init(s, m, p->ls);
    init(m+1, e, p->rs);
}
 
void add(int pos, int ps, int pe, node *prev, node *cur){
    if(ps == pe){
        cur->sum = prev->sum + 1;
        return;
    }
    int pm = (ps + pe) / 2;
    if(pos <= pm){
        cur->ls = new node();
        cur->rs = prev->rs;
        add(pos, ps, pm, prev->ls, cur->ls);
    }
    else{
        cur->rs = new node();
        cur->ls = prev->ls;
        add(pos, pm+1, pe, prev->rs, cur->rs);
    }
    cur->sum = cur->ls->sum + cur->rs->sum;
}
 
int query(int s, int e, int ps, int pe, node *p){
    if(e < ps || pe < s) return 0;
    if(s <= ps && pe <= e) return p->sum;
    int pm = (ps + pe) / 2;
    return query(s, e, ps, pm, p->ls) + query(s, e, pm+1, pe, p->rs);
}
 
int n, dfn[200005], size[200005], piv;
lint l, dep[200005];
vector<pi> graph[200005];
 
vector<lint> v;
 
void dfs(int x){
    dfn[x] = ++piv;
    size[x] = 1;
    for(auto &i : graph[x]){
        dep[i.second] = dep[x] + i.first;
        dfs(i.second);
        size[x] += size[i.second];
    }
    v.push_back(dep[x]);
}
 
int main(){
    scanf("%d %lld",&n,&l);
    for(int i=2; i<=n; i++){
        int p;
        lint l;
        scanf("%d %lld",&p,&l);
        graph[p].push_back(pi(l, i));
    }
    dfs(1);
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    int sz = v.size();
    root[0] = new node();
    init(0, sz-1, root[0]);
    vector<pi> v2;
    for(int i=1; i<=n; i++){
        v2.push_back(pi(dfn[i], i));
    }
    sort(v2.begin(), v2.end());
    for(int i=0; i<n; i++){
        root[i+1] = new node();
        int lb = lower_bound(v.begin(), v.end(), dep[v2[i].second]) - v.begin();
        add(lb, 0, sz-1, root[i], root[i+1]);
    }
    for(int i=1; i<=n; i++){
        int s = lower_bound(v.begin(), v.end(), dep[i]) - v.begin();
        int p = lower_bound(v.begin(), v.end(), dep[i] + l + 1) - v.begin();
        printf("%d\n",query(s, p-1, 0, sz-1, root[dfn[i] + size[i] - 1]) - query(s, p-1, 0, sz-1, root[dfn[i] - 1]));
    }
}