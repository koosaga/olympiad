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
 
int k, n, r1, r2;
pi a[200005];
 
vector<int> vx, vy;
 
struct rmq{
    int tree[132000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        memset(tree, 0x3f, sizeof(tree));
    }
    void add(int x, int v){
        x += lim;
        tree[x] = min(tree[x], v);
        while(x > 1){
            x >>= 1;
            tree[x] = min(tree[2*x], tree[2*x+1]);
        }
    }
    int query(int s, int e){
        s += lim;
        e += lim;
        int ret = 1e9;
        while(s < e){
            if(s%2 == 1) ret = min(ret, tree[s++]);
            if(e%2 == 0) ret = min(ret, tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = min(ret, tree[s]);
        return ret;
    }
}qx1, qx2, qy1, qy2;
 
struct rtree{
    vector<pi> tree[132000];
    int lim;
    void init(int n, pi *a){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=1; i<=n; i++){
            for(int j=lim + a[i].first; j; j>>=1){
                tree[j].push_back(pi(a[i].second, i));
            }
        }
        for(int i=1; i<=2*lim; i++){
            sort(tree[i].begin(), tree[i].end());
        }
    }
    int find(vector<pi> &v, int s, int e){
        auto t = lower_bound(v.begin(), v.end(), pi(s, -1e9));
        if(t == v.end() || t->first > e) return -1;
        return t->second;
    }
    int query(int sx, int ex, int sy, int ey){
        sx += lim;
        ex += lim;
        int r = -1;
        while(sx < ex){
            if(sx%2 == 1){
                int t = find(tree[sx++], sy, ey);
                if(t != -1) return t;
            }
            if(ex%2 == 0){
                int t = find(tree[ex--], sy, ey);
                if(t != -1) return t;
            }
            sx >>= 1;
            ex >>= 1;
        }
        if(sx == ex){
            int t = find(tree[sx++], sy, ey);
            if(t != -1) return t;
        }
        return -1;
    }
}rtree;
 
bool trial(int x){
    if(k == 1){
        int minx = vx.front() + x;
        int miny = vy.front() + x;
        int maxx = vx.back() - x;
        int maxy = vy.back() - x;
        for(int i=1; i<=n; i++){
            if(maxx <= vx[a[i].first] && vx[a[i].first] <= minx
                && maxy <= vy[a[i].second] && vy[a[i].second] <= miny){
                r1 = i;
                return 1;
            }
        }
        return 0;
    }
    else{
        for(int i=1; i<=n; i++){
            int sx = lower_bound(vx.begin(), vx.end(), vx[a[i].first] - x) - vx.begin();
            int ex = upper_bound(vx.begin(), vx.end(), vx[a[i].first] + x) - vx.begin();
            int sy = lower_bound(vy.begin(), vy.end(), vy[a[i].second] - x) - vy.begin();
            int ey = upper_bound(vy.begin(), vy.end(), vy[a[i].second] + x) - vy.begin();
            int minx = min(qy1.query(0, sy-1), qy1.query(ey, n-1));
            int maxx = -min(qy2.query(0, sy-1), qy2.query(ey, n-1));
            if(sx) minx = min(minx, 0), maxx = max(maxx, sx-1);
            if(ex < vx.size()) minx = min(minx, ex), maxx = max(maxx, (int)vx.size()-1);
            int miny = min(qx1.query(0, sx-1), qx1.query(ex, n-1));
            int maxy = -min(qx2.query(0, sx-1), qx2.query(ex, n-1));
            if(sy) miny = min(miny, 0), maxy = max(maxy, sy-1);
            if(ey < vy.size()) miny = min(miny, ey), maxy = max(maxy, (int)vy.size()-1);
            minx = min(minx, (int)vx.size() - 1);
            maxx = max(maxx, 0);
            miny = min(miny, (int)vy.size() - 1);
            maxy = max(maxy, 0);
            tie(minx, maxx) = pi(vx[maxx] - x, vx[minx] + x);
            tie(miny, maxy) = pi(vy[maxy] - x, vy[miny] + x);
            minx = lower_bound(vx.begin(), vx.end(), minx) - vx.begin();
            maxx = upper_bound(vx.begin(), vx.end(), maxx) - vx.begin() - 1;
            miny = lower_bound(vy.begin(), vy.end(), miny) - vy.begin();
            maxy = upper_bound(vy.begin(), vy.end(), maxy) - vy.begin() - 1;
            int t = rtree.query(minx, maxx, miny, maxy);
            if(t != -1){
                r1 = i, r2 = t;
                return 1;
            }
        }
        return 0;
    }
}
 
int main(){
    scanf("%d %d",&k,&n);
    for(int i=1; i<=n; i++){
        int x, y;
        scanf("%d %d",&x, &y);
        a[i] = pi(x+y, x-y);
        vx.push_back(a[i].first);
        vy.push_back(a[i].second);
    }
    sort(vx.begin(), vx.end());
    sort(vy.begin(), vy.end());
    vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
    vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
    for(int i=1; i<=n; i++){
        a[i].first = lower_bound(vx.begin(), vx.end(), a[i].first) - vx.begin();
        a[i].second = lower_bound(vy.begin(), vy.end(), a[i].second) - vy.begin();
    }
    if(k > 1){
        rtree.init(n, a);
        qx1.init(n);
        qy1.init(n);
        qx2.init(n);
        qy2.init(n);
        for(int i=1; i<=n; i++){
            qx1.add(a[i].first, a[i].second);
            qx2.add(a[i].first, -a[i].second);
            qy1.add(a[i].second, a[i].first);
            qy2.add(a[i].second, -a[i].first);
        }
    }
    int s = 0, e = 2e6;
    while(s != e){
        int m = (s+e)/2;
        if(trial(m)) e = m;
        else s = m+1;
    }
    trial(s);
    if(k == 1) printf("%d\n%d",s, r1);
    else printf("%d\n%d %d",s, r1, r2);
}