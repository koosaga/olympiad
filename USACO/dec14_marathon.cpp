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
 
int x[100005], y[100005];
int sum[100005], pos[100005];
int n, q;
 
struct bit{
    int tree[270000], lim;
    int add(int a, int b){return a + b;}
    void init(int n, int *a){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=1; i<=n; i++){
            tree[i+lim] = a[i];
        }
        for(int i=lim; i; i--){
            tree[i] = add(tree[2*i], tree[2*i+1]);
        }
    }
    void upd(int x, int v){
        x += lim;
        tree[x] = v;
        while(x > 1){
            x >>= 1;
            tree[x] = add(tree[2*x], tree[2*x+1]);
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        int ret = 0;
        while(s < e){
            if(s%2 == 1) ret = add(ret,tree[s++]);
            if(e%2 == 0) ret = add(ret,tree[e--]);
            s >>= 1, e >>= 1;
        }
        if(s == e) ret = add(ret,tree[s]);
        return ret;
    }
}bit;
 
struct rmq{
    int tree[270000], lim;
    void init(int n, int *a){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=1; i<=n; i++){
            tree[i+lim] = a[i];
        }
        for(int i=lim; i; i--){
            tree[i] = max(tree[2*i], tree[2*i+1]);
        }
    }
    void upd(int x, int v){
        x += lim;
        tree[x] = v;
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x], tree[2*x+1]);
        }
    }
    int q(int s, int e){
        if(s > e) return 0;
        s += lim;
        e += lim;
        int ret = -1e9;
        while(s < e){
            if(s%2 == 1) ret = max(ret,tree[s++]);
            if(e%2 == 0) ret = max(ret,tree[e--]);
            s >>= 1, e >>= 1;
        }
        if(s == e) ret = max(ret,tree[s]);
        return ret;
    }
}rmq;
 
int main(){
    scanf("%d %d",&n,&q);
    for(int i=1; i<=n; i++){
        scanf("%d %d",&x[i],&y[i]);
    }
    for(int i=1; i<n; i++){
        sum[i] = abs(x[i] - x[i+1]) + abs(y[i] - y[i+1]);
    }
    for(int i=1; i<n-1; i++){
        pos[i] = sum[i] + sum[i+1] - (abs(x[i] - x[i+2]) + abs(y[i] - y[i+2]));
    }
    rmq.init(n-2, pos);
    bit.init(n-1, sum);
    while(q--){
        char t[5];
        scanf("%s",t);
        if(t[0] == 'Q'){
            int s, e;
            scanf("%d %d",&s,&e);
            printf("%d\n",bit.q(s, e-1) - rmq.q(s, e-2));
        }
        else{
            int i, a, b;
            scanf("%d %d %d",&i,&a,&b);
            x[i] = a, y[i] = b;
            if(i > 1){
                sum[i-1] = abs(x[i] - x[i-1]) + abs(y[i] - y[i-1]);
                bit.upd(i-1, sum[i-1]);
            }
            if(i < n){
                sum[i] = abs(x[i] - x[i+1]) + abs(y[i] - y[i+1]);
                bit.upd(i,sum[i]);
            }
            if(i > 2){
                pos[i-2] = sum[i-2] + sum[i-1] - (abs(x[i] - x[i-2]) + abs(y[i] - y[i-2]));
                rmq.upd(i-2, pos[i-2]);
            }
            if(i > 1 && i-1 <= n-2){
                pos[i-1] = sum[i-1] + sum[i] - (abs(x[i+1] - x[i-1]) + abs(y[i+1] - y[i-1]));
                rmq.upd(i-1, pos[i-1]);
            }
            if(i <= n-2){            
                pos[i] = sum[i] + sum[i+1] - abs(x[i] - x[i+2]) - abs(y[i] - y[i+2]);
                rmq.upd(i, pos[i]);
            }
        }
    }
}