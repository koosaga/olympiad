#include <cstdio>
#include <algorithm>
using namespace std;

struct seg{
    int tree[530000], lazy[530000];
    void lazydown(int p){
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        tree[2*p] += lazy[p];
        tree[2*p+1] += lazy[p];
        lazy[p] = 0;
    }
    void add(int s, int e, int ps, int pe, int p, int v){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            tree[p] += v;
            lazy[p] += v;
            return;
        }
        lazydown(p);
        int pm = (ps + pe) / 2;
        add(s,e,ps,pm,2*p,v);
        add(s,e,pm+1,pe,2*p+1,v);
        tree[p] = min(tree[2*p],tree[2*p+1]);
    }
}seg;

int n, a[200005], original[200005];

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
        original[i] = a[i];
    }
    sort(a,a+n);
    for (int i=1; i<=n; i++) {
        seg.add(i,i,1,n,1,i - (int)(upper_bound(a,a+n,i)-a));
    }
    puts(seg.tree[1] < 0 ? "NIE": "TAK");
    int m;
    scanf("%d",&m);
    while (m--) {
        int s, e;
        scanf("%d %d",&s,&e);
        s--;
        seg.add(original[s],n,1,n,1,1);
        original[s] = e;
        seg.add(original[s],n,1,n,1,-1);
        puts(seg.tree[1] < 0 ? "NIE": "TAK");
    }
}