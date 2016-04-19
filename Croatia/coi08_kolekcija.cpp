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

int k, n;
int a[300005];
vector<int> v;

int dp[300005], tra[300005];

vector<pi> intv;

struct rmq{
    pi tree[1050000];
    int lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        fill(tree, tree + 2 * lim, pi(1e9, 1e9));
    }
    void upd(int x, pi v){
        x += lim;
        tree[x] = v;
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
}seg1, seg2;

int main(){
    scanf("%*d %d %d",&k,&n);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
        v.push_back(a[i]);
    }
    v.push_back(0);
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    seg1.init(v.size());
    seg2.init(v.size());
    seg1.upd(0, pi(k, 0));
    seg2.upd(0, pi(- v[1] + 1, 0));
    for(int i=1; i<v.size(); i++){
        // dp[i] = dp[j] + k
        // dp[i] = dp[j] + v[i] - v[j+1] + 1 
        // v[i] - v[j+1] + 1 <= k
        // v[i] + 1 - k <= v[j+1]
        int l = lower_bound(v.begin(), v.end(), v[i] - k + 1) - v.begin() - 1;
        pi tmp1 = seg1.query(l, i-1);
        pi tmp2 = seg2.query(0, l-1);
        tmp2.first += v[i];
        if(tmp1 < tmp2){
            dp[i] = tmp1.first;
            tra[i] = tmp1.second;
        }
        else{
            dp[i] = tmp2.first;
            tra[i] = tmp2.second;
        }
        seg1.upd(i, pi(dp[i] + k, i));
        seg2.upd(i, pi(dp[i] - v[i+1] + 1, i));
    }
    printf("%d\n",dp[v.size()-1]);
    int p = v.size() - 1;
    while(p > 0){
        int st = min(v[tra[p] + 1], v[p] - k + 1), ed = v[p];
        if(st <= 0) ed += (-st + 1), st += (-st + 1);
        //printf("%d %d\n",st,ed);
        intv.push_back(pi(st, ed));
        p = tra[p];
    }
    reverse(intv.begin(), intv.end());
    for(int i=0; i<n; i++){
        auto low = --upper_bound(intv.begin(), intv.end(), pi(a[i],2e9));
        int st = max(a[i] - k + 1, low->first);
        printf("%d %d\n",st, st + k - 1);
    }
}
