#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <set>
using namespace std;

const int offset = 100000;

int n,s;
int l[50005], r[50005];
int dpl[50005], dpr[50005];

struct seg{
    int tree[530000];
    void lazydown(int p){
        tree[2*p] = max(tree[2*p],tree[p]);
        tree[2*p+1] = max(tree[2*p+1],tree[p]);
    }
    int query(int pos, int ps, int pe, int p){
        if(ps == pe) return tree[p];
        int pm = (ps + pe) / 2;
        lazydown(p);
        if(pos <= pm) return query(pos,ps,pm,2*p);
        else return query(pos,pm+1,pe,2*p+1);
    }
    void fill(int s, int e, int ps, int pe, int p, int v){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            tree[p] = v;
            return;
        }
        int pm = (ps + pe) / 2;
        lazydown(p);
        fill(s,e,ps,pm,2*p,v);
        fill(s,e,pm+1,pe,2*p+1,v);
    }
}seg;

int main(){
    scanf("%d %d",&n,&s);
    s += offset;
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&l[i],&r[i]);
        l[i] += offset;
        r[i] += offset;
    }
    l[0] = r[0] = offset;
    for (int i=1; i<=n; i++) {
        int p = seg.query(l[i],0,2*offset,1);
        dpl[i] = min(dpl[p] + abs(l[p] - l[i]),dpr[p] + abs(r[p] - l[i]));
        p = seg.query(r[i],0,2*offset,1);
        dpr[i] = min(dpl[p] + abs(l[p] - r[i]),dpr[p] + abs(r[p] - r[i]));
        seg.fill(l[i]+1,r[i]-1,0,2*offset,1,i);
    }
    printf("%d",min(dpl[n] + abs(s - l[n]),dpr[n] + abs(s - r[n])));
}