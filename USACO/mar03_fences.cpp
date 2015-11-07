#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
 
int n,m,a[100005];
 
bool trial(double t){
    double b[100005];
    for (int i=1; i<=n; i++) {
        b[i] = a[i] - t * i;
    }
    double mp = -1e9;
    for (int i=n-m; i>=0; i--) {
        mp = max(mp,b[i+m]);
        if(mp >= b[i]) return 1;
    }
    return 0;
}
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
        a[i] += a[i-1];
    }
    double s = 0, e = 1e4;
    for (int i=0; i<30; i++) {
        double m = (s+e)/2;
        if(trial(m)) s = m;
        else e = m;
    }
    printf("%d",(int)floor(1000 * e));
}