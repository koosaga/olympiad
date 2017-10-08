#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
 
int n, x[105], y[105];
 
int dist(int p, int q){
    return (y[q] - y[p]) * (y[q] - y[p]) + (x[q] - x[p])  * (x[q] -x[p]);
}
 
int ccw(int p, int q, int r){
    int dx1 = (x[q] - x[p]);
    int dy1 = (y[q] - y[p]);
    int dx2 = (x[r] - x[p]);
    int dy2 = (y[r] - y[p]);
    return (dx1 * dy2 - dy1 * dx2);
}
 
double val(int i, int j){
    double ret = 0;
    double ret2 = 0;
    for(int k=0; k<n; k++){
        double tmp = 1.0 * ccw(i,j,k) / hypot(x[i] - x[j], y[i] - y[j]);
        ret = max(ret,tmp);
        ret2 = min(ret2,tmp);
    }
    return ret - ret2;
}
 
int can(int i, int j){
    for(int k=0; k<n; k++){
        if(k == i || k == j) continue;
        int dab = dist(i,j);
        int dbc = dist(j,k);
        int dca = dist(i,k);
        if(dab + dbc - dca < 0) return 0;
        if(dab + dca - dbc < 0) return 0;
    }
    return 1;
}
 
int cases;
bool solve(){
    scanf("%d",&n);
    if(n == 0) return 0;
    for(int i=0; i<n; i++){
        scanf("%d %d",&x[i],&y[i]);
    }
    double ret = 1e9;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(can(i,j)){
                ret = min(ret, hypot(x[j] - x[i],y[j] - y[i]));
            }
            ret = min(ret, val(i,j));
        }
    }
    printf("Case %d: %.2f\n",++cases,ret + 5e-3 - 1e-6);
    return 1;
}
int main(){
    while(solve());
}