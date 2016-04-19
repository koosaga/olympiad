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
 
int l, n, d[105], c[105];
 
int m1, m2;
pi pt1[100005], pt2[100005];
vector<int> vx;
 
lint dp[1000005];
int bestguy = -1, p1 = 1e9, p2 = 1;
 
void init_dp(){
    for(int i=0; i<n; i++){
        if(1ll * p1 * d[i] > 1ll * p2 * c[i]){
            bestguy = i;
            p1 = c[i], p2 = d[i];
        }
        else if(d[i] < p1 && 1ll * p1 * d[i] == 1ll * p2 * c[i]){
            bestguy = i;
            p1 = c[i], p2 = d[i];
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for(int i=1; i<=1000000; i++){
        for(int j=0; j<n; j++){
            if(i >= d[j]) dp[i] = min(dp[i], dp[i - d[j]] + c[j]);
        }
    }
}
 
lint get_cost(int x){
    if(x > 1000000){
        int dx = (x - 1000001) / d[bestguy];
        dx++;
        return dp[x - dx * d[bestguy]] + 1ll * dx * c[bestguy];
    }
    return dp[x];
}
 
struct rmq{
    pi tree[270000];
    int lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        fill(tree, tree + 270000, pi(1e9, 1e9));
    }
    void add(int x, int v){
        x += lim;
        tree[x] = pi(v, x - lim);
        while(x > 1){
            x >>= 1; 
            tree[x] = min(tree[2*x], tree[2*x+1]);
        }
    }
    pi query(int s, int e){
        s += lim;
        e += lim;
        pi ret(1e9, 1e9);
        while(s < e){
            if(s%2 == 1) ret = min(ret, tree[s++]);
            if(e%2 == 0) ret = min(ret, tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = min(ret, tree[s]);
        return ret;
    }
}rmq;
 
const lint oo = 3e18;
 
lint gob(lint a, lint b){
    if(a == 0) return 0;
    if(oo / a <= b) return oo;
    return a * b;
}
 
pi dnc(int s, int e, int p){
    if(s > e) return pi(0, 0);
    pi m = rmq.query(s, e);
    pi t1 = dnc(s, m.second - 1, m.first);
    pi t2 = dnc(m.second + 1, e, m.first);
    lint tmp1 = gob((m.first - p), get_cost(vx[e+1] - vx[s]));
    lint tmp2 = gob(get_cost(m.first - p), (vx[e+1] - vx[s]));
    pi ret(t1.first + t2.first + tmp1, t1.second + t2.second + tmp2);
    ret.first = min(ret.first, oo);
    ret.second = min(ret.second, oo);
    return ret;
}
 
pi solve1(){
    rmq.init(vx.size());
    for(int i=0; i<m1; i+=2){
        for(int j=pt1[i].first; j<pt1[i+1].first; j++){
            rmq.add(j, pt1[i].second);
        }
    }
    return dnc(0, vx.size()-2, 0);
}
 
int up[100005], dn[100005];
 
pi solve2(){
    for(int i=0; i<m2; i+=2){
        fill(up + pt2[i].first, up + pt2[i+1].first, pt2[i].second);
    }
    for(int i=0; i<m1; i+=2){
        fill(dn + pt1[i].first, dn + pt1[i+1].first, pt1[i].second);
    }
    pi ret(0, 0);
    for(int i=0; i<vx.size()-1; i++){
        lint t1 = gob(vx[i+1] - vx[i], get_cost(up[i] - dn[i]));
        lint t2 = gob(up[i] - dn[i], get_cost(vx[i+1] - vx[i]));
        ret.first += t1;
        ret.second += t2;
        ret.first = min(ret.first, oo);
        ret.second = min(ret.second, oo);
    }
    return ret;
}
 
int main(){
    scanf("%d %d",&l,&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&d[i], &c[i]);
    }
    scanf("%d",&m1);
    for(int i=0; i<m1; i++){
        scanf("%d %d",&pt1[i].first, &pt1[i].second);
        vx.push_back(pt1[i].first);
    }
    scanf("%d",&m2);
    for(int i=0; i<m2; i++){
        scanf("%d %d",&pt2[i].first, &pt2[i].second);
        vx.push_back(pt2[i].first);
    }
    sort(vx.begin(), vx.end());
    vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
    for(int i=0; i<m1; i++){
        pt1[i].first = lower_bound(vx.begin(), vx.end(), pt1[i].first) - vx.begin();
    }
    for(int i=0; i<m2; i++){
        pt2[i].first = lower_bound(vx.begin(), vx.end(), pt2[i].first) - vx.begin();
    }
    init_dp();
    pi t1 = solve1(), t2 = solve2();
    printf("%lld",min(t1.first + t2.first, t1.second + t2.second));
}