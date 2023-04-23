#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;

void Reverse(int s, int e, vector<int> &p, vector<pi> &ret){
    if(s == e - 1) return;
    while(e - s > 1){
        swap(p[s], p[e - 1]);
        ret.emplace_back(s, e - 1);
        s++;
        e--;
    }
}

void merge(int s, int m, int e, vector<int> &p, vector<pi> &ret){
    if(s + 1 == e) return;
    int midVal;
    {
        vector<int> vals(p.begin() + s, p.begin() + e);
        nth_element(vals.begin(), vals.begin() + sz(vals) / 2, vals.end());
        midVal = vals[sz(vals) / 2];
    }
    int p1 = m, p2 = m;
    while(p1 > s && p[p1 - 1] >= midVal) p1--;
    while(p2 < e && p[p2] < midVal) p2++;
    Reverse(p1, m, p, ret);
    Reverse(m, p2, p, ret);
    Reverse(p1, p2, p, ret);
    merge(s, p1, (s + e) / 2, p, ret);
    merge((s + e) / 2, p2, e, p, ret);
}

void dnc(int s, int e, vector<int> &p, vector<pi> &ret){
    if(s + 1 == e) return;
    int m = (s + e) / 2;
    dnc(s, m, p, ret);
    dnc(m, e, p, ret);
//  printf("\nbefore merge[%d, %d, %d]:\n", s, m, e);
//  for(auto &i : p) printf("%d ", i);
    merge(s, m, e, p, ret);
//  printf("\nafter merge[%d, %d, %d]:\n", s, m, e);
//  for(auto &i : p) printf("%d ", i);
}

vector<pi> solve(vector<int> p){
    vector<pi> ret;
    dnc(0, sz(p), p, ret);
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //int q; cin >> q; while(q--){
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(auto &i : a) cin >> i, i--;
    for(auto &i : b) cin >> i, i--;
    for(int i = 0; i < 2; i++){
        auto sol1 = solve(a);
        auto sol2 = solve(b);
        reverse(all(sol2));
        for(auto &i : sol2) sol1.push_back(i);
        if(i == 1){
            for(auto &[x, y] : sol1) tie(x, y) = pi(n - 1 - y, n - 1 - x);
        }
        if(sz(sol1) <= 300000){
            cout << sz(sol1) << "\n";
            for(auto &i : sol1) cout << i.first + 1 << " " << i.second + 1 << "\n";
            return 0;
        }
        //  }
        reverse(all(a));
        reverse(all(b));
    }
}
