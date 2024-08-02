#include "light.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

vector<lint> f = {1};
lint sum = 1;

void prepare() {}

pair<long long, vector<long long>> join(long long p) {
	if (sum != 1)
		f.pop_back();
	sum += p;
	while (sum > 2 * f.back() + 1) {
		lint b = 2 * f.back() + 1;
		f.push_back(b);
	}
	if (sum > f.back())
		f.push_back(sum);
	vector<lint> ans;
	for (auto &x : f)
		ans.push_back(sum + 1 - x);
	reverse(all(ans));
	return make_pair(p, ans);
}

pair<long long, vector<long long>> leave(long long p) {
	sum -= p;
	vector<lint> g = {1};
	while (true) {
		lint nxt = 2 * g.back() + 1;
		auto it = --upper_bound(all(f), nxt + 2 * p);
		lint toput = min(*it, nxt + p) - p;
		//	cout << g.back() << " " << toput << endl;
		if (toput > g.back() && toput < sum) {
			g.push_back(toput);
		} else
			break;
	}
	if (g.back() < sum)
		g.push_back(sum);
	f = g;
	vector<lint> ans;
	for (auto &x : f)
		ans.push_back(sum + 1 - x);
	reverse(all(ans));
	return make_pair(p, ans);
}