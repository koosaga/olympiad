// use when TLE
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
typedef pair<int, int> pi;
const int MAXN = 200005;

namespace fastio {
static constexpr uint32_t SZ = 1 << 17;
char ibuf[SZ];
char obuf[SZ];
uint32_t pil = 0, pir = 0, por = 0;

struct Pre {
	char num[40000];
	constexpr Pre() : num() {
		for (int i = 0; i < 10000; i++) {
			int n = i;
			for (int j = 3; j >= 0; j--) {
				num[i * 4 + j] = n % 10 + '0';
				n /= 10;
			}
		}
	}
} constexpr pre;

__attribute__((target("avx2"), optimize("O3"))) inline void load() {
	memcpy(ibuf, ibuf + pil, pir - pil);
	pir = pir - pil + fread(ibuf + pir - pil, 1, SZ - pir + pil, stdin);
	pil = 0;
}

__attribute__((target("avx2"), optimize("O3"))) inline void flush() {
	fwrite(obuf, 1, por, stdout);
	por = 0;
}

inline void rd(char &c) { c = ibuf[pil++]; }

template <typename T> __attribute__((target("avx2"), optimize("O3"))) inline void rd(T &x) {
	if (pil + 32 > pir)
		load();
	char c;
	do
		rd(c);
	while (c < '-');
	bool minus = 0;
	if constexpr (is_signed<T>::value) {
		if (c == '-') {
			minus = 1;
			rd(c);
		}
	}
	x = 0;
	while (c >= '0') {
		x = x * 10 + (c & 15);
		rd(c);
	}
	if constexpr (is_signed<T>::value) {
		if (minus)
			x = -x;
	}
}

inline void wt(char c) { obuf[por++] = c; }
template <typename T> __attribute__((target("avx2"), optimize("O3"))) inline void wt(T x) {
	if (por + 32 > SZ)
		flush();
	if (!x) {
		wt('0');
		return;
	}
	if constexpr (is_signed<T>::value) {
		if (x < 0) {
			wt('-');
			x = -x;
		}
	}
	if (x >= 10000000000000000) {
		uint32_t r1 = x % 100000000;
		uint64_t q1 = x / 100000000;
		if (x >= 1000000000000000000) {
			uint32_t n1 = r1 % 10000;
			uint32_t n2 = r1 / 10000;
			uint32_t n3 = q1 % 10000;
			uint32_t r2 = q1 / 10000;
			uint32_t n4 = r2 % 10000;
			uint32_t q2 = r2 / 10000;
			memcpy(obuf + por + 15, pre.num + (n1 << 2), 4);
			memcpy(obuf + por + 11, pre.num + (n2 << 2), 4);
			memcpy(obuf + por + 7, pre.num + (n3 << 2), 4);
			memcpy(obuf + por + 3, pre.num + (n4 << 2), 4);
			memcpy(obuf + por, pre.num + (q2 << 2) + 1, 3);
			por += 19;
		} else if (x >= 100000000000000000) {
			uint32_t n1 = r1 % 10000;
			uint32_t n2 = r1 / 10000;
			uint32_t n3 = q1 % 10000;
			uint32_t r2 = q1 / 10000;
			uint32_t n4 = r2 % 10000;
			uint32_t q2 = r2 / 10000;
			uint32_t q3 = (q2 * 205) >> 11;
			uint32_t r3 = q2 - q3 * 10;
			memcpy(obuf + por + 14, pre.num + (n1 << 2), 4);
			memcpy(obuf + por + 10, pre.num + (n2 << 2), 4);
			memcpy(obuf + por + 6, pre.num + (n3 << 2), 4);
			memcpy(obuf + por + 2, pre.num + (n4 << 2), 4);
			obuf[por + 1] = '0' + r3;
			obuf[por + 0] = '0' + q3;
			por += 18;
		} else {
			uint32_t n1 = r1 % 10000;
			uint32_t n2 = r1 / 10000;
			uint32_t n3 = static_cast<uint32_t>(q1) % 10000;
			uint32_t r2 = static_cast<uint32_t>(q1) / 10000;
			uint32_t n4 = r2 % 10000;
			uint32_t q2 = r2 / 10000;
			memcpy(obuf + por + 13, pre.num + (n1 << 2), 4);
			memcpy(obuf + por + 9, pre.num + (n2 << 2), 4);
			memcpy(obuf + por + 5, pre.num + (n3 << 2), 4);
			memcpy(obuf + por + 1, pre.num + (n4 << 2), 4);
			obuf[por + 0] = '0' + q2;
			por += 17;
		}
	} else {
		int i = 8;
		char buf[12];
		while (x >= 10000) {
			memcpy(buf + i, pre.num + (x % 10000) * 4, 4);
			x /= 10000;
			i -= 4;
		}
		if (x < 100) {
			if (x < 10) {
				wt(char('0' + x));
			} else {
				obuf[por + 0] = '0' + x / 10;
				obuf[por + 1] = '0' + x % 10;
				por += 2;
			}
		} else {
			if (x < 1000) {
				memcpy(obuf + por, pre.num + (x << 2) + 1, 3);
				por += 3;
			} else {
				memcpy(obuf + por, pre.num + (x << 2), 4);
				por += 4;
			}
		}
		memcpy(obuf + por, buf + i + 4, 8 - i);
		por += 8 - i;
	}
}

struct Dummy {
	Dummy() { atexit(flush); }
} dummy;

} // namespace fastio
using fastio::rd;
using fastio::wt;

struct point {
	int x, y, idx;
} a[MAXN];

int n, pos[MAXN];
lint ccw(const point &a, const point &b) { return 1ll * a.x * b.y - 1ll * b.x * a.y; }
lint ccw(const point &a, const point &b, const point &c) { return 1ll * (b.x - a.x) * (c.y - a.y) - 1ll * (c.x - a.x) * (b.y - a.y); }
bool operator<(const point &a, const point &b) { return ccw(a, b) < 0; }

bool cmp(int p, int q) {
	if (ccw(a[p], a[q]) > 0) {
		swap(p, q);
		return ccw(a[p], a[p + 1], a[q]) < 0;
	}
	return ccw(a[p], a[p + 1], a[q]) > 0;
}

int queries[MAXN];

struct ds {
	int H[MAXN], sz;
	int rev[MAXN];
	void swp(int a, int b) {
		swap(rev[H[a]], rev[H[b]]);
		swap(H[a], H[b]);
	}
	void insert(int x) {
		H[++sz] = x;
		rev[x] = sz;
		for (int j = sz; j > 1; j >>= 1) {
			if (!cmp(H[j / 2], H[j])) {
				swp(j / 2, j);
			} else
				break;
		}
	}
	void erase(int x) {
		for (int i = rev[x]; i > 1; i >>= 1)
			swp(i / 2, i);
		swp(1, sz--);
		for (int i = 1; 2 * i <= sz;) {
			if (2 * i + 1 <= sz && cmp(H[2 * i + 1], H[2 * i])) {
				if (!cmp(H[i], H[2 * i + 1]))
					swp(i, 2 * i + 1), i = 2 * i + 1;
				else
					break;
			} else {
				if (!cmp(H[i], H[2 * i]))
					swp(i, 2 * i), i = 2 * i;
				else
					break;
			}
		}
	}
	int top() { return H[1]; }
} DS;

__attribute__((target("avx2"), optimize("O3"))) int main() {
	rd(n);
	for (int i = 0; i < n; i++) {
		rd(a[i].x);
		rd(a[i].y);
		a[i].idx = i + 1;
	}
	{
		lint sum = 0;
		for (int i = 0; i < n; i++) {
			sum += ccw(a[i], a[(i + 1) % n]);
		}
		if (sum < 0)
			reverse(a, a + n);
	}
	int min_pos = min_element(a, a + n) - a;
	rotate(a, a + min_pos, a + n);
	int N = n;
	int c = 0;
	{
		vector<point> v;
		int max_pos = max_element(a, a + n) - a;
		for (int i = 0; i <= max_pos; i++) {
			if (sz(v) > 1 && ccw(v[sz(v) - 2], v.back()) > 0 && ccw(v.back(), a[i]) > 0) {
				v.pop_back();
			}
			v.push_back(a[i]);
		}
		n = sz(v);
		for (int i = 0; i < n; i++)
			a[i] = v[i];
		for (int i = 0; i < n; i++)
			v[i].idx = i;
		sort(v.begin(), v.end());
		int j = 0;
		for (int i = 0; i < n;) {
			while (j < n && ccw(v[i], v[j]) == 0) {
				pos[v[j++].idx] = c;
			}
			c++;
			i = j;
		}
	}
	vector<vector<int>> in(c), out(c);
	for (int i = 0; i < n - 1; i++) {
		if (pos[i] < pos[i + 1]) {
			in[pos[i]].push_back(i);
			out[pos[i + 1]].push_back(i);
		}
	}
	for (int i = 0; i < c - 1; i++) {
		if (!sz(in[i]) && !sz(out[i])) {
			queries[i] = queries[i - 1];
			continue;
		}
		for (auto &j : in[i]) {
			DS.insert(j);
		}
		for (auto &j : out[i]) {
			DS.erase(j);
		}
		queries[i] = DS.top();
	}
	vector<int> chk(N + 1);
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		int p = pos[i];
		bool bad = 0;
		if (p != c - 1) {
			int t = queries[p];
			if (ccw(a[t + 1], a[t], a[i]) < 0) {
				bad = 1;
			}
		}
		if (!bad && p != 0) {
			int t = queries[p - 1];
			if (ccw(a[t + 1], a[t], a[i]) < 0) {
				bad = 1;
			}
		}
		if (!bad)
			chk[a[i].idx] = 1, cnt++;
	}
	wt(cnt);
	wt('\n');
	for (int i = 0; i < N; i++) {
		if (chk[i + 1]) {
			wt(i + 1);
			wt(' ');
		}
	}
}