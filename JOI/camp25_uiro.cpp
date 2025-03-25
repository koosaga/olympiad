#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

struct node {
	int sum, pmin;
	node() { sum = pmin = 0; }
	node(int x) {
		sum = x;
		pmin = min(0, x);
	}
	node(int x, int y) { sum = x, pmin = y; }
	node operator+(const node &nd) const { return node(sum + nd.sum, min(pmin, sum + nd.pmin)); }
};

const int MAXA = 101;
const int MAXT = 530000;

int lim;
struct seg {
	node tree[MAXT];
	void init(vector<int> &a) {
		for (lim = 1; lim <= sz(a); lim <<= 1)
			;
		for (int i = 0; i < sz(a); i++)
			tree[i + lim] = node(a[i]);
		for (int i = lim - 1; i; i--)
			tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
	void upd(int x, node v) {
		x += lim;
		tree[x] = v;
		while (x > 1) {
			x >>= 1;
			tree[x] = tree[2 * x] + tree[2 * x + 1];
		}
	}
	node query(int s, int e) {
		e--;
		s += lim;
		e += lim;
		node L, R;
		while (s < e) {
			if (s % 2 == 1)
				L = L + tree[s++];
			if (e % 2 == 0)
				R = tree[e--] + R;
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			L = L + tree[s];
		return L + R;
	}
} sg[2];

struct pkg {
	node L, R;
	int pos;
};
#include <bits/stdc++.h>
using namespace std;

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

__attribute__((target("avx2"), optimize("O3"))) int _readInt() {
	int x;
	rd(x);
	return x;
}

__attribute__((target("avx2"), optimize("O3"))) int main() {
	int n, q;
	n = _readInt();
	vector<int> a(n);
	vector<array<int, MAXA>> sum(n + 1);
	for (auto &x : a)
		x = _readInt();
	for (int i = 0; i < n; i++) {
		sum[i + 1] = sum[i];
		sum[i + 1][a[i]]++;
	}
	for (int i = 0; i < 2; i++) {
		vector<int> b = a;
		for (auto &j : b) {
			if (j <= i)
				j *= -1;
		}
		sg[i].init(b);
	}
	q = _readInt();
	vector<int> ans(q);
	vector<pi> queries(q);
	vector<node> currents(q);
	for (auto &[l, r] : queries) {
		l = _readInt();
		r = _readInt();
		l--;
	}
	for (int i = 1; i < MAXA; i++) {
		int prev = (i - 1) % 2, curr = i % 2;
		pkg LL[50], RR[50];
		int lsz, rsz;
		for (int j = 0; j < q; j++) {
			int l = queries[j][0], r = queries[j][1];
			auto binsearch = [&](int s, int e) {
				if (s == e)
					return s;
				int is = s, ie = e;
				s += lim;
				e--;
				e += lim;
				lsz = rsz = 0;
				while (s < e) {
					if (s % 2 == 1) {
						LL[lsz++] = {sg[prev].tree[s], sg[curr].tree[s], s};
						s++;
					}
					if (e % 2 == 0) {
						RR[rsz++] = {sg[prev].tree[e], sg[curr].tree[e], e};
						e--;
					}
					s >>= 1;
					e >>= 1;
				}
				if (s == e)
					LL[lsz++] = {sg[prev].tree[s], sg[curr].tree[s], s};
				for (int j = rsz - 1; j >= 0; j--)
					LL[lsz++] = RR[j];
				LL[lsz++] = {node(0), node(0), -1};
				for (int i = lsz - 2; i >= 0; i--)
					LL[i].R = LL[i].R + LL[i + 1].R;

				node cur = currents[j];
				if ((cur + LL[0].R).pmin >= 0)
					return is;
				for (int i = 0; i < lsz - 1; i++) {
					if ((cur + LL[i].L + LL[i + 1].R).pmin >= 0) {
						int ptr = LL[i].pos;
						node LBND = cur, RBND = LL[i + 1].R;
						while (ptr < lim) {
							node putL = sg[prev].tree[2 * ptr];
							node putR = sg[curr].tree[2 * ptr + 1];
							if ((LBND + putL + putR + RBND).pmin >= 0) {
								ptr = 2 * ptr;
								RBND = putR + RBND;
							} else {
								ptr = 2 * ptr + 1;
								LBND = LBND + putL;
							}
						}
						currents[j] = LBND + sg[prev].tree[ptr];
						return ptr + 1 - lim;
					}
					cur = cur + LL[i].L;
				}
				assert(0);
			};
			int s = binsearch(l, r);
			queries[j][0] = s;
			ans[j] += sum[r][i] - sum[s][i];
		}
		for (int j = 0; j < n; j++) {
			if (a[j] == i || a[j] == i + 1) {
				sg[prev].upd(j, node(-a[j]));
			}
		}
	}
	for (auto &x : ans) {
		wt(x);
		wt('\n');
	}
}