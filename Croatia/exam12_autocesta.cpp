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
 
struct seg{
    int s, e, x;
    bool operator<(const seg &a)const{
        return e < a.e;
    }
};
 
int n, must[100005];
lint cst[100005];
 
int m, s[100005], e[100005], c[100005];
vector<seg> segs;
 
void input(){
    int intv1[100005] = {}, intv2[100005] = {};
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%lld",&cst[i]);
        cst[i] += cst[i-1];
    }
    scanf("%d",&m);
    for(int i=0; i<m; i++){
        int s, e, c;
        scanf("%d %d %d",&s,&e,&c);
        if(s < e){
            intv1[s]++;
            intv1[e]--;
        }
        else{
            intv2[e]++;
            intv2[s]--;
        }
        if(s > e) swap(s, e);
        segs.push_back({s, e, c});
    }
    sort(segs.begin(), segs.end());
    for(int i=1; i<=n; i++){
        intv1[i] += intv1[i-1];
        intv2[i] += intv2[i-1];
    }
    int k;
    scanf("%d",&k);
    for(int i=0; i<n; i++){
        if(intv1[i] > k || intv2[i] > k){
            must[i] = 1;
        }
    }
}
 
lint dp[100005];
 
struct segtree{
    lint tree[270000], lazy[270000];
    void init(){
        memset(tree, 0x3f, sizeof(tree));
    }
    void lazydown(int p){
        tree[2*p] += lazy[p];
        tree[2*p+1] += lazy[p];
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        lazy[p] = 0;
    }
    void set(int pos, int s, int e, lint x, int p){
        if(s == e){
            lazy[p] = 0;
            tree[p] = x;
            return;
        }
        lazydown(p);
        int m = (s+e)/2;
        if(pos <= m) set(pos, s, m, x, 2*p);
        else set(pos, m+1, e, x, 2*p+1);
        tree[p] = min(tree[2*p], tree[2*p+1]);
    }
    void add(int s, int e, int ps, int pe, int p, lint v){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            tree[p] += v;
            lazy[p] += v;
            return;
        }
        int pm = (ps + pe) / 2;
        lazydown(p);
        add(s, e, ps, pm, 2*p, v);
        add(s, e, pm+1, pe, 2*p+1, v);
        tree[p] = min(tree[2*p], tree[2*p+1]);
    }
    lint query(int s, int e, int ps, int pe, int p){
        if(e < ps || pe < s) return 1e18;
        if(s <= ps && pe <= e) return tree[p];
        lazydown(p);
        int pm = (ps + pe) / 2;
        return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
    }
}seg;
 
struct bit{
    lint tree[105000];
    void add(int x, lint v){
        x += 2;
        while(x <= n+2){
            tree[x] += v;
            x += x & -x;
        }
    }
    lint sum(int x){
        x += 2;
        lint ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
}bit;
 
int main(){
    input();
    lint ret = 0;
    for(int i=0; i<m; i++){
        ret += segs[i].x;
    }
    int p = 0;
    seg.init();
    seg.set(0, 0, n, 0, 1);
    for(int i=1; i<=n; i++){
        while(p < m && segs[p].e <= i){
            bit.add(segs[p].s, segs[p].x);
            seg.add(segs[p].s+1, n, 0, n, 1, segs[p].x);
            p++;
        }
        dp[i] = seg.query(0, i-1, 0, n, 1) + cst[i] - bit.sum(i);
        if(!must[i-1]) dp[i] = min(dp[i], dp[i-1]);
        seg.set(i, 0, n, dp[i] - cst[i] + bit.sum(i-1), 1);
    }
    printf("%lld",ret + dp[n]);
}