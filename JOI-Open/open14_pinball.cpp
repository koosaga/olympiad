#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
 
struct sti{int s,e,d,x;}a[100005];
 
vector<int> v;
lint dpl[100005], dpu[100005];
 
struct rmq{
    lint tree[1050000];
    int lim;
    void init(int n){
        memset(tree,0x3f,sizeof(tree));
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void add(int x, lint v){
        x += lim;
        tree[x] = min(tree[x],v);
        while(x > 1){
            x >>= 1;
            tree[x] = min(tree[2*x],tree[2*x+1]);
        }
    }
    lint query(int s, int e){
        s += lim;
        e += lim;
        lint r = 1e18;
        while(s < e){
            if(s%2 == 1) r = min(r,tree[s++]);
            if(e%2 == 0) r = min(r,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) r = min(r,tree[s]);
        return r;
    }
}rmq;
 
struct seg{
    lint tree[1050000];
    void init(){
        memset(tree,0x3f,sizeof(tree));
    }
    void lazydown(int p){
        tree[2*p] = min(tree[p],tree[2*p]);
        tree[2*p+1] = min(tree[p],tree[2*p+1]);
    }
    void add(int s, int e, lint x, int ps, int pe, int p){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            tree[p] = min(tree[p],x);
            return;
        }
        lazydown(p);
        int pm = (ps+pe)/2;
        add(s,e,x,ps,pm,2*p);
        add(s,e,x,pm+1,pe,2*p+1);
    }
    lint q(int x, int ps, int pe, int p){
        if(ps == pe) return tree[p];
        lazydown(p);
        int pm = (ps+pe)/2;
        if(x <= pm) return q(x,ps,pm,2*p);
        return q(x,pm+1,pe,2*p+1);
    }
}seg;
 
int n,m;
 
void input(){
    scanf("%d %d",&n,&m);
    v.push_back(1);
    v.push_back(m);
    for (int i=2; i<=n+1; i++) {
        scanf("%d %d %d %d",&a[i].s,&a[i].e,&a[i].d,&a[i].x);
        v.push_back(a[i].s);
        v.push_back(a[i].e);
        v.push_back(a[i].d);
    }
    sort(v.begin(),v.end());
    v.resize(unique(v.begin(),v.end()) - v.begin());
    for (int i=2; i<=n+1; i++) {
        a[i].s = (int)(lower_bound(v.begin(),v.end(),a[i].s) - v.begin());
        a[i].e = (int)(lower_bound(v.begin(),v.end(),a[i].e) - v.begin());
        a[i].d = (int)(lower_bound(v.begin(),v.end(),a[i].d) - v.begin());
    }
    a[1] = {0,0,0,0};
    a[0] = {(int)v.size()-1,(int)v.size()-1,(int)v.size()-1,0};
}
 
int main(){
    input();
    rmq.init((int)v.size());
    seg.init();
    rmq.add(a[0].d,0);
    for (int i=1; i<n+2; i++) {
        dpu[i] = rmq.query(0,a[i].e) + a[i].x;
        rmq.add(a[i].d,dpu[i]);
    }
    for (int i=n+1; i; i--) {
        dpl[i] = seg.q(a[i].d,0,(int)v.size()-1,1) + a[i].x;
        dpl[i] = min(dpl[i],dpu[i]);
        seg.add(a[i].s,a[i].e,dpl[i],0,(int)v.size()-1,1);
    }
    if(dpl[1] >= 1e17) puts("-1");
    else printf("%lld",dpl[1]);
}