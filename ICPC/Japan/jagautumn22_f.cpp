#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int mod = 998244353;
const int MAXN = 300005;
struct mint {
    int val;
    mint() { val = 0; }
    mint(const lint &v) {
        val = (-mod <= v && v < mod) ? v : v % mod;
        if (val < 0)
            val += mod;
    }

    friend ostream &operator<<(ostream &os, const mint &a) { return os << a.val; }
    friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
    friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
    friend bool operator<(const mint &a, const mint &b) { return a.val < b.val; }

    mint operator-() const { return mint(-val); }
    mint &operator+=(const mint &m) {
        if ((val += m.val) >= mod)
            val -= mod;
        return *this;
    }
    mint &operator-=(const mint &m) {
        if ((val -= m.val) < 0)
            val += mod;
        return *this;
    }
    mint &operator*=(const mint &m) {
        val = (lint)val * m.val % mod;
        return *this;
    }
    friend mint ipow(mint a, lint p) {
        mint ans = 1;
        for (; p; p /= 2, a *= a)
            if (p & 1)
                ans *= a;
        return ans;
    }
    mint inv() const { return ipow(*this, mod - 2); }
    mint &operator/=(const mint &m) { return (*this) *= m.inv(); }

    friend mint operator+(mint a, const mint &b) { return a += b; }
    friend mint operator-(mint a, const mint &b) { return a -= b; }
    friend mint operator*(mint a, const mint &b) { return a *= b; }
    friend mint operator/(mint a, const mint &b) { return a /= b; }
    operator int64_t() const { return val; }
};

#include <algorithm>
#include <cassert>
#include <numeric>
#include <string>
#include <vector>

namespace yosupo {

namespace internal {

std::vector<int> sa_naive(const std::vector<int> &s) {
    int n = int(s.size());
    std::vector<int> sa(n);
    std::iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&](int l, int r) {
        if (l == r)
            return false;
        while (l < n && r < n) {
            if (s[l] != s[r])
                return s[l] < s[r];
            l++;
            r++;
        }
        return l == n;
    });
    return sa;
}

std::vector<int> sa_doubling(const std::vector<int> &s) {
    int n = int(s.size());
    std::vector<int> sa(n), rnk = s, tmp(n);
    std::iota(sa.begin(), sa.end(), 0);
    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int x, int y) {
            if (rnk[x] != rnk[y])
                return rnk[x] < rnk[y];
            int rx = x + k < n ? rnk[x + k] : -1;
            int ry = y + k < n ? rnk[y + k] : -1;
            return rx < ry;
        };
        std::sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        std::swap(tmp, rnk);
    }
    return sa;
}

// SA-IS, linear-time suffix array construction
// Reference:
// G. Nong, S. Zhang, and W. H. Chan,
// Two Efficient Algorithms for Linear Time Suffix Array Construction
template <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40> std::vector<int> sa_is(const std::vector<int> &s, int upper) {
    int n = int(s.size());
    if (n == 0)
        return {};
    if (n == 1)
        return {0};
    if (n == 2) {
        if (s[0] < s[1]) {
            return {0, 1};
        } else {
            return {1, 0};
        }
    }
    if (n < THRESHOLD_NAIVE) {
        return sa_naive(s);
    }
    if (n < THRESHOLD_DOUBLING) {
        return sa_doubling(s);
    }

    std::vector<int> sa(n);
    std::vector<bool> ls(n);
    for (int i = n - 2; i >= 0; i--) {
        ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
    }
    std::vector<int> sum_l(upper + 1), sum_s(upper + 1);
    for (int i = 0; i < n; i++) {
        if (!ls[i]) {
            sum_s[s[i]]++;
        } else {
            sum_l[s[i] + 1]++;
        }
    }
    for (int i = 0; i <= upper; i++) {
        sum_s[i] += sum_l[i];
        if (i < upper)
            sum_l[i + 1] += sum_s[i];
    }

    auto induce = [&](const std::vector<int> &lms) {
        std::fill(sa.begin(), sa.end(), -1);
        std::vector<int> buf(upper + 1);
        std::copy(sum_s.begin(), sum_s.end(), buf.begin());
        for (auto d : lms) {
            if (d == n)
                continue;
            sa[buf[s[d]]++] = d;
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        sa[buf[s[n - 1]]++] = n - 1;
        for (int i = 0; i < n; i++) {
            int v = sa[i];
            if (v >= 1 && !ls[v - 1]) {
                sa[buf[s[v - 1]]++] = v - 1;
            }
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        for (int i = n - 1; i >= 0; i--) {
            int v = sa[i];
            if (v >= 1 && ls[v - 1]) {
                sa[--buf[s[v - 1] + 1]] = v - 1;
            }
        }
    };

    std::vector<int> lms_map(n + 1, -1);
    int m = 0;
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms_map[i] = m++;
        }
    }
    std::vector<int> lms;
    lms.reserve(m);
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms.push_back(i);
        }
    }

    induce(lms);

    if (m) {
        std::vector<int> sorted_lms;
        sorted_lms.reserve(m);
        for (int v : sa) {
            if (lms_map[v] != -1)
                sorted_lms.push_back(v);
        }
        std::vector<int> rec_s(m);
        int rec_upper = 0;
        rec_s[lms_map[sorted_lms[0]]] = 0;
        for (int i = 1; i < m; i++) {
            int l = sorted_lms[i - 1], r = sorted_lms[i];
            int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
            int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
            bool same = true;
            if (end_l - l != end_r - r) {
                same = false;
            } else {
                while (l < end_l) {
                    if (s[l] != s[r]) {
                        break;
                    }
                    l++;
                    r++;
                }
                if (l == n || s[l] != s[r])
                    same = false;
            }
            if (!same)
                rec_upper++;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }

        auto rec_sa = sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

        for (int i = 0; i < m; i++) {
            sorted_lms[i] = lms[rec_sa[i]];
        }
        induce(sorted_lms);
    }
    return sa;
}

} // namespace internal

std::vector<int> suffix_array(const std::vector<int> &s, int upper) {
    assert(0 <= upper);
    for (int d : s) {
        assert(0 <= d && d <= upper);
    }
    auto sa = internal::sa_is(s, upper);
    return sa;
}

template <class T> std::vector<int> suffix_array(const std::vector<T> &s) {
    int n = int(s.size());
    std::vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int l, int r) { return s[l] < s[r]; });
    std::vector<int> s2(n);
    int now = 0;
    for (int i = 0; i < n; i++) {
        if (i && s[idx[i - 1]] != s[idx[i]])
            now++;
        s2[idx[i]] = now;
    }
    return internal::sa_is(s2, now);
}

std::vector<int> suffix_array(const std::string &s) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return internal::sa_is(s2, 255);
}

// Reference:
// T. Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park,
// Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its
// Applications
template <class T> std::vector<int> lcp_array(const std::vector<T> &s, const std::vector<int> &sa) {
    int n = int(s.size());
    assert(n >= 1);
    std::vector<int> rnk(n);
    for (int i = 0; i < n; i++) {
        rnk[sa[i]] = i;
    }
    std::vector<int> lcp(n - 1);
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (h > 0)
            h--;
        if (rnk[i] == 0)
            continue;
        int j = sa[rnk[i] - 1];
        for (; j + h < n && i + h < n; h++) {
            if (s[j + h] != s[i + h])
                break;
        }
        lcp[rnk[i] - 1] = h;
    }
    return lcp;
}

std::vector<int> lcp_array(const std::string &s, const std::vector<int> &sa) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return lcp_array(s2, sa);
}

// Reference:
// D. Gusfield,
// Algorithms on Strings, Trees, and Sequences: Computer Science and
// Computational Biology
template <class T> std::vector<int> z_algorithm(const std::vector<T> &s) {
    int n = int(s.size());
    if (n == 0)
        return {};
    std::vector<int> z(n);
    z[0] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        int &k = z[i];
        k = (j + z[j] <= i) ? 0 : std::min(j + z[j] - i, z[i - j]);
        while (i + k < n && s[k] == s[i + k])
            k++;
        if (j + z[j] < i + z[i])
            j = i;
    }
    z[0] = n;
    return z;
}

std::vector<int> z_algorithm(const std::string &s) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return z_algorithm(s2);
}

} // namespace yosupo
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, l;
    cin >> m >> n >> l;
    vector<int> a(n), b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    map<int, int> prv;
    vector<int> rk(n);
    for (int i = 0; i < n; i++) {
        rk[i] = (prv.count(a[i]) ? (i - prv[a[i]]) : -1);
        prv[a[i]] = i;
    }
    prv.clear();
    vector<int> fail(n + 1);
    int p = 0;
    auto getRank = [&](int x, int y) {
        if (prv.count(y) == 0)
            return -1;
        int j = x - prv[y];
        if (j > p)
            return -1;
        return j;
    };
    for (int i = 1; i < n; i++) {
        while (p && getRank(i, a[i]) != rk[p]) {
            p = fail[p];
        }
        if (getRank(i, a[i]) == rk[p]) {
            p++;
        }
        prv[a[i]] = i;
        fail[i + 1] = p;
    }
    prv.clear();
    p = 0;
    vector<int> ans;
    for (int i = 0; i < m; i++) {
        while (p && getRank(i, b[i]) != rk[p]) {
            p = fail[p];
        }
        if (getRank(i, b[i]) == rk[p]) {
            p++;
        }
        prv[b[i]] = i;
        if (p == n) {
            ans.push_back(i + 1 - p);
            p = fail[p];
        }
    }
    auto sa = yosupo::suffix_array(b);
    auto lcp = yosupo::lcp_array(b, sa);
    vector<int> rev(m);
    for (int i = 0; i < m; i++)
        rev[sa[i]] = i;
    for (auto &x : ans)
        x = rev[x];
    sort(all(ans));
    int mtch = sz(ans);
    for (int i = 1; i < sz(ans); i++) {
        int minval = *min_element(lcp.begin() + ans[i - 1], lcp.begin() + ans[i]);
        if (minval >= n)
            mtch--;
    }
    sort(all(a));
    a.resize(unique(all(a)) - a.begin());
    mint fact = 1;
    for (int i = 0; i < l - sz(a); i++)
        fact *= i + 1;
    cout << mint(mtch) * fact << endl;
}
