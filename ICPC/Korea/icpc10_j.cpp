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

pi a[10005];
int dp[10005];

struct rmq{
    int tree[33000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        memset(tree, 0, sizeof(tree));
    }
    void add(int x, int v){
        x += lim;
        tree[x] = max(tree[x], v);
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x], tree[2*x+1]);
        }
    }
    int query(int s, int e){
        s += lim;
        e += lim;
        int ret = 0;
        while(s < e){
            if(s%2 == 1) ret = max(ret, tree[s++]);
            if(e%2 == 0) ret = max(ret, tree[e--]);
            s >>= 1;
            e >>= 1;    
        }
        if(s == e) ret = max(ret, tree[s]);
        return ret;
    }
}rmq;

int main(){
    int t, n;
    cin >> t;
    while(t--){
        vector<int> v;
        scanf("%d",&n);
        for(int i=0; i<n; i++){
            int t1, t2;
            char a, b;
            scanf("%d%c%d%c",&t1,&a,&t2,&b);
            int n1 = (a == 'W' ? -t1 : (3000000 + t1));
            int n2 = (b == 'W' ? t2 : (2000000 - t2));
            ::a[i] = pi(n1, n2);
            v.push_back(n2);
        }
        rmq.init(n);
        sort(v.begin(), v.end());
        for(int i=0; i<n; i++){
            a[i].second = lower_bound(v.begin(), v.end(), a[i].second) - v.begin() + 1;
        }
        sort(a, a+n);
        for(int i=0; i<n; i++){
            dp[i] = rmq.query(a[i].second + 1, n) + 1;
            rmq.add(a[i].second, dp[i]);
        }
        cout << *max_element(dp, dp+n) << endl;
    }
}