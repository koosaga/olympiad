#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long lint;
 
lint d[100005];
int n;
lint trial(lint piv){
    lint res = 0;
    for (int i=0; i<n; i++) {
        res += max(d[i] - piv * i, piv * i - d[i]);
    }
    return res;
}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%lld",&d[i]);
    }
    int s = 0, e = 1e9;
    while (s != e) {
        int m = (s+e)>>1;
        if(trial(m) > trial(m+1)) s = m+1;
        else e = m;
    }
    printf("%lld",trial(s));
}