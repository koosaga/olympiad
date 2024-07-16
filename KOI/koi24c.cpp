#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int MAXN = 300005;

struct node {
	int front, fuck1, fuck2;
	bool operator<(const node &nd) const { return front > nd.front; }
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	vector<vector<int>> gph(n);
	vector<priority_queue<node>> pq(n);
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		gph[p - 1].push_back(i);
	}
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector<int> nxt(n + 1);
	for (int i = n - 1; i >= 0; i--) {
		for (auto &j : gph[i]) {
			if (sz(pq[i]) < sz(pq[j]))
				swap(pq[i], pq[j]);
			while (sz(pq[j])) {
				auto x = pq[j].top();
				pq[j].pop();
				pq[i].push(x);
			}
		}
		node ans;
		ans.front = a[i];
		ans.fuck1 = ans.fuck2 = a[i];
		while (sz(pq[i]) && pq[i].top().front < a[i]) {
			nxt[ans.fuck2] = pq[i].top().fuck1;
			ans.fuck2 = pq[i].top().fuck2;
			pq[i].pop();
		}
		pq[i].push(ans);
	}
	while (sz(pq[0])) {
		auto x = pq[0].top();
		pq[0].pop();
		while (x.fuck1)
			cout << x.fuck1 << "\n", x.fuck1 = nxt[x.fuck1];
	}
}