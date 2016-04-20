#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

int n,m,k,a[1005];
pi swp[100005];

int up[1005], down[100005];

int main(){
    scanf("%d %d %*d %d",&n,&m,&k);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
        up[i] = i;
        down[i] = i;
    }
    for (int i=1; i<=m; i++) {
        scanf("%d %d",&swp[i].second,&swp[i].first);
    }
    sort(swp+1,swp+m+1);
    for (int i=1; i<=m; i++) {
        swap(up[swp[i].second],up[swp[i].second+1]);
    }
    int ret = 0;
    for (int i=1; i<=n; i++) {
        if(up[i] <= k) ret += a[i];
    }
    swap(up[swp[m].second],up[swp[m].second+1]);
    for (int i=m-1; i; i--) {
        int ret2 = 0;
        for (int j=1; j<=n; j++) {
            if(up[j] <= k) ret2 += a[down[j]];
        }
        ret = min(ret,ret2);
        swap(up[swp[i].second],up[swp[i].second+1]);
        swap(down[swp[i+1].second],down[swp[i+1].second+1]);
    }
    printf("%d",ret);
}