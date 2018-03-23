#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

struct v{
    int a, b;
    int idx;
}a[10005];

int n;

bool cmp(v a, v b){
    return 1ll * a.a * b.b > 1ll * b.a * a.b;
}

int main(){
    cin >> n;
    for(int i=1; i<=n; i++){
        double x, y;
        cin >> x >> y;
        a[i].a = (int)round(1e6 * x);
        a[i].b = (int)round(1e6 * y);
        a[i].idx = i;
    }
    sort(a+1, a+n+1, cmp);
    for(int i=1; i<=n; i++) printf("%d\n", a[i].idx);
}

