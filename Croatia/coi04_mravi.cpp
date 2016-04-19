#include <cstdio>
#include <algorithm>
using namespace std;
 
int l,t,n,a[70005];
char str[5];
 
int main(){
    scanf("%d %d %d",&l,&t,&n);
    for (int i=0; i<n; i++) {
        scanf("%d %s",&a[i],str);
        if(str[0] == 'L') a[i] -= t;
        else a[i] += t;
    }
    for (int i=0; i<n; i++) {
        if(a[i] < 0) a[i] = -a[i];
        a[i] %= 2 * l;
        if(a[i] > l ) a[i] = 2 * l - a[i];
    }
    sort(a,a+n);
    for (int i=0; i<n; i++) {
        printf("%d ",a[i]);
    }
}