#include <cstdio>
#include <algorithm>

struct strap{int c,h;}a[2005];
int cmp(strap p, strap q){return p.c>q.c;}

int n;
int dp[2005][2005];

int f(int avail, int pos){
    if(pos==n) return 0;
    if(avail>n) avail=n;
    if(avail<0) return 0;
    if(dp[avail][pos]) return dp[avail][pos];
    return dp[avail][pos]=std::max(f(avail+a[pos+1].c-1,pos+1),f(avail,pos+1)-a[pos+1].h)+a[pos].h;
}

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&a[i].c,&a[i].h);
    }
    std::sort(a,a+n,cmp);
    printf("%d",std::max(f(a[0].c,0),f(1,0)-a[0].h));
}