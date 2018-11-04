#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long lint;

int a[1000005], n;

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0; i<n; i++){
            scanf("%d",&a[i]);
        }
        int maxv = -1;
        lint ret = 0;
        for(int i=n-1; i>=0; i--){
            maxv = max(maxv, a[i]);
            ret += maxv - a[i];
        }
        printf("%lld\n",ret);
    }
}