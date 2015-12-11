#include <cstdio>
#include <algorithm>
using namespace std;
const int oo = 1e9;
 
struct node{long long l, r, lr, x;};
 
node add(node a, node b){
    node c;
    if(a.x == 0){
        c = b;
        return c;
    }
    if(b.x == 0){
        c = a;
        return c;
    }
    c.l = max(a.lr + b.x, a.l + b.l);
    c.r = max(a.x + b.lr, a.r + b.r);
    c.lr = max(a.l + b.lr, a.lr + b.r);
    c.l = max(c.l, c.lr);
    c.r = max(c.r, c.lr);
    c.x = max(a.r + b.x, a.x + b.l);
    c.x = max(c.x, max(c.l,c.r));
    return c;
}
 
struct seg{
    node tree[132000];
    int lim;
    void init(int n, int *a){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=1; i<=n; i++){
            tree[i + lim] = {0,0,0,a[i]};
        }
        for(int i=lim; i; i--){
            tree[i] = add(tree[2*i],tree[2*i+1]);
        }
    }
    void upd(int x, int v){
        x += lim;
        tree[x].l = tree[x].r = tree[x].lr = 0;
        tree[x].x = v;
        while(x > 1){
            x >>= 1;
            tree[x] = add(tree[2*x],tree[2*x+1]);
        }
    }
}seg;
 
int n, d, a[40005];
 
int main(){
    scanf("%d %d",&n,&d);
    for(int i=1; i<=n; i++) scanf("%d",&a[i]);
    seg.init(n,a);  
    long long ret = 0;
    while(d--){
        int pos, val;
        scanf("%d %d",&pos,&val);
        seg.upd(pos,val);
        ret += seg.tree[1].x;
    //  printf("%d\n",seg.tree[1].x);
    }
    printf("%lld",ret);
}