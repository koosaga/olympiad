#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 530000;
const int offset = 10;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<array<int, 3>> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
		a[i][2] = i;
	}
	int curmax = a[0][1];
	vector<pi> seg;
	vector<int> sum = {0};
	for (int i = 1; i < n; i++) {
		if (curmax < a[i][0]) {
			seg.emplace_back(curmax, a[i][0]);
			int prv = sum.back();
			sum.push_back(prv + a[i][0] - curmax);
		}
		curmax = max(curmax, a[i][1]);
	}
	int pos = 0;
	lint ret = 0;
	for (int i = 0; i < k; i++) {
		int x;
		cin >> x;
		x--;
		int l = a[pos][0], r = a[x][1];
		if (l > r)
			swap(l, r);
		auto it1 = lower_bound(all(seg), pi(l, -1)) - seg.begin();
		auto it2 = lower_bound(all(seg), pi(r, -1)) - seg.begin();
		ret += sum[it2] - sum[it1];
		pos = x;
	}
	cout << ret << "\n";
}