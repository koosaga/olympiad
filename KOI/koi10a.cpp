#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
long long n, a[5005];
int p = 0, q = 1, r = 2;
 
void update(int x, int y, int z){
    if(abs(a[x] + a[y] + a[z]) < abs(a[p] + a[q] + a[r])){
        p = x, q = y, r = z;
    }
}
 
int main(){
    scanf("%lld",&n);
    for (int i=0; i<n; i++) {
        scanf("%lld",&a[i]);
    }
    sort(a,a+n);
    for (int i=0; i<n; i++) {
        int p = n-1;
        for (int j=i+1; j<n; j++) {
            while (p-1 > j && a[i] + a[j] >= -a[p-1]) {
                p--;
            }
            if(j >= p) break;
            update(i,j,p);
            if(j != p-1) update(i,j,p-1);
        }
    }
    printf("%lld %lld %lld",a[p],a[q],a[r]);
}