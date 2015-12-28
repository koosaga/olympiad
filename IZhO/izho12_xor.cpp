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
 
int n, x;
 
struct node{
    node *ls, *rs;
    int minv;
    node(){
        ls = rs = NULL;
        minv = 1e9;
    }
}*root;
 
void add(node *p, int pos, int val, int dep){
    if(dep == -1){
        p->minv = min(p->minv, val);
        return;
    }
    if(!p->ls) p->ls = new node();
    if(!p->rs) p->rs = new node();
    if((pos >> dep) % 2 == 0){
        add(p->ls, pos, val, dep-1);
    }
    if((pos >> dep) % 2 == 1){
        add(p->rs, pos, val, dep-1);
    }
    p->minv = min(p->ls->minv, p->rs->minv);
}
 
int query(node *p, int pos, int dep){
    if(dep == -1) return p->minv;
    if(!p->ls) p->ls = new node();
    if(!p->rs) p->rs = new node();
    bool b1 = (pos >> dep) & 1, b2 = (x >> dep) & 1;
    if(!b1 && !b2) return min(p->rs->minv, query(p->ls, pos, dep-1));
    if(b1 && !b2) return min(p->ls->minv, query(p->rs, pos, dep-1));
    if(!b1 && b2) return query(p->rs, pos, dep-1);
    if(b1 && b2) return query(p->ls, pos, dep-1);
}
 
int main(){
    root = new node();
    cin >> n >> x;
    add(root, 0, 0, 29);
    int pxor = 0;
    int ret = 0, retp = 0;
    for(int i=1; i<=n; i++){
        add(root, pxor, i-1, 29);
        int t;
        scanf("%d",&t);
        pxor ^= t;
        int tmp = i - query(root, pxor, 29);
        if(ret < tmp){
            ret = tmp;
            retp = i;
        }
    }
    cout << retp - ret + 1 << " " << ret;
}