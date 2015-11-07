#include <cstdio>
 
struct seg{
    int tree[270000], lazy[270000];
    void flip(int ps, int pe, int p){
        tree[p] = pe - ps + 1 - tree[p];
        lazy[p] ^= 1;
    }
    void mod(int s, int e, int ps, int pe, int p){
        if(pe < s || e < ps) return;
        else if(s <= ps && pe <= e){
            flip(ps,pe,p);
            return;
        }
        int pm = (ps+pe)/2;
        if(lazy[p]){
            lazy[p] = 0;
            flip(ps,pm,p<<1);
            flip(pm+1,pe,p<<1|1);
        }
        mod(s,e,ps,pm,p<<1);
        mod(s,e,pm+1,pe,p<<1|1);
        tree[p] = tree[p<<1] + tree[p<<1|1];
    }
    int sum(int s, int e, int ps, int pe, int p){
        if(s <= ps && pe <= e) return tree[p];
        else if(pe < s || e < ps) return 0;
        int pm = (ps+pe)/2;
        if(lazy[p]){
            lazy[p] = 0;
            flip(ps,pm,p<<1);
            flip(pm+1,pe,p<<1|1);
        }
        int res = sum(s,e,ps,pm,p<<1) + sum(s,e,pm+1,pe,p<<1|1);
        tree[p] = tree[p<<1] + tree[p<<1|1];
        return res;
    }
}seg;
int main(){
    int n,q;
    scanf("%d %d",&n,&q);
    for (int i=0; i<q; i++) {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        if(x == 0){
            seg.mod(y,z,1,n,1);
        }
        else{
            printf("%d\n",seg.sum(y,z,1,n,1));
        }
    }
}