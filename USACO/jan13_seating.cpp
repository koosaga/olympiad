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
 
struct node{
    int lmax, rmax, pmax, size;
    int lazydown;
}tree[1050000];
 
node merge(node a, node b){
    node c;
    if(a.lmax == a.size){
        c.lmax = a.size + b.lmax;
    }
    else c.lmax = a.lmax;
    if(b.rmax == b.size){
        c.rmax = b.size + a.rmax;
    }
    else c.rmax = b.rmax;
    c.size = a.size + b.size;
    c.pmax = max(a.pmax, b.pmax);
    c.pmax = max(c.pmax, max(c.lmax, c.rmax));
    c.pmax = max(c.pmax, a.rmax + b.lmax);
    c.lazydown = 0;
    return c;
}
 
void lazydown(int p){
    if(tree[p].lazydown == -1){
        tree[2*p] = {0, 0, 0, tree[2*p].size, -1};
        tree[2*p+1] = {0, 0, 0, tree[2*p+1].size, -1};
    }
    else if(tree[p].lazydown == 1){
        tree[2*p] = {tree[2*p].size, tree[2*p].size, tree[2*p].size, tree[2*p].size, 1};
        tree[2*p+1] = {tree[2*p+1].size, tree[2*p+1].size, tree[2*p+1].size, tree[2*p+1].size, 1};
    }
    tree[p].lazydown = 0;
}
 
void init(int s, int e, int p){
    if(s == e){
        tree[p] = {1, 1, 1, 1, 0};
        return;
    }
    int m = (s+e)/2;
    init(s, m, 2*p);
    init(m+1, e, 2*p+1);
    tree[p] = merge(tree[2*p], tree[2*p+1]);
}
 
void erase(int s, int e, int ps, int pe, int p){
    if(e < ps || pe < s) return;
    if(s <= ps && pe <= e){
        tree[p] = {pe - ps + 1, pe - ps + 1, pe - ps + 1, pe - ps + 1, 1};
        return;
    }
    lazydown(p);
    int pm = (ps + pe) / 2;
    erase(s, e, ps, pm, 2*p);
    erase(s, e, pm+1, pe, 2*p+1);
    tree[p] = merge(tree[2*p], tree[2*p+1]);
}
 
void fill(int s, int e, int ps, int pe, int p){
    if(e < ps || pe < s) return;
    if(s <= ps && pe <= e){
        tree[p] = {0, 0, 0, pe - ps + 1, -1};
        return;
    }
    lazydown(p);
    int pm = (ps + pe) / 2;
    fill(s, e, ps, pm, 2*p);
    fill(s, e, pm+1, pe, 2*p+1);
    tree[p] = merge(tree[2*p], tree[2*p+1]);   
}
 
int search(int ps, int pe, int p, int k){
    if(ps == pe) return ps;
    int pm = (ps + pe) / 2;
    lazydown(p);
    if(tree[2*p].pmax >= k){
        return search(ps, pm, 2*p, k);
    }
    else if(tree[2*p].rmax + tree[2*p+1].lmax >= k){
        return pm + 1 - tree[2*p].rmax;
    }
    else{
        return search(pm+1, pe, 2*p+1, k);
    }
}
 
int main(){
    int n, q;
    scanf("%d %d",&n,&q);
    init(1, n, 1);
    int ret = 0;
    while(q--){
        char str[5];
        scanf("%s",str);
        if(str[0] == 'A'){
            int t;
            scanf("%d",&t);
            if(tree[1].pmax < t) ret++;
            else{
                int p = search(1, n, 1, t);
                fill(p, p+t-1, 1, n, 1);
            }
        }
        else{
            int s, e;
            scanf("%d %d",&s,&e);
            erase(s, e, 1, n, 1);
        }
    }
    printf("%d",ret);
}