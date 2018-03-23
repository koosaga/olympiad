#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

pi a[3005];
int n;

void solve(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first, &a[i].second);
    }
    int ret = 0;
    sort(a,a+n);
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            int dx = (a[i].first + a[j].first);
            int dy = (a[i].second + a[j].second);
            int dx2 = (a[i].first - a[j].first);
            int dy2 = (a[i].second - a[j].second);
            if((dx + dy2) % 2 == 0 && (dy + dx2) % 2 == 0){
                pi f1((dx + dy2) / 2, (dy - dx2) / 2);
                pi f2((dx - dy2) / 2, (dy + dx2) / 2);
                auto t = lower_bound(a,a+n,f1);
                if(t != a+n && *t == f1){
                    auto t2 = lower_bound(a,a+n,f2);
                    if(t2 != a+n && *t2 == f2){
                        ret = max(ret, dx2 * dx2 + dy2 * dy2);
                    }
                }
            }
        }
    }
    printf("%d\n",ret/2);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
}