#include <stdio.h>

int beet (int n){
    int r=1;
    while (n!=0) {
        n>>=1;
        r<<=1;
    }
    return r;
}
int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    k=beet((1<<n)-k);
    for (int i=0; i<(1<<n)-k; i++) {
        printf("I");
    }
    for (int i=0; i<(k+1)/2; i++) {
        printf("J");
    }
    for (int i=0; i<k/2; i++) {
        printf("O");
    }
    puts("");
}