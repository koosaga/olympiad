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
 
lint fact[300005];
int n, q, a[300005];
 
struct node{
    int ls, rs;
    int sum, cnt;
}tree[8000005];
int piv;
 
void init(int s, int e, int p){
    if(s == e) return;
    tree[p].ls = ++piv;
    tree[p].rs = ++piv;
    int m = (s+e)/2;
    init(s, m, tree[p].ls);
    init(m+1, e, tree[p].rs);
}
 
void add(int pos, int ps, int pe, int prev, int cur, lint v){
    if(ps == pe){
        tree[cur].sum = (tree[prev].sum + v) % mod;
        tree[cur].cnt = tree[prev].cnt + 1;
        return;
    }
    int pm = (ps + pe) / 2;
    if(pos <= pm){
        tree[cur].ls = ++piv;
        tree[cur].rs = tree[prev].rs;
        add(pos, ps, pm, tree[prev].ls, tree[cur].ls, v);
    }
    else{
        tree[cur].ls = tree[prev].ls;
        tree[cur].rs = ++piv;
        add(pos, pm+1, pe, tree[prev].rs, tree[cur].rs, v);
    }
    tree[cur].sum = (tree[tree[cur].ls].sum + tree[tree[cur].rs].sum) % mod;
    tree[cur].cnt = tree[tree[cur].ls].cnt + tree[tree[cur].rs].cnt;
}
 
int sum(int s, int e, int ps, int pe, int p){
    if(e < ps || pe < s) return 0;
    if(s <= ps && pe <= e) return tree[p].sum;
    int pm = (ps + pe) / 2;
    return (sum(s, e, ps, pm, tree[p].ls) + sum(s, e, pm+1, pe, tree[p].rs)) % mod;
}
 
int cnt(int s, int e, int ps, int pe, int p){
    if(e < ps || pe < s) return 0;
    if(s <= ps && pe <= e) return tree[p].cnt;
    int pm = (ps + pe) / 2;
    return (cnt(s, e, ps, pm, tree[p].ls) + cnt(s, e, pm+1, pe, tree[p].rs)) % mod;
}
 
int main(){
    fact[0] = 1;
    scanf("%d %d",&n,&q);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        fact[i] = fact[i-1] * i % mod;
    }
    lint rnk = 1;
    piv = n+1;
    init(1, n, n+1);
    for(int i=n; i; i--){
        add(a[i], 1, n, i+1, i, fact[n-i]);
        rnk += fact[n-i] * cnt(1, a[i]-1, 1, n, i);
        rnk %= mod;
    }
    for(int i=1; i<=q; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        lint tmp = 0;
        if(a[s] < a[e]){
            tmp += fact[n-s] * cnt(a[s]+1, a[e], 1, n, s+1) % mod;
            tmp += (mod - fact[n-e]) * cnt(a[s]+1, a[e], 1, n, e+1) % mod;
            tmp += sum(a[s]+1, a[e]-1, 1, n, s+1) - sum(a[s]+1, a[e]-1, 1, n, e) + mod;
            tmp %= mod;
            printf("%lld\n",(rnk + tmp) % mod);
        }
        if(a[s] > a[e]){
            tmp += (mod - fact[n-s]) * cnt(a[e], a[s]-1, 1, n, s+1);
            tmp += fact[n-e] * cnt(a[e], a[s]-1, 1, n, e+1);
            tmp += mod - sum(a[e]+1, a[s]-1, 1, n, s+1) + sum(a[e]+1, a[s]-1, 1, n, e);
            tmp %= mod;
            printf("%lld\n",(rnk + tmp) % mod);
        }
    }
}