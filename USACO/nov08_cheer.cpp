#include <cstdio>
#include <algorithm>
using namespace std;
 
struct edg{int s,e,x;}a[100005];
bool cmp(edg a, edg b){return a.x < b.x;}
 
struct disj{
    int pa[10005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p;
        return 1;
    }
}disj;
 
int n,m,c[10005];
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        scanf("%d",&c[i]);
    }
    for (int i=0; i<m; i++) {
        scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
        a[i].x *= 2;
        a[i].x += c[a[i].s] + c[a[i].e];
    }
    sort(a,a+m,cmp);
    int ret = *min_element(c+1,c+n+1);
    disj.init(n);
    for (int i=0; i<m; i++) {
        if(disj.uni(a[i].s,a[i].e)){
            ret += a[i].x;
        }
    }
    printf("%d",ret);
}