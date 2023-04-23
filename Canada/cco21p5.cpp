#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 530000;
const int mod = 1e9 + 7;

struct seg{
    int tree[MAXT], lazy[MAXT];
    void lazydown(int p){
        for(int i = 2*p; i < 2*p+2; i++){
            lazy[i] += lazy[p];
            tree[i] += lazy[p];
        }
        lazy[p] = 0;
    }
    void add(int s, int e, int ps, int pe, int p, int v){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            tree[p] += v;
            lazy[p] += v;
            return;
        }
        lazydown(p);
        int pm = (ps+pe)/2;
        add(s, e, ps, pm, 2*p, v);
        add(s, e, pm+1, pe, 2*p+1, v);
        tree[p] = min(tree[2*p], tree[2*p+1]);
    }
    int query(int s, int e, int ps, int pe, int p){
        if(e < ps || pe < s) return 1e9;
        if(s <= ps && pe <= e) return tree[p];
        lazydown(p);
        int pm = (ps+pe)/2;
        return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
    }
}seg;

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> L(n, 1e9), R(n, -1e9), dp(n + 1), nxt(n, 1e9);
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        u--; v--;
        if(u > v) swap(u, v);
        R[u] = max(R[u], v);
        L[v] = min(L[v], u);
    }
    for(int i = 0; i < n; i++){
        nxt[i] = R[i];
        if(i) nxt[i] = max(nxt[i], nxt[i - 1]);
    }
    vector<pi> swp;
    for(int i = 0; i < n; i++) swp.emplace_back(min(i, L[i]), i);
    sort(all(swp)); 
    for(int i = n - 1; i >= 1; i--){
        while(sz(swp) && swp.back().first >= i){
            seg.add(swp.back().second + 1, n, 0, n, 1, 1);
            swp.pop_back();
        }
        dp[i] = seg.query(max(i, nxt[i-1]) + 1, n, 0, n, 1);
        seg.add(i, i, 0, n, 1, dp[i]);
    }
    cout << dp[1] << "\n";
}
