#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 500005;
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

mt19937 rng(0x1557);
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }

struct bit {
	int tree[MAXN];
	void add(int x, int v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

vector<int> sweep(int n, vector<array<int, 4>> rec, vector<pi> qry) {
	vector<vector<array<int, 2>>> event(n + 1);
	vector<vector<array<int, 2>>> points(n + 1);
	vector<int> ans(sz(qry));
	memset(bit.tree, 0, sizeof(bit.tree));
	for (auto &[x1, x2, y1, y2] : rec) {
		event[x1].push_back({y1, +1});
		if (y2 < n)
			event[x1].push_back({y2 + 1, -1});
		if (x2 < n)
			event[x2 + 1].push_back({y1, -1});
		if (x2 < n && y2 < n)
			event[x2 + 1].push_back({y2 + 1, +1});
	}
	for (int i = 0; i < sz(qry); i++) {
		points[qry[i][0]].push_back({qry[i][1], i});
	}
	for (int i = 0; i <= n; i++) {
		for (auto &[p, v] : event[i])
			bit.add(p, v);
		for (auto &[p, j] : points[i])
			ans[j] = bit.query(p);
	}
	return ans;
}
template <typename T> struct StaticRangeModeQuery {
	StaticRangeModeQuery() = default;
	explicit StaticRangeModeQuery(const std::vector<T> &a) {
		_len = a.size();
		_block_size = std::max<int>(std::sqrt(_len), 1);
		_block_num = (_len + _block_size - 1) / _block_size;
		_val_num = a.size() + 2;
		_a.resize(_len);

		_start.assign(_val_num + 1, 0);
		for (int i = 0; i < _len; ++i) {
			_a[i] = a[i];
			++_start[_a[i]];
		}
		for (int i = 0; i < _val_num; ++i) {
			_start[i + 1] += _start[i];
		}
		_pos.resize(_len);
		_pos_inv.resize(_len);
		for (int i = _len; i--;) {
			int idx = --_start[_a[i]];
			_pos[idx] = i;
			_pos_inv[i] = idx;
		}

		_block_ans.assign((_block_num + 1) * (_block_num + 1), {0, 0});
		std::vector<int> cnt(_val_num);
		std::pair<int, int> cur_ans{0, 0};
		for (int left_block = 0; left_block <= _block_num; ++left_block) {
			cnt.assign(_val_num, 0);
			cur_ans = {0, 0};
			for (int right_block = left_block + 1; right_block <= _block_num; ++right_block) {
				int left_index = (right_block - 1) * _block_size;
				int right_index = std::min(_len, left_index + _block_size);
				for (int i = left_index; i < right_index; ++i) {
					std::pair<int, int> cand_ans{++cnt[_a[i]], _a[i]};
					if (cand_ans > cur_ans) {
						cur_ans.swap(cand_ans);
					}
				}
				_block_ans[left_block * (_block_num + 1) + right_block] = cur_ans;
			}
		}
	}

	std::pair<T, int> query(int l, int r) const {
		assert(0 <= l and l < r and r <= _len);
		int left_block = (l + _block_size - 1) / _block_size;
		int right_block = r / _block_size;

		auto [freq, val] = _block_ans[left_block * (_block_num + 1) + right_block];

		for (int i = l; i < std::min(r, left_block * _block_size); ++i) {
			int new_val = _a[i];
			int idx = _pos_inv[i];
			if (idx + freq < _start[new_val + 1] and _pos[idx + freq] < r) {
				do
					++freq;
				while (idx + freq < _start[new_val + 1] and _pos[idx + freq] < r);
				val = new_val;
			}
		}
		for (int i = r; i-- > std::max(l, right_block * _block_size);) {
			int new_val = _a[i];
			int idx = _pos_inv[i];
			if (idx - freq >= _start[new_val] and _pos[idx - freq] >= l) {
				do
					++freq;
				while (idx - freq >= _start[new_val] and _pos[idx - freq] >= l);
				val = new_val;
			}
		}
		return {69, freq};
	}
	std::pair<T, int> operator()(int l, int r) const { return query(l, r); }

  private:
	int _len, _block_size, _block_num, _val_num;
	std::vector<int> _a;
	std::vector<int> _pos;
	std::vector<int> _pos_inv;
	std::vector<int> _start;
	std::vector<std::pair<int, int>> _block_ans;
};
int main() {
	int n, q;
	rd(n);
	rd(q);
	vector<int> a(n);
	for (auto &x : a)
		rd(x);
	vector<pi> sorted;
	for (int i = 0; i < n; i++)
		sorted.push_back({a[i], i});
	sort(all(sorted));
	vector<array<int, 4>> swpOner, swpNext;
	for (int i = 0; i < n;) {
		int j = i;
		while (j < sz(sorted) && sorted[i][0] == sorted[j][0])
			j++;
		for (int k = i; k < j; k++) {
			int li = (i < k ? sorted[k - 1][1] : -1) + 1;
			int ri = (k + 1 < j ? sorted[k + 1][1] : n) - 1;
			swpOner.push_back({li, sorted[k][1], sorted[k][1] + 1, ri + 1});
			if (k + 1 < j)
				swpNext.push_back({0, sorted[k][1], sorted[k + 1][1] + 1, n});
		}
		i = j;
	}
	vector<pi> accm;
	for (int i = 0; i < q; i++) {
		int l, r;
		rd(l);
		rd(r);
		l--;
		accm.push_back({l, r});
	}
	auto onera = sweep(n, swpOner, accm);
	auto lowa = sweep(n, swpNext, accm);
	auto srmq = StaticRangeModeQuery(a);
	auto GetMaj = [&](int l, int r) { return srmq.query(l, r).second; };

	for (int i = 0; i < q; i++) {
		auto [l, r] = accm[i];
		int maj = GetMaj(l, r);
		int oner = onera[i];
		int cnt = r - l - lowa[i];
		if (r % 2 != l % 2) {
			if (maj * 2 <= r - l)
				wt(cnt);
			else
				wt(1);
		} else {
			if (maj * 2 <= r - l - 2 || maj == 1)
				wt(cnt - oner);
			else if (maj * 2 == r - l && cnt == 2)
				wt(0);
			else
				wt(1);
		}
		wt('\n');
	}
}