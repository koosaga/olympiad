#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> m >> n;
    if(n == 0){
cout << "0\n";
    return 0;
    }
	vector<int> indeg(n), a(n, -1);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		a[u] = v;
		indeg[v]++;
	}
	queue<int> que;
	for (int i = 0; i < n; i++) {
		if (indeg[i] == 0)
			que.push(i);
	}
	vector<int> ord;
	while (sz(que)) {
		int x = que.front();
		que.pop();
		ord.push_back(x);
		if (a[x] == -1)
			continue;
		indeg[a[x]]--;
		if (indeg[a[x]] == 0) {
			que.push(a[x]);
		}
	}
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		if (indeg[i]) {
			vector<int> v;
			for (int j = i; indeg[j]; j = a[j]) {
				v.push_back(j);
				indeg[j] = 0;
			}
			for (auto &x : v)
				ans[x] = sz(v);
		}
        if(a[i] == -1) ans[i] = 1;
	}
	reverse(all(ord));
	for (auto &x : ord) {
		if (~a[x])
			ans[x] = ans[a[x]] + 1;
	}
	cout << max(1, *max_element(all(ans))) << "\n";
}