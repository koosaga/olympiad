#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 100005;
const lint inf = 2e18;

namespace atcoder {
// @return same with std::bit::bit_ceil
unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n))
        x *= 2;
    return x;
}

// @param n `1 <= n`
// @return same with std::bit::countr_zero
int countr_zero(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

// @param n `1 <= n`
// @return same with std::bit::countr_zero
constexpr int countr_zero_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x)))
        x++;
    return x;
}
#if __cplusplus >= 201703L

template <class S, auto op, auto e> struct segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>, "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>, "e must work as S()");

#else

template <class S, S (*op)(S, S), S (*e)()> struct segtree {

#endif

  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S> &v) : _n(int(v.size())) {
        size = (int)bit_ceil((unsigned int)(_n));
        log = countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++)
            d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1)
                sml = op(sml, d[l++]);
            if (r & 1)
                smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n)
            return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0)
                l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0)
            return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2))
                r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

} // namespace atcoder

lint TT(lint a, lint b) { return min(a + b, inf); }
lint UT(bool a, lint b) { return b; }
bool UU(bool a, bool b) { return a + b; }
lint ET() { return 0; }
bool EU() { return 0; }
lint T;

bool pred(lint v) { return v < T; }

vector<lint> dp[11];
int ans[MAXN][11];
bool fucked[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, p, q;
    cin >> n >> p >> q;
    vector<pi> a(n);
    vector<int> pos(n), rev(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i][0];
        a[i][1] = i;
    }
    {
        vector<pi> b = a;
        sort(all(b));
        for (int i = 0; i < n; i++) {
            int rnk = lower_bound(all(b), a[i]) - b.begin();
            pos[rnk] = i + 1;
        }
        pos.push_back(0);
        n++;

        for (int i = 0; i < n; i++)
            rev[pos[i]] = i;
    }
    cr(dp[0], n);
    for (int i = 0; i < n; i++)
        dp[0][i] = 1;
    for (int i = 1; i <= p; i++) {
        cr(dp[i], n);
        atcoder::segtree<lint, TT, ET> seg(n);
        for (int j = 0; j < n; j++) {
            seg.set(pos[j], dp[i - 1][pos[j]]);
            dp[i][pos[j]] = seg.prod(pos[j] + 1, n);
        }
    }
    vector<array<lint, 3>> upds;
    for (int i = 0; i < q; i++) {
        lint k;
        cin >> k;
        if (dp[p][pos[n - 1]] < k) {
            fucked[i] = 1;
            continue;
        }
        upds.push_back({n - 1, k, i});
    }
    for (int i = p; i > 0; i--) {
        atcoder::segtree<lint, TT, ET> seg(dp[i - 1]);
        int ptr = sz(upds);
        vector<array<lint, 3>> new_upds;
        for (int j = n - 1; j >= 0; j--) {
            seg.set(pos[j], 0);
            while (ptr > 0 && upds[ptr - 1][0] == j) {
                ptr--;
                auto [_, kval, idx] = upds[ptr];
                T = kval;
                int nxt = seg.max_right<pred>(pos[j]);
                ans[idx][p - i] = nxt;
                new_upds.push_back({rev[nxt], kval - seg.prod(pos[j], nxt), idx});
            }
        }
        upds = new_upds;
        sort(all(upds));
    }
    for (int i = 0; i < q; i++) {
        if (fucked[i]) {
            cout << "-1\n";
            continue;
        }
        for (int j = 0; j < p; j++) {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
}