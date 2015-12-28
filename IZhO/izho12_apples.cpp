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
    node *ls, *rs;
    int sum, lazy;
    node(){
        ls = rs = NULL;
        sum = lazy = 0;
    }
}*root;
 
void lazydown(node *p, int ps, int pe){
    if(!p->ls) p->ls = new node();
    if(!p->rs) p->rs = new node();
    if(p->lazy == 0) return;
    int pm = (ps+pe)/2;
    p->ls->lazy = 1;
    p->rs->lazy = 1;
    p->ls->sum = pm - ps + 1;
    p->rs->sum = pe - pm;
    p->lazy = 0;
}
 
void add(int s, int e, int ps, int pe, node *p){
    if(e < ps || pe < s) return;
    if(s <= ps && pe <= e){
        p->sum = pe - ps + 1;
        p->lazy = 1;
        return;
    }
    lazydown(p,ps,pe);
    int pm = (ps + pe) / 2;
    add(s, e, ps, pm, p->ls);
    add(s, e, pm+1, pe, p->rs);
    p->sum = p->ls->sum + p->rs->sum;
}
 
int sum(int s, int e, int ps, int pe, node *p){
    if(e < ps || pe < s) return 0;
    if(s <= ps && pe <= e) return p->sum;
    lazydown(p,ps,pe);
    int pm = (ps + pe) / 2;
    return sum(s, e, ps, pm, p->ls) + sum(s, e, pm+1, pe, p->rs);
}
 
int main(){
    int q;
    scanf("%d",&q);
    int c = 0;
    root = new node();
    while(q--){
        int s, e, x;
        scanf("%d %d %d",&x,&s,&e);
        s += c;
        e += c;
        if(x == 1){
            c = sum(s, e, 1, 1e9, root);
            printf("%d\n",c);
        }
        else add(s, e, 1, 1e9, root);
    }
}