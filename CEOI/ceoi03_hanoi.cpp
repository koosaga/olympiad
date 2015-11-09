#include <cstdio>
const int mod = 1e6;
 
int pos[100005], n;
int pow2[100005];
 
int main(){
    scanf("%d",&n);
    int arr[5],t;
    for (int i=0; i<3; i++) {
        scanf("%d",&arr[i]);
    }
    for (int i=0; i<3; i++) {
        for (int j=0; j<arr[i]; j++) {
            scanf("%d",&t);
            pos[t] = i;
        }
    }
    pow2[0] = 1;
    for (int i=1; i<=n; i++) {
        pow2[i] = pow2[i-1] << 1;
        pow2[i] %= mod;
    }
    printf("%d\n",pos[n]+1);
    int p = pos[n], ret = 0;
    for (int i=n; i; i--) {
        if(p == pos[i]) continue;
        else{
            ret += pow2[i-1];
            ret %= mod;
            p = 3 - pos[i] - p;
        }
    }
    printf("%d\n",ret);
}