#include <cstdio>
#include <cmath>
int c[100001],a[400];
int main(){
    int i,k,l,m;
    scanf("%d",&l);
    m = (int)sqrt(l);
    
    for (int i=0; i<m; i++) {
        a[i]=(i+1)*(i+1);
        c[a[i]]=1;
    }
    for (i=2; i<=l; i++) {
        if (c[i]) continue;
        c[i]=1e9;
        for (k=m-1; k>=0; k--) {
            if (a[k]>i) continue;
            if (c[i-a[k]] && c[i-a[k]]+1<c[i]) c[i]=c[i-a[k]]+1;
        }
        if (c[i]==1e9) c[i]=0;
    }
    printf("%d",c[l]==1e9?0:c[l]);
}