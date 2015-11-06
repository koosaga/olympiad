#include <cstdio>
 
int n, m;
int a[1000005], b[1000005];
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    int piv = 1;
    while (m) {
        if(m&1){
            for (int i=0; i<n; i++) {
                b[i] = a[i] ^ a[(i+piv)%n];
            }
            for (int i=0; i<n; i++) {
                a[i] = b[i];
            }
        }
        piv <<= 1;
        m >>= 1;
    }
    for (int i=0; i<n; i++) {
        printf("%d\n",a[i]);
    }
}