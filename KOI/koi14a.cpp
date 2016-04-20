#include <cstdio>
 
int gcd(int a, int b){return b?gcd(b,a%b):a;}
 
int main(){
    int a,b,r = 0;
    scanf("%d %d",&a,&b);
    for (int i=a; i<=b; i++) {
        for (int j=1; j<=i; j++) {
            int g = gcd(i,j);
            if(i*(g-1) < a*g) r++;
        }
    }
    printf("%d",r);
}