#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long lint;

int k;

struct pos{int x,y,n;}x[200005];
bool cmpx(pos a, pos b){return a.x < b.x;}
bool cmpy(pos a, pos b){return a.y < b.y;}
bool cmpn(pos a, pos b){return a.n < b.n;}

int lx[200005], ly[200005], piv, m, n;
long long res;

struct query{int s,e,x;}q[200005];
bool cmpq(query a, query b){return a.x < b.x;}

struct seg{
    int tree[530000];
    bool lazy[530000];
    void rev(int s, int e, int p){
        tree[p] = lx[e] - lx[s] - tree[p];
        lazy[p] ^= 1;
    }
    void insert(int s, int e, int ps, int pe, int p){
        if(pe < s || e < ps) return;
        if(s <= ps && pe <= e){
            rev(ps,pe,p);
            return;
        }
        if(pe == ps + 1) return;
        else{
            int pm = (ps+pe)/2;
            if(lazy[p]){
                lazy[p] ^= 1;
                rev(ps,pm,p<<1);
                rev(pm,pe,p<<1|1);
            }
            insert(s,e,ps,pm,p<<1);
            insert(s,e,pm,pe,p<<1|1);
            tree[p] = tree[2*p] + tree[2*p+1];
        }
    }
    int query(){ return tree[1]; }
}seg;

struct seg2{
    lint tree[530000];
    int lazy[530000];
    void insert(int s, int e, int ps, int pe, int p){
        if(pe < s || e < ps) return;
        if(s <= ps && pe <= e){
            tree[p] = lx[pe] - lx[ps] - tree[p];
            lazy[p] ^= 1;
            return;
        }
        if(ps+1 == pe) return;
        insert(s,e,ps,(ps+pe)/2,2*p);
        insert(s,e,(ps+pe)/2,pe,2*p+1);
        tree[p] = tree[2*p] + tree[2*p+1];
        if(lazy[p])
            tree[p] = lx[pe] - lx[ps] - tree[p];
    }
    lint query(){return tree[1];}
}seg2;

int main(){
    int a,b,c,d;
    scanf("%d %d %d",&m,&n,&k);
    for (int i=0; i<k; i++) {
        scanf("%d %d %d %d",&a,&b,&c,&d);
        x[i<<1] = {a,c,i<<1};
        x[i<<1|1] = {b+1,d+1,i<<1|1};
    }
    sort(x,x+2*k,cmpx);
    for (int i=0; i<2*k; i++) {
        lx[i] = x[i].x;
        x[i].x = i;
    }
    sort(x,x+2*k,cmpy);
    for (int i=0; i<2*k; i++) {
        ly[i] = x[i].y;
        x[i].y = i;
    }
    sort(x,x+2*k,cmpn);
    for (int i=0; i<k; i++) {
        q[i<<1] = {x[i<<1].x,x[i<<1|1].x,x[i<<1].y};
        q[i<<1|1] = {x[i<<1].x,x[i<<1|1].x,x[i<<1|1].y};
    }
    sort(q,q+2*k,cmpq);
    for (int i=0; i<2*k; i++) {
        if(i) res += 1ll * piv * (ly[i] - ly[i-1]);
        seg.insert(q[i].s,q[i].e,0,2*k,1);
        piv = seg.query();
    }
    printf("%lld",1ll*n*m - res);
}