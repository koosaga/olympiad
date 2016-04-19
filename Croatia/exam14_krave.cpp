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
 
struct node{
    node *ls, *rs;
    int minv;
    node(){
        ls = rs = NULL;
        minv = 1e9;
    }
};
 
void add(int pos, int s, int e, int x, node *p){
    p->minv = min(p->minv, x);
    if(s == e) return;
    int m = (s+e)/2;
    if(pos <= m){
        if(!p->ls) p->ls = new node();
        add(pos, s, m, x, p->ls);
    }
    else{
        if(!p->rs) p->rs = new node();
        add(pos, m+1, e, x, p->rs);
    }
}
 
int query(int s, int e, int ps, int pe, node *p){
    if(e < ps || pe < s || p == NULL) return 1e9;
    if(s <= ps && pe <= e) return p->minv;
    int pm = (ps + pe) / 2;
    return min(query(s, e, ps, pm, p->ls), query(s, e, pm+1, pe, p->rs));
}
 
int a, b;
int n, x[100005], y[100005], d[100005];
 
struct seg{
    node *tree[270000];
    int lim;
    void init(){
        for(lim = 1; lim <= a; lim <<= 1);
        for(int i=1; i<=2*lim; i++) tree[i] = new node();
        for(int i=1; i<=n; i++){
            int p = x[i] + lim;
            while(p){
                add(y[i], 1, b-1, i, tree[p]);
                p >>= 1;
            }
        }
    }
    int dquery(int sx, int ex, int sy, int ey){
        sx += lim;
        ex += lim;
        int ret = 1e9;
        while(sx < ex){
            if(sx%2 == 1) ret = min(ret, query(sy, ey, 1, b-1, tree[sx++]));
            if(ex%2 == 0) ret = min(ret, query(sy, ey, 1, b-1, tree[ex--]));
            sx >>= 1;
            ex >>= 1;
        }
        if(sx == ex) ret = min(ret, query(sy, ey, 1, b-1, tree[sx]));
        return ret;
    }
}seg;
 
lint r1[100005], r2[100005];
 
void solve(int sx, int ex, int sy, int ey){
    int t = seg.dquery(sx+1, ex-1, sy+1, ey-1);
    if(t > n) return;
    if(d[t] == 2){
        r1[t] = 1ll * (x[t] - sx) * (ey - sy);
        r2[t] = 1ll * (ex - x[t]) * (ey - sy);
        solve(sx, x[t], sy, ey);
        solve(x[t], ex, sy, ey);
    }
    else{
        r1[t] = 1ll * (ex - sx) * (y[t] - sy);
        r2[t] = 1ll * (ex - sx) * (ey - y[t]);
        solve(sx, ex, sy, y[t]);
        solve(sx, ex, y[t], ey);
    }
}
 
int main(){
    scanf("%d %d %d",&a,&b,&n);
    for(int i=1; i<=n; i++){
        scanf("%d %d %d",&x[i],&y[i],&d[i]);
    }
    seg.init();
    solve(0, a, 0, b);
    for(int i=1; i<=n; i++){
        printf("%lld %lld\n",min(r1[i], r2[i]), max(r1[i], r2[i]));
    }
}