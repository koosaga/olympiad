#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int OFFSET = 10000000;
// 6 ABC + 3 AAB + AAA = n^3

int radix[OFFSET * 6 + 5];
#define rep(i, s, e) for (int i = s; i < e; i++)

int mult(int a, int b, int c) {
    if (a == b && b == c)
        return 1;
    if (a == b || b == c)
        return 3;
    return 6;
}

int mult(int a, int b) { return a != b ? 2 : 1; }

lint get_total(vector<int> sum) {
    lint ans = 0;
    int n = sz(sum);
    // case#15
    memset(radix, 0, sizeof(radix));
    rep(d, 0, n) {
        rep(e, d + 1, n) rep(f, e, n) { ans += radix[sum[e] + sum[f] - sum[d] + 3 * OFFSET] * mult(e, f); }
        int a = d;
        radix[sum[a] + 3 * OFFSET] += 3;
    }
    // case#16
    memset(radix, 0, sizeof(radix));
    rep(d, 0, n) {
        rep(f, d + 1, n) { ans += radix[sum[d] + sum[f] + 3 * OFFSET]; }
        rep(a, 0, d + 1) {
            int b = d;
            radix[sum[a] + sum[b] + 3 * OFFSET] += 3 * mult(a, b);
        }
    }
    // case#17
    memset(radix, 0, sizeof(radix));
    rep(d, 0, n) {
        rep(e, d + 1, n) rep(f, e, n) { ans += radix[sum[e] + sum[f] + 3 * OFFSET] * mult(e, f); }
        rep(a, 0, d + 1) {
            int b = d;
            radix[sum[a] + sum[b] + 3 * OFFSET] += 6 * mult(a, b);
        }
    }
    // case#3
    memset(radix, 0, sizeof(radix));
    rep(d, 0, n) {
        rep(e, d + 1, n) rep(f, e, n) {
            int k = -2 * sum[d] + sum[e] + sum[f];
            if (k < -3 * OFFSET || k > 3 * OFFSET)
                continue;
            ans += radix[k + 3 * OFFSET] * mult(e, f);
        }
        rep(a, 0, d) {
            int b = d;
            radix[sum[a] - sum[b] + 3 * OFFSET] += 3;
        }
    }
    // case#7
    memset(radix, 0, sizeof(radix));
    rep(d, 0, n) {
        rep(e, d + 1, n) rep(f, e + 1, n) {
            int k = 2 * sum[d] - sum[e] + sum[f];
            if (k < -3 * OFFSET || k > 3 * OFFSET)
                continue;
            ans += radix[k + 3 * OFFSET];
        }
        rep(a, 0, d + 1) {
            int b = d;
            radix[sum[a] + sum[b] + 3 * OFFSET] += 3 * mult(a, b);
        }
    }
    // case#1
    memset(radix, 0, sizeof(radix));
    rep(d, 0, n) {
        rep(e, d + 1, n) rep(f, e + 1, n) ans += radix[sum[d] - sum[e] + sum[f] + 3 * OFFSET];
        rep(a, 0, n) rep(b, a + 1, d) radix[sum[a] - sum[b] + sum[d] + 3 * OFFSET] += 6;
    }
    // case#2
    memset(radix, 0, sizeof(radix));
    rep(d, 0, n) {
        rep(e, d, n) rep(f, e, n) ans += radix[sum[d] + sum[e] + sum[f] + 3 * OFFSET] * mult(d, e, f);
        rep(a, 0, n) rep(b, a, d + 1) radix[sum[a] + sum[b] + sum[d] + 3 * OFFSET] += mult(a, b, d);
    }
    // case#4, 5, 6
    memset(radix, 0, sizeof(radix));
    rep(d, 0, n) {
        rep(e, d + 1, n) rep(f, e + 1, n) ans += radix[-sum[d] + sum[e] + sum[f] + 3 * OFFSET] * 2;
        rep(e, d + 1, n) rep(f, e, e + 1) ans += radix[-sum[d] + sum[e] + sum[f] + 3 * OFFSET];
        rep(e, d, d + 1) rep(f, e + 1, n) ans += radix[-sum[d] + sum[e] + sum[f] + 3 * OFFSET];
        rep(a, 0, n) rep(b, a + 1, d) {
            int c = d;
            radix[sum[a] - sum[b] + sum[c] + 3 * OFFSET] += 6;
        }
    }
    // case#8,9,10
    memset(radix, 0, sizeof(radix));
    rep(d, 0, n) {
        rep(e, d + 1, n) rep(f, e + 1, n) ans += radix[sum[d] - sum[e] + sum[f] + 3 * OFFSET];
        rep(a, 0, d) rep(b, a + 1, d) {
            int c = d;
            radix[sum[a] + sum[b] - sum[c] + 3 * OFFSET] += 12;
        }
        rep(a, 0, d) {
            int b = a, c = d;
            radix[sum[a] + sum[b] - sum[c] + 3 * OFFSET] += 6;
        }
        rep(a, 0, d) {
            int b = d, c = d;
            radix[sum[a] + sum[b] - sum[c] + 3 * OFFSET] += 6;
        }
    }
    // case#11, 14
    memset(radix, 0, sizeof(radix));
    rep(d, 0, n) {
        // query
        rep(e, d, d + 1) rep(f, e + 1, n) ans += radix[-sum[d] + sum[e] + sum[f] + 3 * OFFSET];
        rep(a, 0, d) {
            int b = d, c = d;
            radix[sum[a] + sum[b] - sum[c] + 3 * OFFSET] += 6;
        }
        rep(a, 0, d) rep(b, a, d) {
            int c = d;
            radix[sum[a] + sum[b] - sum[c] + 3 * OFFSET] += 6 * mult(a, b);
        }
    }
    // case#12, 13
    memset(radix, 0, sizeof(radix));
    rep(d, 0, n) {
        // query
        rep(e, d + 1, n) rep(f, e, n) ans += radix[-sum[d] + sum[e] + sum[f] + 3 * OFFSET] * mult(e, f);
        rep(a, 0, d) rep(b, a, d) {
            int c = d;
            radix[sum[a] + sum[b] - sum[c] + 3 * OFFSET] += 6 * mult(a, b);
        }
        rep(a, 0, d) {
            int b = d, c = d;
            radix[sum[a] + sum[b] - sum[c] + 3 * OFFSET] += 6;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n), sum(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum[i + 1] = sum[i] + a[i];
    }
    lint total = get_total(sum);
    vector<int> v;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            v.push_back(sum[j + 1] - sum[i]);
        }
    }
    map<int, int> mp;
    for (auto &x : v)
        mp[2 * x]++;
    for (auto &x : v) {
        if (x == 0)
            total += 2;
        if (mp.count(-x))
            total -= 3 * mp[-x];
    }

    cout << total / 6 << "\n";
}