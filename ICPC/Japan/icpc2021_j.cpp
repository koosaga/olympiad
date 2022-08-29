#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 200005;

struct bit{
    int tree[MAXN];
    void clear(){
        memset(tree, 0, sizeof(tree));
    }
    void add(int x, int v){
        for(int i = x; i < MAXN; i+=i&-i) tree[i] += v;
    }
    int query(int x){
        int ret = 0;
        for(int i = x; i; i-=i&-i) ret += tree[i];
        return ret;
    }
}bit;

lint solve(vector<pi> a){
    int n = sz(a);
    sort(all(a));
    vector<int> L(n), R(n);
    int curmin = 1e9;
    for(int i = 0; i < n; i++){
        if(curmin > a[i].second) L[i] = 1;
        curmin = min(curmin, a[i].second);
    }
    curmin = -1e9;
    for(int i = n - 1; i >= 0; i--){
        if(curmin < a[i].second) R[i] = 1;
        curmin = max(curmin, a[i].second);
    }
    vector<int> Up(n + 1, n + 1), Dn(n + 1, n + 1);
    for(int i = 0; i < n; i++){
        Up[a[i].second - 1] = a[i].first;
        Dn[a[i].first - 1] = a[i].second;
    }
    for(int i = n - 1; i >= 0; i--) Up[i] = min(Up[i], Up[i + 1]);
    for(int i = n - 1; i >= 0; i--) Dn[i] = min(Dn[i], Dn[i + 1]);
    lint ret = 0;
    vector<vector<int>> event(n);
    for(int i = 0; i < n; i++){
        if(R[i]){
            if(Up[a[i].second] >= 2) event[Up[a[i].second] - 2].push_back(Dn[a[i].first]);
        }
    }
    bit.clear();
    for(int i = 0; i < n; i++){
        if(L[i]) bit.add(a[i].second, 1);
        for(auto &j : event[i]) ret += bit.query(j - 1);
    }
    return ret;
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n; cin >> n;
    vector<pi> a(n);
    vector<int> x(n), y(n);
    for(int i = 0; i < n; i++){
        cin >> x[i] >> y[i];
        a[i] = pi(x[i], y[i]);
    }
    sort(all(x)); sort(all(y));
    for(int i = 0; i < n; i++){
        a[i].first = lower_bound(all(x), a[i].first) - x.begin() + 1;
        a[i].second = lower_bound(all(y), a[i].second) - y.begin() + 1;
    }
    lint ans = solve(a);
    for(int i = 0; i < n; i++) a[i].second = n + 1 - a[i].second;
    cout << ans << "\n";
}
