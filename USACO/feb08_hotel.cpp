#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct seg{
    int ltree[135000], rtree[135000], tree[135000];
    int lazy[135000];
    void init(int n){
        memset(lazy,-1,sizeof(lazy));
        lazy[1] = 0;
        tree[1] = ltree[1] = rtree[1] = n;
    }
    void lazydown(int p, int ps, int pe){
        if(lazy[p] == -1) return;
        lazy[2*p] = lazy[p];
        lazy[2*p+1] = lazy[p];
        int pm = (ps+pe)/2;
        if(lazy[p] == 0){
            tree[2*p] = ltree[2*p] = rtree[2*p] = (pm - ps + 1);
            tree[2*p+1] = ltree[2*p+1] = rtree[2*p+1] = (pe - pm);
        }
        else{
            tree[2*p] = ltree[2*p] = rtree[2*p] = 0;
            tree[2*p+1] = ltree[2*p+1] = rtree[2*p+1] = 0;
        }
        lazy[p] = -1;
    }
    int get_pos(int ps, int pe, int p, int len){
        if(ps == pe){
            if(tree[p] >= len) return ps;
            return -1;
        }
        lazydown(p,ps,pe);
        int pm = (ps+pe)/2;
        if(tree[2*p] >= len){
            return get_pos(ps,pm,2*p,len);
        }
        int ret = rtree[2*p] + ltree[2*p+1];
        if(ret >= len) return pm + 1 - rtree[2*p];
        return get_pos(pm+1,pe,2*p+1,len);
    }
    void fill(int s, int e, int ps, int pe, int p, int v){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            lazy[p] = v;
            if(v == 0){
                tree[p] = ltree[p] = rtree[p] = (pe - ps + 1);
            }
            else{
                tree[p] = ltree[p] = rtree[p] = 0;
            }
            return;
        }
        int pm = (ps+pe)/2;
        lazydown(p,ps,pe);
        fill(s,e,ps,pm,2*p,v);
        fill(s,e,pm+1,pe,2*p+1,v);
        ltree[p] = ltree[2*p];
        if(ltree[2*p] == (pm + 1 - ps)) ltree[p] += ltree[2*p+1];
        rtree[p] = rtree[2*p+1];
        if(rtree[2*p+1] == (pe - pm)) rtree[p] += rtree[2*p];
        tree[p] = max(tree[2*p],tree[2*p+1]);
        tree[p] = max(tree[p],rtree[2*p] + ltree[2*p+1]);
    }
}seg;

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    seg.init(n);
    while (m--) {
        int t;
        scanf("%d",&t);
        if(t == 1){
            int u;
            scanf("%d",&u);
            int q = seg.get_pos(1,n,1,u);
            if(~q){
                printf("%d\n",q);
                seg.fill(q,q+u-1,1,n,1,1);
            }
            else puts("0");
        }
        else{
            int s,u;
            scanf("%d %d",&s,&u);
            seg.fill(s,s+u-1,1,n,1,0);
        }
    }
}