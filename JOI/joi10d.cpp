#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
int n;
pi a[100005];
 
int solve(){
    int s = 0, e = 400000;
    while (s != e) {
        int m = (s+e)/2;
        int xl = 1e9, yl = 1e9, xh = -1e9, yh = -1e9;
        for (int j=0; j<n; j++) {
            if(a[j].first > m || a[j].second > m){
                xl = min(xl,a[j].first);
                xh = max(xh,a[j].first);
                yl = min(yl,a[j].second);
                yh = max(yh,a[j].second);
            }
        }
        if(yh - yl <= m && xh - xl <= m) e = m;
        else s = m+1;
    }
    return s;
}
 
int main(){
    scanf("%d",&n);
    int minv1 = 1e9, minv2 = 1e9, maxv1 = 0, maxv2 = 0;
    for (int i=0; i<n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        a[i] = pi(x+y,x-y);
        maxv1 = max(maxv1,x+y);
        maxv2 = max(maxv2,x-y);
        minv1 = min(minv1,x+y);
        minv2 = min(minv2,x-y);
    }
    maxv1 -= minv1;
    maxv2 -= minv2;
    for (int i=0; i<n; i++) {
        a[i].first -= minv1;
        a[i].second -= minv2;
    }
    int ret = solve();
    for (int i=0; i<n; i++) {
        a[i].first = maxv1 - a[i].first;
    }
    ret = min(ret,solve());
    printf("%d\n",ret);
}