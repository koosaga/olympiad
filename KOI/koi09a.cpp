#include <cstdio>
 
int a[20005],n,v[20005];
 
int get_comp(int x){
    if(v[x]) return 0;
    v[x] = 1;
    return 1 + get_comp(a[x]);
}
 
int g(int x, int y){
    return y?g(y,x%y):x;
}
 
int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
    }
    int x = 1;
    for (int i=1; i<=n; i++) {
        if(!v[i]){
            int t = get_comp(i);
            x /= g(x,t);
            x *= t;
        }
    }
    printf("%d",x);
}