#include <cstdio>

void solve(){
    int a, b;
    scanf("%d %d",&a,&b);
    int rem = 0;
    while(a){
        int p = (b + a - 1) / a;
        rem = p;
        a = a * p - b;
        b *= p;
    }
    printf("%d\n",rem);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
}