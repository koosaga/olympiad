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
 
struct seg1{
    int tree[270000], lazy[270000];
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
        tree[p] = min(tree[2*p], tree[2*p+1]);
    }
}seg1, seg2;
 
int main(){
    int q;
    scanf("%d",&q);
    for(int i=0; i<q; i++){
        int a, b;
        scanf("%d %d",&b,&a);
        if(a == 1) seg1.add(1, b, 1, q, 1, 1), seg2.add(1, b, 1, q, 1, -1);
        else seg1.add(1, b, 1, q, 1, -1), seg2.add(1, b, 1, q, 1, 1);
        if(seg1.tree[1] >= 0){
            puts(">");
        }
        else if(seg2.tree[1] >= 0){
            puts("<");
        }
        else puts("?");
    }
}