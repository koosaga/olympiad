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
const int maxp = 100000;
const int mod = 10009;
  
int ipow(int x, int p){
    int ret = 1, piv = x % mod;
    while(p){
        if(p&1) ret *= piv;
        piv *= piv;
        ret %= mod;
        piv %= mod;
        p >>= 1;
    }
    return ret;
}
  
int n, k;
int xmax[100005], ymax[100005];
int dpx[100005][33], dpy[100005][33];
int fact[35], bino[100005][35];
 
int main(){
    scanf("%d %d",&n,&k);
    for(int i=0; i<n; i++){
        int v, r;
        scanf("%d %d",&v,&r);
        --v; --r;
        xmax[v] = max(xmax[v], r);
        ymax[r] = max(ymax[r], v);
    }
    fact[0] = 1;
    for(int i=1; i<=k; i++){
        fact[i] = fact[i-1] * i % mod;
    }
    for(int i=maxp-1; i>=0; i--){
        xmax[i] = max(xmax[i], xmax[i+1]);
        ymax[i] = max(ymax[i], ymax[i+1]);
    }
    for(int i=0; i<=maxp; i++){
        bino[i][0] = 1;
        for(int j=1; j<=min(k, i); j++){
            bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]) % mod;
        }
    }
    for(int i=maxp; i>=0; i--){
        dpx[i][0] = 1;
        dpy[i][0] = 1;
        for(int j=1; j<=k; j++){
            dpx[i][j] = dpx[i+1][j] + dpx[i+1][j-1] * max(0, xmax[i] + 1 - j);
            dpy[i][j] = dpy[i+1][j] + dpy[i+1][j-1] * max(0, ymax[i] + 1 - j);
            dpx[i][j] %= mod;
            dpy[i][j] %= mod;
        }
    }
    int q;
    scanf("%d",&q);
    while(q--){
        int x, y;
        scanf("%d %d",&x, &y);
        x--, y--;
        if(xmax[x] >= y){
            printf("%d\n",dpx[1][k]);
        }
        else{
            int ret = 0;
            for(int i=0; i<=k; i++){
                for(int j=0; i+j<=k; j++){
                    int t1 = (x >= j ? bino[x-j][k-i-j] : 0) * (y >= i ? bino[y-i][k-i-j] : 0) % mod;
                    ret += 1ll * (dpx[x+1][i] * dpy[y+1][j] % mod) * (t1 * fact[k-i-j] % mod) % mod;
                    ret %= mod;
                }
            }
            printf("%d\n",ret);
        }
    }
}