#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
 
int n, q;
int a[100005];
 
struct seg{
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
        int pm = (ps + pe) / 2;
        lazydown(p);
        add(s,e,ps,pm,2*p,v);
        add(s,e,pm+1,pe,2*p+1,v);
        tree[p] = max(tree[2*p], tree[2*p+1]);
    }
    int lower_bound(int ps, int pe, int p, int val){
        if(tree[1] < val) return n+1;
        if(ps == pe) return ps;
        int pm = (ps + pe) / 2;
        lazydown(p);
        if(tree[2*p] < val) return lower_bound(pm+1,pe,2*p+1,val);
        else return lower_bound(ps,pm,2*p,val);
    }
    int getval(int pos, int ps, int pe, int p){
        if(ps == pe) return tree[p];
        int pm = (ps + pe) / 2;
        lazydown(p);
        if(pos <= pm) return getval(pos,ps,pm,2*p);
        return getval(pos,pm+1,pe,2*p+1);
    }
    void dfs(int ps, int pe, int p){
        if(ps == pe){
            printf("%d ",tree[p]);
            return;
        }
        lazydown(p);
        dfs(ps,(ps+pe)/2,2*p);
        dfs((ps+pe)/2+1,pe,2*p+1);
    }
}seg;
 
int main(){
    scanf("%d %d",&n,&q);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    for(int i=1; i<=n; i++){
        seg.add(i,i,1,n,1,a[i]);
    }
    while(q--){
        char str[5];
        int x, y;
        scanf("%s %d %d",str,&y,&x);
        if(str[0] == 'F'){
            int st = seg.lower_bound(1,n,1,x);
            if(st == n+1) continue;
            int ed = min(st + y - 1, n);
            int val = seg.getval(ed,1,n,1);
            int t = seg.lower_bound(1,n,1,val);
            int cnt = ed - t + 1;
            int u = seg.lower_bound(1,n,1,val + 1);
            seg.add(st, t - 1, 1, n, 1, 1);
            seg.add(u - cnt, u - 1, 1, n, 1, 1);
        }
        else{
            swap(x,y);
            int t = seg.lower_bound(1,n,1,y+1);
            int u = seg.lower_bound(1,n,1,x);
            printf("%d\n",t - u);
        }
    }
}