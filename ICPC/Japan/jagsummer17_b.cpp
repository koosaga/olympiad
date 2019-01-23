#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int mod = 1e9 + 7;
const int MAXN = 100005;

lint s, t;
int n, a[MAXN];

int main(){
    scanf("%lld %lld %d",&s,&t,&n);
    for(int i=0; i<n; i++) scanf("%d",&a[i]);
    lint acc = accumulate(a, a + n, 0ll);
    lint ret = 6e18;
    for(int i=0; i<n; i++){
        if(s <= t){
            ret = min(ret, 1ll * i);
        }
        else if(acc < 0){
            ret = min(ret, i + n * ((s - t + (-acc) - 1) / (-acc)));
        }
        s += a[i];
    }
    if(ret > 5e18) ret = -1;
    cout << ret << endl;
}
