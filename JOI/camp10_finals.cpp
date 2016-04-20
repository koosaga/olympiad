#include <cstdio>
#include <algorithm>
using namespace std;

int n,m,k;
int p[100005],r[100005];

struct edge{int s,e,x;}a[100005];
int cmp(edge a, edge b){return a.x < b.x;}

int find(int x){
    if(p[x] == x) return x;
    else return p[x] = find(p[x]);
}

void uni(int a, int b){
    a = find(a);
    b = find(b);
    if(r[a] > r[b]) p[a] = b;
    else p[b] = a;
    if(r[a] == r[b]) r[b]++;
}

int main(){
    scanf("%d %d %d",&n,&m,&k);
    for (int i=1; i<=n; i++) p[i] = i;
    for (int i=0; i<m; i++) {
        scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
    }
    sort(a,a+m,cmp);
    int piv = 0, ans = 0;
    for (int i=0; i<m; i++) {
        if(piv >= n-k) break;
        if(find(a[i].s) == find(a[i].e)) continue;
        else{
            uni(a[i].s,a[i].e);
            ans += a[i].x;
            piv++;
        }
    }
    printf("%d",ans);
}