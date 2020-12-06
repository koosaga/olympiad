#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 80005;

/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Various self-explanatory methods for string hashing.
 * Status: tested
 */
#pragma once
#define rep(i, a, b) for(int i = a; i < (b); ++i)

// Arithmetic mod 2^64-1. 2x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse, where
// ABBA... and BAAB... of length 2^10 hash the same mod 2^64).
// "typedef ull H;" instead if you think test data is random,
// or work mod 10^9+7 if the Birthday paradox is not a problem.
struct H {
	typedef uint64_t ull;
	ull x; H(ull x=0) : x(x) {}
#define OP(O,A,B) H operator O(H o) { ull r = x; asm \
	(A "addq %%rdx, %0\n adcq $0,%0" : "+a"(r) : B); return r; }
	OP(+,,"d"(o.x)) OP(*,"mul %1\n", "r"(o.x) : "rdx")
	H operator-(H o) { return *this + ~o.x; }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lint randint(lint lb, lint ub){ return uniform_int_distribution<lint>(lb, ub)(rng); }
static H C = randint(1e10, 2e10) * 2 + 1;

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

vector<H> getHashes(string& str, int length) {
	if (sz(str) < length) return {};
	H h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h};
	rep(i,length,sz(str)) {
		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
	}
	return ret;
}

struct splitmix64_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

#include <bits/extc++.h>
template <typename K, typename V, typename Hash = splitmix64_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = splitmix64_hash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;

int n, k;
char str[MAXN];
int gp[MAXN];
hash_map<lint, int> mp;
bool cut[1 << 20];

bool distinct(vector<lint> &H){
    bool good = 1;
    for(auto &i : H){
        if(cut[i & 1048575]){
            good = 0;
            break;
        }
        cut[i & 1048575] = 1;
    }
    for(auto &i : H) cut[i & 1048575] = 0;
    return good;
}

int solve_whatsoever(vector<lint> H){
    if(distinct(H)) return sz(H) - k + 1;
	mp.clear();
	for(auto &i : H){
		auto it = mp.find(i);
		if(it != mp.end()) i = it->second;
		else{
			int val = sz(mp);
			mp[i] = val;
			i = val;
		}
	}
	int ret = 0;
	int badshits = 0;
	for(int j = 0; j < sz(H); j++){
		int qq = ++gp[H[j]];
		if(qq == 2) badshits++;
		if(j - k >= 0){
			auto acc = H[j - k];
			int qq = --gp[acc];
			if(qq == 1) badshits--;
		}
		if(j >= k - 1 && badshits == 0) ret++;
	}
	for(int j=0; j<k; j++) gp[H[sz(H) - 1 - j]]--;
	return ret;
}

int solve_hash(int l){
	static string s = str;
	static HashInterval hi(s);
	vector<lint> H;
	int ret = 0;
	for(int i=0; i<l; i++){
		if(i + l * k > n) break;
		vector<lint> H;
		for(int j = i; j + l <= n; j += l){
			lint val = hi.hashInterval(j, j + l).get();
			H.push_back(val);
		}
		ret += solve_whatsoever(H);
	}
	return ret;
}



namespace yosupo {

namespace internal {

std::vector<int> sa_naive(const std::vector<int>& s) {
    int n = int(s.size());
    std::vector<int> sa(n);
    std::iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&](int l, int r) {
        if (l == r) return false;
        while (l < n && r < n) {
            if (s[l] != s[r]) return s[l] < s[r];
            l++;
            r++;
        }
        return l == n;
    });
    return sa;
}

std::vector<int> sa_doubling(const std::vector<int>& s) {
    int n = int(s.size());
    std::vector<int> sa(n), rnk = s, tmp(n);
    std::iota(sa.begin(), sa.end(), 0);
    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int x, int y) {
            if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
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
template <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40>
std::vector<int> sa_is(const std::vector<int>& s, int upper) {
    int n = int(s.size());
    if (n == 0) return {};
    if (n == 1) return {0};
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
        if (i < upper) sum_l[i + 1] += sum_s[i];
    }

    auto induce = [&](const std::vector<int>& lms) {
        std::fill(sa.begin(), sa.end(), -1);
        std::vector<int> buf(upper + 1);
        std::copy(sum_s.begin(), sum_s.end(), buf.begin());
        for (auto d : lms) {
            if (d == n) continue;
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
            if (lms_map[v] != -1) sorted_lms.push_back(v);
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
                if (l == n || s[l] != s[r]) same = false;
            }
            if (!same) rec_upper++;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }

        auto rec_sa =
            sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

        for (int i = 0; i < m; i++) {
            sorted_lms[i] = lms[rec_sa[i]];
        }
        induce(sorted_lms);
    }
    return sa;
}

}  // namespace internal

std::vector<int> suffix_array(const std::vector<int>& s, int upper) {
    assert(0 <= upper);
    for (int d : s) {
        assert(0 <= d && d <= upper);
    }
    auto sa = internal::sa_is(s, upper);
    return sa;
}

template <class T> std::vector<int> suffix_array(const std::vector<T>& s) {
    int n = int(s.size());
    std::vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int l, int r) { return s[l] < s[r]; });
    std::vector<int> s2(n);
    int now = 0;
    for (int i = 0; i < n; i++) {
        if (i && s[idx[i - 1]] != s[idx[i]]) now++;
        s2[idx[i]] = now;
    }
    return internal::sa_is(s2, now);
}

std::vector<int> suffix_array(const std::string& s) {
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
template <class T>
std::vector<int> lcp_array(const std::vector<T>& s,
                           const std::vector<int>& sa) {
    int n = int(s.size());
    assert(n >= 1);
    std::vector<int> rnk(n);
    for (int i = 0; i < n; i++) {
        rnk[sa[i]] = i;
    }
    std::vector<int> lcp(n - 1);
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (h > 0) h--;
        if (rnk[i] == 0) continue;
        int j = sa[rnk[i] - 1];
        for (; j + h < n && i + h < n; h++) {
            if (s[j + h] != s[i + h]) break;
        }
        lcp[rnk[i] - 1] = h;
    }
    return lcp;
}

std::vector<int> lcp_array(const std::string& s, const std::vector<int>& sa) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return lcp_array(s2, sa);
}

}  // namespace yosupo

namespace ds{
	vector<int> sfx, rev, lcp;
	int spt[18][MAXN], lg[MAXN];

	int get_lcp(int s, int e){
		if(s == 2 * n + 1 || e == 2 * n + 1) return 0;
		s = rev[s]; e = rev[e];
		if(s > e) swap(s, e);
		int l = lg[e - s];
		return min(spt[l][e - 1], spt[l][s + (1<<l) - 1]);
	}

	int get_lcp_rev(int s, int e){
		return get_lcp(2*n+1-s, 2*n+1-e);
	}

	void prep(){
		string s = str;
		string r = s; reverse(all(r));
		s = s + "#" + r;
		sfx = yosupo::suffix_array(s);
		lcp = yosupo::lcp_array(s, sfx);
		rev.resize(sz(sfx));
		for(int i=0; i<sz(sfx); i++) rev[sfx[i]] = i;
		for(int i=1; i<MAXN; i++){
			lg[i] = lg[i-1];
			while((2 << lg[i]) <= i) lg[i]++;
		}
		for(int i=0; i<sz(sfx)-1; i++) spt[0][i] = lcp[i];
		for(int i=1; i<18; i++){
			for(int j=0; j<sz(sfx); j++){
				spt[i][j] = spt[i-1][j];
				if(j >= (1<<(i-1))) spt[i][j] = min(spt[i][j], spt[i-1][j-(1<<(i-1))]);
			}
		}
	}
}

struct sweep{
	int pos, s, e, x;
	bool operator<(const sweep &s)const{
		return pos < s.pos;
	}
};

struct seg{
    int tree[140000], tree2[140000];
    void add(int s, int e, int x, int ps, int pe, int p){
        if(e <= ps || pe <= s) return;
        if(s <= ps && pe <= e){
            tree2[p] += x;
            if(tree2[p] == 0){
                if(ps != pe) tree[p] = tree[2*p] + tree[2*p+1];
            }
            else tree[p] = pe - ps;
        }
        else{
            int pm = (ps+pe)/2;
            add(s,e,x,ps,pm,2*p);
            add(s,e,x,pm,pe,2*p+1);
            if(tree2[p] == 0 && ps != pe) tree[p] = tree[2*p] + tree[2*p+1];
        }
    }
}seg;

int cnt[MAXN];

int Go(vector<sweep> v, int sz){
	sort(all(v));
	int area = 0;
	int ret = 0;
	for(int i=0; i<sz(v); i++){
		if(i) ret += (v[i].pos - v[i-1].pos) * area;
		if(v[i].x == 1){
			for(int j = v[i].s; j <= v[i].e; j++){
				if(!cnt[j]) area++;
				cnt[j]++;
			}
		}
		else{
			for(int j = v[i].s; j <= v[i].e; j++){
				cnt[j]--;
				if(!cnt[j]) area--;
			}
		}
	}
	return ret;
}

int solve_real(int l){
	vector<sweep> ev;
	auto add_rect = [&](int sx, int ex, int sy, int ey){
		ev.push_back({sx, sy, ey, +1});
		ev.push_back({ex + 1, sy, ey, -1});
	};
	for(int i = 1; i < k; i++){
		int cutpos = -1;
		for(int j = 0; j + i * l <= n; j += l){
			int x = min(ds::get_lcp(j, j + i * l), l - 1);
			int y = min(ds::get_lcp_rev(j, j + i * l), l);
			int st = j - y, ed = j+x-l;
			if(st <= ed){
				int sx = st % l, ex = ed % l;
				int sy = j / l + i - k, ey = j / l - 1;
				sy = max(sy, 0);
				ey = min(ey, (n+1)/l - k);
				if(sy <= ey) add_rect(sx, ex, sy, ey);
			}
			cutpos = j + x;
		}
	}
	add_rect((n+1) % l, l - 1, (n+1) / l - k, (n+1)/l - k);
	return (1 + (n + 1) / l - k) * l - Go(ev, l);
}

int main(){
	scanf("%d %d %s",&n,&k,str);
	int ret = 0;
    ds::prep();
    for(int i=1; i<=n/k; i++){
        if(4 * i <= k) ret += solve_hash(i);
        else ret += solve_real(i);
    }
	cout << ret << endl;
}


