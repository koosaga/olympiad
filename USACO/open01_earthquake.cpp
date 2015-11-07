#include <cstdio>
#include <algorithm>
using namespace std;
 
struct disj{
    int pa[405];
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
 
struct edg{
    int s,e;
    double x;
};
 
bool cmp(edg a, edg b){return a.x < b.x;}
 
int n,m,f;
int s[10005], e[10005], d[10005], t[10005];
 
edg edges[10005];
 
bool trial(double k){
    for (int i=0; i<m; i++) {
        edges[i].s = s[i];
        edges[i].e = e[i];
        edges[i].x = k * t[i] + d[i];
    }
    sort(edges,edges+m,cmp);
    disj.init(n);
    double ret = 0;
    for (int i=0; i<m; i++) {
        if(disj.uni(edges[i].s,edges[i].e)){
            ret += edges[i].x;
        }
    }
    return ret <= f;
}
 
int main(){
    scanf("%d %d %d",&n,&m,&f);
    for (int i=0; i<m; i++) {
        scanf("%d %d %d %d",&s[i],&e[i],&d[i],&t[i]);
    }
    double s = 0, e = 1e18;
    for (int i=0; i<100; i++) {
        double m = (s+e)/2;
        if(trial(m)) s = m;
        else e = m;
    }
    printf("%.4lf",s);
}