#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

template <typename T> struct StaticRangeModeQuery {
	StaticRangeModeQuery() = default;
	explicit StaticRangeModeQuery(const std::vector<T> &a) {
		_len = a.size();
		_block_size = std::max<int>(std::sqrt(_len), 1);
		_block_num = (_len + _block_size - 1) / _block_size;
		_sorted = a;
		std::sort(_sorted.begin(), _sorted.end());
		_sorted.erase(std::unique(_sorted.begin(), _sorted.end()), _sorted.end());
		_val_num = _sorted.size();
		_a.resize(_len);

		_start.assign(_val_num + 1, 0);
		for (int i = 0; i < _len; ++i) {
			_a[i] = std::lower_bound(_sorted.begin(), _sorted.end(), a[i]) - _sorted.begin();
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
		return {_sorted[val], freq};
	}
	std::pair<T, int> operator()(int l, int r) const { return query(l, r); }

  private:
	int _len, _block_size, _block_num, _val_num;
	std::vector<T> _sorted;
	std::vector<int> _a;
	std::vector<int> _pos;
	std::vector<int> _pos_inv;
	std::vector<int> _start;
	std::vector<std::pair<int, int>> _block_ans;
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	StaticRangeModeQuery srmq(a);
	while (q--) {
		int l, r;
		cin >> l >> r;
		auto [k, v] = srmq.query(l, r);
		cout << k << " " << v << "\n";
	}
}