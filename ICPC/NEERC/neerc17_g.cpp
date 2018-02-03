#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 30005;
const lint inf = 1e11;
const lint offset = 5e10;
typedef pair<int, int> pi;

int n, r, k;
lint a[MAXN], b[MAXN], c[MAXN];
lint f[MAXN];

struct bit{
    int mp[MAXN];
    void add(lint x, int v){
        x++;
        while(x < MAXN){
            mp[x] += v;
            x += x & -x;
        }
    }
    int query(lint x){
        x++;
        int ret = 0;
        while(x){
            ret += mp[x];
            x -= x & -x;
        }
        return ret;
    }
    void clear(){ memset(mp, 0, sizeof(mp)); }
}bit;

vector<lint> v;

int trial1(lint x){
    v.clear();
    for(int i=1; i<=n-r+1; i++)v.push_back(f[i]);
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    x -= a[n];
    bit.clear();
    int ans = 0;
    for(int i=n; i; i--){
        if(i + r <= n - r + 1){
            int l = lower_bound(v.begin(), v.end(), f[i+r]) - v.begin();
            bit.add(l, 1);
        }
        int l = upper_bound(v.begin(), v.end(), x - f[i]) - v.begin();
        ans += bit.query(l - 1);
    }
    return ans;
}

int trial2(lint x){
    x -= a[n];
    int ans = 0;
    v.clear();
    for(int i=1; i<=n-r; i++){
        v.push_back(b[i + r] - c[i]);
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    bit.clear();
    for(int i=n; i; i--){
        if(i + r <= n - r + 1){
            int l = lower_bound(v.begin(), v.end(), b[i + r + r - 1] - c[i + r - 1]) - v.begin();
            bit.add(l, -1);
        }
        if(i + 1 <= n - r + 1){
            int l = lower_bound(v.begin(), v.end(), b[i + r] - c[i]) - v.begin();
            bit.add(l, 1);
        }
        int l = upper_bound(v.begin(), v.end(), x - (c[i + r - 1] - b[i-1])) - v.begin();
        ans += bit.query(l - 1);
    }
    return ans;
}

int main(){
    scanf("%d %d %d",&n,&r,&k);
    for(int i=1; i<=n; i++) scanf("%lld",&a[i]);
    for(int i=1; i<=n; i++) scanf("%lld",&b[i]);
    for(int i=1; i<=n; i++) scanf("%lld",&c[i]);
    for(int i=1; i<=n; i++){
        c[i] -= b[i];
        b[i] -= a[i];
        a[i] += a[i-1];
        b[i] += b[i-1];
        c[i] += c[i-1];
    }
    for(int i=1; i<=n-r+1; i++){
        f[i] = b[i + r - 1] - b[i - 1];
    }
    lint s = 0, e = 4e10;
    while(s != e){
        lint m = (s+e)/2;
        if(trial1(m) + trial2(m)< k) s = m+1;
        else e = m;
    }
    cout << s << endl;
}
