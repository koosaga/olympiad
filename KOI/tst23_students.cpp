#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

pair<int, vector<int>> complaint(int n, vector<int> L, vector<int> R) {
	vector<int> n1(n + 2, 0), d1(n + 2);
	vector<int> n2(n + 2, n + 1), d2(n + 2);
	for (int i = 0; i < sz(L); i++) {
		n1[R[i] + 1] = max(n1[R[i] + 1], L[i] + 1);
		n2[L[i] + 1] = min(n2[L[i] + 1], R[i] + 1);
	}
	for (int i = 1; i <= n; i++) {
		n1[i] = max(n1[i], n1[i - 1]);
		d1[i] = (n1[i] == 0 ? 0 : (d1[n1[i] - 1] + 1));
	}
	for (int i = n; i; i--) {
		n2[i] = min(n2[i], n2[i + 1]);
		d2[i] = (n2[i] == n + 1 ? 0 : (d2[n2[i] + 1] + 1));
	}
	int k = d1[n];
	vector<int> ans;
	for (int i = 1; i <= n; i++) {
		int u = d1[i - 1] + d2[i + 1];
		if (u + 1 == k) {
			ans.push_back(i - 1);
		}
	}
	return make_pair(k, ans);
}