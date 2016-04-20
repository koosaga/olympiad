#include <cstdio>
typedef long long lint;

int n, q, k;
int a[100005];

struct bit{
    lint tree[100005];
    int lim;
    void init(int n){
        lim = n + 2;
    }
    void add(int x, lint v){
        x += 2;
        while(x <= lim){
            tree[x] += v;
            x += x & -x;
        }
    }
    lint sum(int x){
        x += 2;
        lint ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
    lint rsum(int s, int e){
        return sum(e) - sum(s-1);
    }
}bit;

void solve3(){
    bit.init(n);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
        bit.add(i,a[i]);
    }
    for (int i=0; i<q; i++) {
        int t;
        scanf("%d",&t);
        if(t == 1){
            int u, b;
            scanf("%d %d",&u,&b);
            bit.add(u,b - a[u]);
            a[u] = b;
        }
        if(t == 2){
            scanf("%*d %*d");
        }
        if(t == 3){
            int s,e;
            scanf("%d %d",&s,&e);
            printf("%lld\n",bit.rsum(s,e));
        }
    }
}

struct seg{
    lint tree[270000][30];
    int lazy[270000];
    void lazydown(int p){
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        for(int i=0; i<30; i++){
            if(i + lazy[p] < 30) tree[2*p][i] = tree[2*p][i + lazy[p]];
            else tree[2*p][i] = 0;
            if(i + lazy[p] < 30) tree[2*p+1][i] = tree[2*p+1][i + lazy[p]];
            else tree[2*p+1][i] = 0;
        }
        lazy[p] = 0;
        for(int i=0; i<30; i++){
            tree[p][i] = tree[2*p][i] + tree[2*p+1][i];
        }
    }
    void add(int pos, int ps, int pe, int p, int v){
        if(ps == pe){
            lazy[p] = 0;
            tree[p][0] = v;
            for (int i=1; i<30; i++){
                tree[p][i] = tree[p][i-1] / k;
            }
            return;
        }
        int pm = (ps + pe) / 2;
        lazydown(p);
        if(pos <= pm) add(pos,ps,pm,2*p,v);
        else add(pos,pm+1,pe,2*p+1,v);
        for (int i=0; i<30; i++){
            tree[p][i] = tree[2*p][i] + tree[2*p+1][i];
        }
    }
    void move(int s, int e, int ps, int pe, int p){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            lazy[p]++;
            for(int i=0; i<30; i++){
                tree[p][i] = tree[p][i+1];
            }
            tree[p][29] = 0;
            return;
        }
        lazydown(p);
        int pm = (ps + pe) / 2;
        move(s,e,ps,pm,2*p);
        move(s,e,pm+1,pe,2*p+1);
        for(int i=0; i<30; i++){
            tree[p][i] = tree[2*p][i] + tree[2*p+1][i];
        }
    }
    lint sum(int s, int e, int ps, int pe, int p){
        if(e < ps || pe < s) return 0;
        if(s <= ps && pe <= e) return tree[p][0];
        lazydown(p);
        int pm = (ps + pe) / 2;
        lint ret = sum(s,e,ps,pm,2*p) + sum(s,e,pm+1,pe,2*p+1);
        for(int i=0; i<30; i++){
            tree[p][i] = tree[2*p][i] + tree[2*p+1][i];
        }
        return ret;
    }
}seg;

int main(){
    scanf("%d %d %d",&n,&q,&k);
    if(k == 1){
        solve3();
        return 0;
    }
    else{
        for (int i=1; i<=n; i++) {
            scanf("%d",&a[i]);
            seg.add(i,1,n,1,a[i]);
        }
        for (int i=0; i<q; i++) {
            int t;
            scanf("%d",&t);
            if(t == 1){
                int u, b;
                scanf("%d %d",&u,&b);
                seg.add(u,1,n,1,b);
            }
            if(t == 2){
                int s,e;
                scanf("%d %d",&s,&e);
                seg.move(s,e,1,n,1);
            }
            if(t == 3){
                int s,e;
                scanf("%d %d",&s,&e);
                printf("%lld\n",seg.sum(s,e,1,n,1));
            }
        }
    }
}