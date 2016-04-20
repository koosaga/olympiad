#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long lint;
 
struct sti{int s,e,x;}a[100005], b[100005];
int atrack[100005], btrack[100005];
int fa[100005], fb[100005];
int n;
lint dp[100005][2],l;
 
bool cmp1(sti a, sti b){return a.s == b.s?(a.e < b.e) : (a.s < b.s);}
bool cmp2(sti a, sti b){return a.e == b.e?(a.s < b.s) : (a.e < b.e);}
 
lint f(int pos, int piv){
    if(dp[pos][piv]) return dp[pos][piv];
    if(piv == 0){
        if(a[pos+1].s != a[pos].s) return l + abs(a[pos].e - a[pos].s);
        else return dp[pos][piv] =
            max(f(btrack[fa[pos+1]],1) + l + abs(a[pos].e - a[pos].s)
               ,f(pos+1,0) + abs(a[pos].e-a[pos].s) - abs(a[pos+1].e - a[pos+1].s));
    }
    else{
        if(b[pos+1].e != b[pos].e) return l + abs(b[pos].e - b[pos].s);
        else return dp[pos][piv] =
            max(f(atrack[fb[pos+1]],0) + l + abs(b[pos].e - b[pos].s)
               ,f(pos+1,1) + abs(b[pos].e-b[pos].s) - abs(b[pos+1].e - b[pos+1].s));
    }
}
 
int main(){
    scanf("%d %lld",&n,&l);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&a[i].s,&a[i].e);
        a[i].x = i;
        b[i] = a[i];
    }
    sort(a,a+n,cmp1);
    sort(b,b+n,cmp2);
    for (int i=0; i<n; i++) {
        fa[i] = a[i].x;
        fb[i] = b[i].x;
        atrack[a[i].x] = i;
        btrack[b[i].x] = i;
    }
    lint res = 0;
    for (int i=0; i<n; i++) {
        res = max(res,f(i,0));
        res = max(res,f(i,1));
    }
    printf("%lld",res);
}