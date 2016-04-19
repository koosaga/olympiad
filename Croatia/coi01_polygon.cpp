#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int x[105], y[105], n;
 
bool ccw(int p, int q, int r){
    if(q == r) return 1;
    int dx1 = x[q] - x[p];
    int dy1 = y[q] - y[p];
    int dx2 = x[r] - x[q];
    int dy2 = y[r] - y[q];
    return dx1 * dy2 - dy1 * dx2 > 0;
}
 
int dp[105][105];
 
int f(int pa, int a){
    if(a == 0) return 1;
    if(dp[pa][a]) return dp[pa][a];
    int res = -1e9;
    for (int i=0; i<=n; i++) {
        if(a == i) continue;
        if(ccw(pa,a,i) && ccw(a,i,0)){
            res = max(res,f(a,i));
        }
    }
    return dp[pa][a] = res + 1;
}
int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&x[i],&y[i]);
    }
    int res = 0;
    for (int i=1; i<=n; i++) {
        res = max(res,f(0,i));
    }
    printf("%d",res);
}