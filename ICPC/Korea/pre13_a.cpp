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
const int oo = 1e9;

int n, q;

struct rect{
    int sx, ex, sy, ey, w, idx;
}a[100005];

struct line{
    int s, e, idx;
}vx[100005], vy[100005];

bool operator<(line a, line b){
    return a.s < b.s;
}

int rx[100005], ry[100005];
struct rmq{
    pi tree[270000];
    int lim;
    void init(int n){
        fill(tree, tree+270000, pi(-1e9, -1e9));
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void add(int x, pi v){
        x += lim;
        tree[x] = v;
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x], tree[2*x+1]);
        }
    }
    pi q(int s, int e){
        s += lim;
        e += lim;
        pi ret(-1e9,-1e9);
        while(s < e){
            if(s%2 == 1) ret = max(ret,tree[s++]);
            if(e%2 == 0) ret = max(ret,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = max(ret,tree[s]);
        return ret;
    }
    // {end coord, index}
}rmqx, rmqy;

void solve(){
    scanf("%*d %d %d",&n,&q);
    for(int i=0; i<n; i++){
        int sx, sy, ex, ey, w;
        scanf("%d %d %d %d %d",&sx,&sy,&ex,&ey,&w);
        if(sx > ex) swap(sx, ex);
        if(sy > ey) swap(sy, ey);
        a[i] = {sx, ex, sy, ey, w, i};
    }
    rmqx.init(n);
    rmqy.init(n);
    sort(a, a+n,[&](const rect &a, const rect &b){
        return a.sx < b.sx;
    });
    for(int i=0; i<n; i++){
        vx[i] = {a[i].sx, a[i].ex, a[i].idx};
        rmqx.add(i, pi(a[i].ex, a[i].idx));
        rx[a[i].idx] = i;
    }
    sort(a, a+n,[&](const rect &a, const rect &b){
        return a.sy < b.sy;
    });
    for(int i=0; i<n; i++){
        vy[i] = {a[i].sy, a[i].ey, a[i].idx};
        rmqy.add(i, pi(a[i].ey, a[i].idx));
        ry[a[i].idx] = i;
    }
    sort(a, a+n, [&](const rect &a, const rect &b){
        return a.idx < b.idx;
    });
    while(q--){
        int p, b;
        scanf("%d %d",&p,&b);
        int ret = 0;
        if(b == 1){
            int lbnd = lower_bound(vx, vx + n, (line){p+1, -oo, -oo}) - vx;
            while(1){
                pi t = rmqx.q(0, lbnd - 1);
                if(t.second < 0) break;
                if(t.first < p) break;
                ret = max(ret, a[t.second].w);
                rmqx.add(rx[t.second], pi(-1e9, -1e9));
                rmqy.add(ry[t.second], pi(-1e9, -1e9));
            }
        }
        else{
            int lbnd = lower_bound(vy, vy + n, (line){p+1, -oo, -oo}) - vy;
            while(1){
                pi t = rmqy.q(0, lbnd - 1);
                if(t.second < 0) break;
                if(t.first < p) break;
                ret = max(ret, a[t.second].w);
                rmqx.add(rx[t.second], pi(-1e9, -1e9));
                rmqy.add(ry[t.second], pi(-1e9, -1e9));
            }
        }
        printf("%d\n",ret);
    }
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--) solve();
}