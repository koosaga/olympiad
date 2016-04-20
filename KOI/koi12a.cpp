#include <cstdio>
#include <algorithm>
using namespace std;
 
int a[10005];
int n,m;
 
bool f(int x){
    int res = 0;
    for (int i=0; i<n; i++) {
        res += min(a[i],x);
    }
    return res <= m;
}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    scanf("%d",&m);
    int s = 0, e = *max_element(a,a+n);
    while (s != e) {
        int m = (s+e+1)/2;
        if(f(m)) s = m;
        else e = m-1;
    }
    printf("%d",s);
}