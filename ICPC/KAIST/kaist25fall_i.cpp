#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	deque<int> dq[2];
	vector<pi> aseq;
	auto Do = [&](int A, int B) {
		assert(sz(dq[B]) <= n);
		int b = dq[A].front();
		dq[A].pop_front();
		dq[B].push_back(b);
		aseq.push_back({A + 1, B + 1});
	};
	for (int i = 0; i < 2; i++) {
		int z;
		cin >> z;
		while (z--) {
			int x;
			cin >> x;
			x--;
			dq[i].push_back(x);
		}
	}
	if (sz(dq[0]) > sz(dq[1]))
		Do(0, 1);
	if (sz(dq[0]) < sz(dq[1]))
		Do(1, 0);
	vector<int> cnt(n);
	for (auto &x : dq[0])
		cnt[x]++;
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (cnt[i] == 2) {
			while (j < n && cnt[j] != 0)
				j++;
			while (dq[0][0] != i)
				Do(0, 0);
			while (dq[1][0] != j)
				Do(1, 1);
			Do(0, 1);
			Do(1, 0);
			j++;
		}
	}
	{
		for (int i = 0; i < n; i++)
			assert(count(all(dq[0]), i) == 1 && count(all(dq[1]), i) == 1);
	}
	for (int A = 0; A < 2; A++) {
		int B = 1 - A;
		for (int i = 1; i < n; i++) {
			if (dq[A][i - 1] > dq[A][i]) {
				auto z = dq[B];
				int j = lower_bound(dq[A].begin(), dq[A].begin() + i, dq[A][i]) - dq[A].begin();
				for (int k = 0; k < i; k++)
					Do(A, A);
				Do(A, B);
				Do(B, A);
				for (int k = 0; k < n - 1; k++)
					Do(B, B);
				for (int k = 0; k < n - 1; k++)
					Do(A, A);
				Do(A, B);
				for (int k = 0; k < n - 1 - (i - j); k++)
					Do(A, A);
				Do(B, A);
				for (int k = 0; k < n - 1; k++)
					Do(B, B);
				for (int k = 0; k < n - 1 - j; k++)
					Do(A, A);
				assert(dq[B] == z);
			}
		}
	}
	assert(is_sorted(all(dq[0])));
	assert(is_sorted(all(dq[1])));
	cout << sz(aseq) << "\n";
	for (auto &[a, b] : aseq)
		cout << a << " " << b << "\n";
}