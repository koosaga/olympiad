#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> pi;

int n,d[100005];

void solve(){
    pi a[100005];
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&a[i].first,&a[i].second);
    }
    sort(a,a+n);
    int low = 1e9, ret = 0;
    for (int i=0; i<n; i++) {
        if(low > a[i].second){
            ret++;
        }
        low = min(low,a[i].second);
    }
    printf("%d\n",ret);
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        solve();
    }
}