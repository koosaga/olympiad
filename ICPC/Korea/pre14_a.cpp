#include <cstdio>

int t;

int main(){
    scanf("%d",&t);
    while (t--) {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        printf("%d%02d\n",c%a + a * (c%a == 0) ,(c-1)/a+1);
    }
}