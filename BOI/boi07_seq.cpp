#include <cstdio>
#include <algorithm>
using namespace std;
 
long long t;
int a[1000005];
 
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    for (int i=0; i<n-1; i++) {
        t += max(a[i],a[i+1]);
    }
    printf("%lld",t);
}