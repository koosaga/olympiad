#include <cstdio>
#include <algorithm>
 
int gcd(int a, int b){
    if(a%b==0) return b;
    return gcd(b,a%b);
}
 
int main(){
    int n,m,t;
    scanf("%d %d",&n,&m);
    if(n>m) {t=n;n=m;m=t;}
    if(n!=gcd(n,m))return 0;
    t=1;
    for (int i=2; i*i<=m/n; i++) {
        if((m/n)%i==0 && gcd(i,(m/n)/i)==1) t=i;
    }
    printf("%d %d",n*t,m/t);
}