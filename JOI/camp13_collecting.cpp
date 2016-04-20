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
 
int n, q;
 
struct seg{
    int tree[1<<21];
    int cnts[20];
    void init(){
        for(int i=0; i<n; i++){
            cnts[i] = (1<<i);
        }
    }
    void flip(int x){
        x |= (1<<n);
        tree[x] ^= 1;
        for(int dep = n-1; dep >= 0; dep--){
            x >>= 1;
            if(tree[x] == (1 << (n - dep)) || tree[x] == 0){
                cnts[dep]--; //
            }
            tree[x] = tree[2*x] + tree[2*x+1];
            if(tree[x] == (1 << (n - dep)) || tree[x] == 0){
                cnts[dep]++;
            }
        }
    }
}px, py;
 
int main(){
    scanf("%d %d",&n,&q);
    px.init();
    py.init();
    for(int i=0; i<q; i++){
        int t, p;
        scanf("%d %d",&t, &p);
        p--;
        if(t) px.flip(p);
        else py.flip(p);
        lint ret = 0;
        for(int i=0; i<n; i++){
            int rcnt = (1 << (n - i - 1));
            ret += 1ll * rcnt * rcnt - 1ll * px.cnts[n-1-i] * py.cnts[n-1-i];
        }
        printf("%lld\n",ret * 4 + 1);
    }
}
