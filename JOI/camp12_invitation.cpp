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
 
struct node{
    int len, val, pos, place;
};
 
node maxv(node a, node b){
    if(a.val > b.val) return a;
    if(a.val < b.val) return b;
    if(a.place > b.place) return b;
    if(a.place < b.place) return a;
    if(a.pos > b.pos) return b;
    return a;
}
 
vector<int> vx, vy;
 
struct seg{
    node tree[530000];
    int lazy[530000];
    bool flag[530000];
    void init(int ps, int pe, int p, vector<int> &v, int flag){
        if(ps == pe){
            tree[p] = {v[ps+1] - v[ps], 0, ps, flag};
            return;
        }
        int pm = (ps + pe) / 2;
        init(ps, pm, 2*p, v, flag);
        init(pm+1, pe, 2*p+1, v, flag);
        tree[p] = maxv(tree[2*p], tree[2*p+1]);
    }
    void apply(int p, int ps, int v){
        if(tree[p].val == -1) return;
        if(tree[p].val <= v){
            if(tree[p].place == 1){
                tree[p] = {vx[ps+1] - vx[ps], v, ps, 1};
            }
            else{
                tree[p] = {vy[ps+1] - vy[ps], v, ps, 2};
            }
        }
        lazy[p] = max(lazy[p], v);
        flag[p] = 1;
    }
    void lazydown(int p, int ps, int pe){
        if(!flag[p]) return;
        int pm = (ps + pe) / 2;
        apply(2*p, ps, lazy[p]);
        apply(2*p+1, pm+1, lazy[p]);
        lazy[p] = 0;
        flag[p] = 0;
    }
    void add(int s, int e, int ps, int pe, int p, int v){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            apply(p, ps, v);
            return;
        }
        lazydown(p, ps, pe);
        int pm = (ps + pe) / 2;
        add(s, e, ps, pm, 2*p, v);
        add(s, e, pm+1, pe, 2*p+1, v);
        tree[p] = maxv(tree[2*p], tree[2*p+1]);
    }
    void erase(int pos, int ps, int pe, int p){
        if(ps == pe){
            tree[p].val = -1;
            lazy[p] = flag[p] = 0;
            return;
        }
        lazydown(p, ps, pe);
        int pm = (ps + pe) / 2;
        if(pos <= pm) erase(pos, ps, pm, 2*p);
        else erase(pos, pm+1, pe, 2*p+1);
        tree[p] = maxv(tree[2*p], tree[2*p+1]);
    }
}sega, segb;
 
int a, b, c, n;
int p[100005], q[100005], r[100005], s[100005], t[100005];
bool vis[100005];
 
struct seg2{
    set<pi> seg[200005];
    pi tree[530000];
    int lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
    }
    pi q(int s, int e){
        s += lim;
        e += lim;
        pi ret(0,0);
        while(s < e){
            if(s%2 == 1) ret = max(ret,tree[s++]);
            if(e%2 == 0) ret = max(ret,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = max(ret,tree[s]);
        return ret;
    }
    void add(int x, pi t){
        seg[x].insert(t);
        tree[x + lim] = *seg[x].rbegin();
        x += lim;
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x], tree[2*x+1]);
        }
    }
    void del(int x, pi t){
        seg[x].erase(t);
        if(seg[x].empty()) tree[x + lim] = pi(0,0);
        else tree[x + lim] = *seg[x].rbegin();
        x += lim;
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x], tree[2*x+1]);
        }
    }
}seg1, seg2;
  
int main(){
    scanf("%d %d %d %d",&a,&b,&c,&n);
    vx.push_back(1);
    vy.push_back(1);
    vx.push_back(a+1);
    vy.push_back(b+1);
    for(int i=0; i<n; i++){
        scanf("%d %d %d %d %d",&p[i],&q[i],&r[i],&s[i],&t[i]);
        vx.push_back(p[i]);
        vx.push_back(q[i]+1);
        vy.push_back(r[i]);
        vy.push_back(s[i]+1);
    }
    sort(vx.begin(), vx.end());
    sort(vy.begin(), vy.end());
    vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
    vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
    seg1.init(2*n+2);
    seg2.init(2*n+2);
    for(int i=0; i<n; i++){
        p[i] = (int)(lower_bound(vx.begin(), vx.end(), p[i]) - vx.begin()); 
        q[i] = (int)(lower_bound(vx.begin(), vx.end(), q[i]+1) - vx.begin());   
        r[i] = (int)(lower_bound(vy.begin(), vy.end(), r[i]) - vy.begin()); 
        s[i] = (int)(lower_bound(vy.begin(), vy.end(), s[i]+1) - vy.begin());
        seg1.add(p[i], pi(q[i], i));
        seg2.add(r[i], pi(s[i], i));    
    }
    sega.init(0, vx.size() - 2, 1, vx, 1);
    segb.init(0, vy.size() - 2, 1, vy, 2);
    c = (int)(upper_bound(vx.begin(), vx.end(), c) - vx.begin()) - 1;
    lint ret = -1;
    sega.add(c, c, 0, vx.size() - 2, 1, 1);
    for(int i=0; i<vx.size() + vy.size() - 2; i++){
        node cur = maxv(sega.tree[1], segb.tree[1]);
        if(cur.val <= 0){
            puts("-1");
            return 0;
        }
        ret += cur.val;
        int tp = cur.val;
        while(1){
            pi tmp;
            if(cur.place == 1) tmp = seg1.q(0, cur.pos);
            else tmp = seg2.q(0, cur.pos);
            if(tmp.first <= cur.pos) break;
            int pos = tmp.second;
            sega.add(p[pos], q[pos] - 1, 0, vx.size() - 2, 1, t[pos]);
            segb.add(r[pos], s[pos] - 1, 0, vy.size() - 2, 1, t[pos]);
            tp = max(tp, t[pos]);
            seg1.del(p[pos], pi(q[pos], pos));
            seg2.del(r[pos], pi(s[pos], pos));
        }
        ret += 1ll * tp * (cur.len - 1);
        if(cur.place == 1){
            sega.erase(cur.pos, 0, vx.size() - 2, 1);
        }
        else{
            segb.erase(cur.pos, 0, vy.size() - 2, 1);
        }
    }
    printf("%lld\n",ret);
}