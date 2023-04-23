#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 100005;

struct bit{
    int tree[MAXN];
    void add(int x, int v){
        for(int i = x; i < MAXN; i += i & -i) tree[i] += v;
    }
    int query(int x){
        int ret = 0;
        for(int i = x; i; i -= i & -i) ret += tree[i];
        return ret;
    }
}bit;

vector<int> v[MAXN];
map<pi, lint> mp;

lint query(int x, int y){
    if(sz(v[x]) > sz(v[y])) return -query(y, x);
    if(mp.count(pi(x, y))) return mp[pi(x, y)];
    lint ret = 0;
    for(int i = 0; i < sz(v[x]); i++){
        int p = lower_bound(all(v[y]), v[x][i]) - v[y].begin();
        ret += sz(v[y]) - 2 * p;
    }
    return mp[pi(x, y)] = ret;
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k, q; cin >> n >> k >> q;
    vector<int> ord(k); iota(all(ord), 1);
    vector<int> a(n);
    lint ret = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        ret += bit.query(k) - bit.query(a[i]);
        bit.add(a[i], 1);
        v[a[i]].push_back(i);
    }
    while(q--){
        int x; cin >> x;
        int l = ord[x - 1], r = ord[x];
        swap(ord[x - 1], ord[x]);
        ret += query(l, r);
        cout << ret << "\n";
    }
}
