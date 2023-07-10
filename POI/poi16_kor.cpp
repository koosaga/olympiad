#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

struct node {
	lint sum;
	vector<int> iseq;
	bool operator<(const node &nd) const {
		if (sum != nd.sum)
			return sum > nd.sum;
		return iseq > nd.iseq;
	}
	int spos;
	node() {
		sum = 0;
		spos = -1;
	}
	node insert(pi x, int idx) {
		node ret = *this;
		ret.sum += x[0];
		ret.spos = idx;
		ret.iseq.insert(lower_bound(all(ret.iseq), x[1]), x[1]);
		return ret;
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0];
		a[i][1] = i;
	}
	sort(all(a));
	priority_queue<node> pq;
	pq.push(node());
	for (int i = 0; i < m; i++) {
		auto x = pq.top();
		pq.pop();
		if (i == m - 1) {
			cout << x.sum << "\n";
			for (auto &z : x.iseq)
				cout << z + 1 << " ";
			cout << "\n";
			return 0;
		}
		if (x.spos + 1 < n) {
			auto y = x.insert(a[x.spos + 1], x.spos + 1);
			pq.push(y);
		}
		if (x.spos >= 0) {
			x.iseq.erase(find(all(x.iseq), a[x.spos][1]));
			x.sum -= a[x.spos][0];
			if (x.spos + 1 < n) {
				x.spos++;
				pq.push(x.insert(a[x.spos], x.spos));
			}
		}
	}
}