#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long lint;
  
int n, x[100005], y[100005];
long double one = 1;
long double ccw(int p, int q){
    int dx1 = x[p] - x[0];
    int dy1 = y[p] - y[0];
    int dx2 = x[q] - x[0];
    int dy2 = y[q] - y[0];
    return one * dx1 * dy2 - one * dy1 * dx2;
}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&x[i],&y[i]);
    }
    long double ret = 0;
    for (int i=1; i<n-1; i++) {
        ret += ccw(i, i+1) * one * 2;
    }
    if(ret < 0) ret = -ret;
    for (int i=0; i<n; i++) {
        if(x[i] == x[(i+1)%n]){
            ret -= abs(y[(i+1)%n] - y[i]);
            continue;
        }
        if(y[i] == y[(i+1)%n]){
            ret -= abs(x[(i+1)%n] - x[i]);
            continue;
        }
    }
    printf("%.1Lf",ret/2);
}