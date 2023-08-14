#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using lint = long long;
using pi = array<lint, 2>;

int n, m;
vector<array<lint, 3>> a;

bool Do(vector<lint> l, vector<lint> r, vector<array<lint, 3>> intv, lint K) {
	for (int i = 1; i < l.size(); i++)
		l[i] = min(l[i], l[i - 1]);
	for (int i = 1; i < r.size(); i++)
		r[i] = min(r[i], r[i - 1]);
	l.push_back(0);
	r.push_back(0);
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	int ptr = 0;
	vector<lint> opt(r.size());
	for (int i = 0; i + 1 < l.size(); i++) {
		while (ptr < intv.size() && intv[ptr][0] <= i) {
			pq.push({intv[ptr][1], intv[ptr][2]});
			ptr++;
		}
		while (l[i + 1] < K) {
			if (pq.empty())
				return 0;
			auto nxt = pq.top();
			pq.pop();
			lint dx = min(K - l[i + 1], nxt[1]);
			opt[nxt[0]] += dx;
			nxt[1] -= dx;
			K -= dx;
			if (nxt[1])
				pq.push(nxt);
		}
	}
	for (int i = opt.size() - 2; i >= 0; i--)
		opt[i] += opt[i + 1];
	for (int i = 0; i < r.size(); i++) {
		if (opt[i] > r[i])
			return false;
	}
	return true;
}

lint cnt[MAXN];
int maxpos;

bool trial(lint x) {
	lint mx = cnt[maxpos];
	for (lint i = mx - x; i <= mx - x + 1 && i <= x; i++) {
		vector<lint> surp(n - 1);
		for (int j = 0; j < n - 1; j++) {
			surp[j] = x + i - cnt[j + 1];
			surp[j] /= 2;
		}
		// number of reversal
		vector<array<lint, 3>> intv;
		for (int k = 0; k < m; k++) {
			if (a[k][0] <= maxpos && a[k][1] > maxpos) {
				intv.push_back({a[k][0] - 1, n - a[k][1], a[k][2]});
			}
		}
		vector<lint> l = {lint(1e18)};
		vector<lint> r = {lint(1e18)};
		for (int k = 0; k < maxpos - 1; k++)
			l.push_back(surp[k]);
		for (int k = n - 2; k >= maxpos; k--)
			r.push_back(surp[k]);
		if (Do(l, r, intv, i))
			return true;
	}

	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	a.resize(m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> a[i][j];
		}
		if (a[i][0] > a[i][1])
			swap(a[i][0], a[i][1]);
		cnt[a[i][0]] += a[i][2];
		cnt[a[i][1]] -= a[i][2];
	}
	sort(a.begin(), a.end());
	for (int i = 1; i <= n; i++)
		cnt[i] += cnt[i - 1];
	maxpos = max_element(cnt + 1, cnt + n + 1) - cnt;
	lint s = 0, e = cnt[maxpos];
	while (s != e) {
		lint m = (s + e) / 2;
		if (trial(m))
			e = m;
		else
			s = m + 1;
	}
	cout << s << endl;
}
