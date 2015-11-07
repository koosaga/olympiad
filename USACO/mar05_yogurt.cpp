#include <cstdio>
#include <algorithm>
using namespace std;

int n,s;

int main(){
    scanf("%d %d",&n,&s);
    int p = 1e9;
    long long ret = 0;
    for (int i=0; i<n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        p = min(p + s, x);
        ret += 1ll * y * p;
    }
    printf("%lld",ret);
}