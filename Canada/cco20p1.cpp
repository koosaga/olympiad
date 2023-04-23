#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 200005;
const int mod = 998244353;

int n, l, r, y;

int main(){
    vector<pi> v;
    scanf("%d %d %d %d",&n,&l,&r,&y);
    for(int i=0; i<n; i++){
        lint x, vv, h;
        scanf("%lld %lld %lld",&x,&vv,&h);
        lint q = (y * h - 1) / vv;
        lint s = x - q, e = x + q;
        s = max(s, 1ll * l);
        e = min(e, 1ll * r);
        if(s <= e){
            v.emplace_back(s, 1);
            v.emplace_back(e + 1, -1);
        }
    }
    sort(all(v));
    int cnt = 0;
    vector<int> dap(n + 1);
    for(int i=0; i+1<sz(v); i++){
        cnt += v[i].second;
        if(cnt) dap[cnt] += v[i+1].first - v[i].first;
    }
    dap[0] += r - l + 1 - accumulate(all(dap), 0);
    for(int i=0; i<=n; i++){
        if(i) dap[i] += dap[i - 1];
        printf("%d\n", dap[i]);
    }
}
