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
 
struct trap{
    int pos, st, ed, val;
}a[200005];
 
vector<int> vx;
int n, k;
 
struct seg{
    lint tree[530000], lazy[530000];
    void lazydown(int p){
        tree[2*p] += lazy[p];
        tree[2*p+1] += lazy[p];
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        lazy[p] = 0;
    }
    void add(int s, int e, int ps, int pe, int p, int v){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            tree[p] += v;
            lazy[p] += v;
            return;
        }
        lazydown(p);
        int pm = (ps + pe) / 2;
        add(s, e, ps, pm, 2*p, v);
        add(s, e, pm+1, pe, 2*p+1, v);
        tree[p] = max(tree[2*p], tree[2*p+1]);
    }
}seg;
 
int main(){
    scanf("%d %d",&n,&k);
    for(int i=0; i<n; i++){
        int x, y, g;
        scanf("%d %d %d",&g,&x,&y);
        int t = x + y, u = x - y;
        vx.push_back(t - k);
        vx.push_back(t + k + 1);
        a[2*i] = {u - k, t - k, t + k + 1, g};
        a[2*i+1] = {u + k + 1, t - k, t + k + 1, -g};
    }
    sort(vx.begin(), vx.end());
    vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
    for(int i=0; i<n; i++){
        int t = lower_bound(vx.begin(), vx.end(), a[2*i].st) - vx.begin();
        int u = lower_bound(vx.begin(), vx.end(), a[2*i].ed) - vx.begin();
        a[2*i].st = a[2*i+1].st = t;
        a[2*i].ed = a[2*i+1].ed = u;
    }
    sort(a, a+2*n,[&](const trap &a, const trap &b){
        return a.pos < b.pos;
    });
    lint ret = 0;
    for(int i=0; i<2*n; i++){
        int e = i;
        while(e < 2*n && a[e].pos == a[i].pos){
            seg.add(a[e].st, a[e].ed - 1, 0, 2*n-1, 1, a[e].val);
            e++;
        }
        ret = max(ret, seg.tree[1]);
        i = e-1;
    }
    printf("%lld",ret);
}