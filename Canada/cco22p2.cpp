#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<lint> src(n - 1), snk(n), costs(n - 1);
	for (int i = 0; i < n; i++)
		cin >> snk[i];
	for (int i = 0; i < n - 1; i++)
		cin >> src[i];
	for (int i = 0; i < n - 1; i++)
		cin >> costs[i];
	vector<pi> flows(n - 1);
	vector<lint> remain(n - 1);
	for (int i = 0; i < n - 1; i++) {
		remain[i] = snk[i] - (i > 0 ? flows[i - 1][1] : 0);
		remain[i] = min(remain[i], src[i]);
		flows[i][0] = remain[i];
		flows[i][1] = min(snk[i + 1], src[i] - remain[i]);
		remain[i] = src[i] - flows[i][0] - flows[i][1];
	}
	vector<lint> todo(n + 1);
	auto route_flow = [&](int s, int e, lint x) {
		remain[s] -= x;
		if (s < e) {
			todo[s] += x;
			todo[e] -= x;
		} else {
			todo[e] -= x;
			todo[s] += x;
		}
	};
	vector<pi> stk;
	lint towrite = accumulate(all(remain), 0ll);
	lint insum = 0;
	for (int i = 0; i < n - 1; i++) {
		insum += remain[i];
		stk.push_back({i, remain[i]});
		while (sz(stk) && costs[i] > 0) {
			auto x = stk.back();
			stk.pop_back();
			lint delta = min(x[1], costs[i]);
			route_flow(x[0], i, delta);
			x[1] -= delta;
			insum -= delta;
			costs[i] -= delta;
			if (x[1])
				stk.push_back(x);
		}
		if (i + 1 < n - 1) {
			while (sz(stk) && insum > flows[i + 1][0]) {
				auto x = stk.back();
				stk.pop_back();
				lint delta = min(x[1], insum - flows[i + 1][0]);
				x[1] -= delta;
				insum -= delta;
				if (x[1])
					stk.push_back(x);
			}
		}
	}
	stk.clear();
	insum = 0;
	{
		lint foo = 0;
		for (int i = 0; i < n - 2; i++) {
			foo += todo[i];
			flows[i + 1][0] -= foo;
			flows[i][1] += foo;
		}
		fill(all(todo), 0);
	}
	for (int i = n - 2; i >= 0; i--) {
		insum += remain[i];
		stk.push_back({i, remain[i]});
		while (sz(stk) && costs[i] > 0) {
			auto x = stk.back();
			stk.pop_back();
			lint delta = min(x[1], costs[i]);
			route_flow(x[0], i, delta);
			x[1] -= delta;
			insum -= delta;
			costs[i] -= delta;
			if (x[1])
				stk.push_back(x);
		}
		if (i) {
			while (sz(stk) && insum > flows[i - 1][1]) {
				auto x = stk.back();
				stk.pop_back();
				lint delta = min(x[1], insum - flows[i - 1][1]);
				x[1] -= delta;
				insum -= delta;
				if (x[1])
					stk.push_back(x);
			}
		}
	}
	{
		lint foo = 0;
		for (int i = 0; i < n - 2; i++) {
			foo += todo[i];
			flows[i + 1][0] -= foo;
			flows[i][1] += foo;
		}
		fill(all(todo), 0);
	}

	if (accumulate(all(remain), 0ll)) {
		cout << "NO\n";
		return 0;
	}
	cout << "YES\n" << towrite << "\n";
	for (int i = 0; i < n - 1; i++) {
		cout << flows[i][0] << " " << src[i] - flows[i][0] - flows[i][1] << " " << flows[i][1] << "\n";
	}
}