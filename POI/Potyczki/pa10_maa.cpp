#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000005;

pi merge(pi a, pi b){
    return pi(min(a.first, b.first), max(a.second, b.second));
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, d; cin >> n >> d;
    vector<pi> a(n);
    for(auto &[x, y] : a) cin >> x >> y;
    sort(all(a));
    vector<pi> L(n), R(n);
    for(int i = 0; i < n; i++){
        L[i] = R[i] = pi(a[i].second, a[i].second);
    }
    for(int i = 1; i < n; i++) L[i] = merge(L[i], L[i - 1]);
    for(int i = n - 2; i >= 0; i--) R[i] = merge(R[i], R[i + 1]); 
    lint ret = 0;
    for(int i = 0; i < n; ){
        int j = i; while(j < n && a[j].first == a[i].first) j++;
        if(i > 0 && j < n){
            int s = max(L[i - 1].first, R[j].first);
            int e = min(L[i - 1].second, R[j].second);
            ret += max(e - s - 1, 0);
        }
        if(j < n){
            int s = max(L[j - 1].first, R[j].first);
            int e = min(L[j - 1].second, R[j].second);
            ret += 1ll * (a[j].first - a[i].first - 1) * max(e - s - 1, 0);
        }
        i = j;
    }
    cout << ret << "\n";
}
