#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 100005;
typedef long long lint;

lint k;
int n, a[MAXN];

pi up[MAXN], dn[MAXN];
lint up1[MAXN], up2[MAXN];

lint fuck(int js, int i, int je, lint w){
    lint ans = w * (je - js + 1);
    ans -= 1ll * i * (i - js + 1);
    ans += 1ll * i * (je - i);
    ans += up1[i] - up1[js-1];
    ans += up2[je] - up2[i];
    //for(int j=js; j<=i; j++) ans += j - a[j];
    //for(int j=i+1; j<=je; j++) ans += -j - a[j];
    return ans;
}

bool trial(int x){
    for(int i=2; i<n; i++){
        auto l = lower_bound(dn + 1, dn + n + 1, pi(x - i, -1e9)) - dn;
        auto r = lower_bound(up + 1, up + n + 1, pi(x + i, -1e9)) - up;
        if(l == n + 1 || r == n + 1) continue;
        int s = dn[l].second + 1;
        int e = up[r].second - 1;
        if(fuck(s, i, e, x) <= k) return true;
    }
    return false;
}

int main(){
    scanf("%d %lld",&n,&k);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        up[i] = pi(a[i] + i, i);
        dn[i] = pi(a[i] - i, i);
        up1[i] = up1[i-1] + (i - a[i]);
        up2[i] = up2[i-1] + (-i - a[i]);
    }
    sort(up + 1, up + n + 1);
    sort(dn + 1, dn + n + 1);
    for(int i=n-1; i; i--){
        up[i].second = min(up[i].second, up[i+1].second);
        dn[i].second = max(dn[i].second, dn[i+1].second);
    }
    int st = *max_element(a+1, a+n+1);
    int ed = st + 200000;
    while(st != ed){
        int m = (st+ed+1)/2;
        if(trial(m)) st = m;
        else ed = m-1;
    }
    cout << st;
}
