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
 
int n, a[500005];
 
struct rmq{
    int tree[1050000], lim;
    void init(int n, int *a){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=1; i<=n; i++){
            tree[i+lim] = a[i];
        }
        for(int i=lim; i; i--){
            tree[i] = max(tree[2*i], tree[2*i+1]);
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        int ret = 0;
        while(s < e){
            if(s%2 == 1) ret = max(ret,tree[s++]);
            if(e%2 == 0) ret = max(ret,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = max(ret,tree[s]);
        return ret;
    }
}rmq;
 
pi tmp[500005];
 
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        tmp[i] = pi(a[i], i);
    }
    sort(tmp+1, tmp+n+1);
    lint ret = 0;
    rmq.init(n, a);
    for(int i=1; i<=n; i++){
        if(rmq.q(1, i) > a[i]) ret++;
        if(rmq.q(i+1, n) > a[i]) ret++;
    }
    for(int i=1; i<=n; ){
        int e = i;
        while(e <= n && tmp[e].first == tmp[i].first) e++;
        int lpos = i;
        for(int j=i+1; j<e; j++){
            if(rmq.q(tmp[lpos].second, tmp[j].second) > tmp[j].first){
                lpos = j;
            }
            ret += j - lpos;
        }
        i = e;
    }
    printf("%lld",ret);
}