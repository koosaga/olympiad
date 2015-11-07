#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long lint;
 
struct disj{
    int pa[1005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p), q = find(q);
        if(p == q) return 0;
        pa[q] = p;
        return 1;
    }
}uf[10005];
 
int comp[300005];
int n, m, k;
 
struct edg{int s, e, x, n;}a[300005];
bool cmp(const edg& a, const edg& b){return a.x > b.x;}
int main(){
    scanf("%d %d %d",&n,&m,&k);
    for (int i=0; i<k; i++){
        uf[i].init(n);
    }
    for (int i=0; i<m; i++) {
        scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
        a[i].n = i;
    }
    sort(a,a+m,cmp);
    for (int i=0; i<m; i++) {
        int s = 0, e = k-1;
        while (s != e) {
            int m = (s+e)/2;
            if(uf[m].find(a[i].s) != uf[m].find(a[i].e)){
                e = m;
            }
            else s = m+1;
        }
        if(e == k-1 && uf[e].find(a[i].s) == uf[e].find(a[i].e)){
            continue;
        }
        uf[s].uni(a[i].s,a[i].e);
        comp[a[i].n] = s+1;
    }
    for (int i=0; i<m; i++) {
        printf("%d\n",comp[i]);
    }
}