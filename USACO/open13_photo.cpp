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
 
int n, m;
int s[100005], e[100005];
int stp[200005], edp[200005];
int dp[200005];
 
struct seg{
    int tree[530000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        fill(tree, tree + 2 * lim, -1e9);
    }
    void upd(int x, int v){
        x += lim;
        tree[x] = max(tree[x], v);
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x], tree[2*x+1]);
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        int ret = -1e9;
        while(s < e){
            if(s%2 == 1) ret = max(ret,tree[s++]);
            if(e%2 == 0) ret = max(ret,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = max(ret,tree[s]);
        return ret;
    }
}seg;
 
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<=n; i++) stp[i] = i;
    memset(edp, 0x3f, sizeof(edp));
    seg.init(n);
    for(int i=0; i<m; i++){
        scanf("%d %d",&s[i],&e[i]);
        stp[s[i]] = max(stp[s[i]], e[i]);
        edp[s[i]] = min(edp[s[i]], e[i]);
    }
    for(int i=1; i<=n; i++) stp[i] = max(stp[i-1], stp[i]);
    edp[n+1] = n+1;
    for(int i=n; i>=1; i--){
        edp[i] = min(edp[i], edp[i+1]);
    }
    seg.upd(n+1, 0);
    for(int i=n; i>=0; i--){
        dp[i] = seg.q(stp[i] + 1, edp[i+1]) + 1;
        seg.upd(i, dp[i]);
    }
    if(dp[0] < 0) puts("-1");
    else printf("%d",dp[0] - 1);
}