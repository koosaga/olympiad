#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int t[100005],u[100005],p[100005],q[100005],m[100005],n[100005],ps,qs,ms,ns;

int main(){
    int no,l,a,b;
    long long res = 0;
    scanf("%d %d",&l,&no);
    for (int i=0; i<no; i++) {
        scanf("%d %d",&a,&b);
        t[i]=a+b;
        u[i]=a-b;
    }
    std::sort(t,t+no);
    std::sort(u,u+no);
    for (int i=0; i<no; i++) {
        if(!i || t[i]!=t[i-1]){
            if(t[i]&1) q[qs++]=t[i];
            else p[ps++]=t[i];
        }
        if(!i || u[i]!=u[i-1]){
            if(u[i]&1) n[ns++]=u[i];
            else m[ms++]=u[i];
        }
    }
    for (int i=0; i<ps; i++) res+=l-abs(l-1-p[i]);
    for (int i=0; i<qs; i++) res+=l-abs(l-1-q[i]);
    for (int i=0; i<ms; i++) res+=l-abs(m[i]);
    for (int i=0; i<ns; i++) res+=l-abs(n[i]);
    for (int i=0; i<ps; i++) res-=upper_bound(m,m+ms,min((l<<1)-p[i]-1,p[i]))-lower_bound(m,m+ms,max(-p[i],p[i]-(l<<1)+1));
    for (int i=0; i<qs; i++) res-=upper_bound(n,n+ns,min((l<<1)-q[i]-1,q[i]))-lower_bound(n,n+ns,max(-q[i],q[i]-(l<<1)+1));
    printf("%lld\n",res);
}