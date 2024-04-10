#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

bool ans[39];
vector<pi> a;
int n;

void dfs(vector<char> arr, int p) {
	for (int i = p; i < sz(a); i++) {
		if (arr[a[i][0]] > arr[a[i][1]])
			swap(arr[a[i][0]], arr[a[i][1]]);
		if (arr[a[i][0]] == 1 && arr[a[i][1]] == 1) {
			arr[a[i][0]] = arr[a[i][1]] = 0;
			dfs(arr, i + 1);
			arr[a[i][0]] = arr[a[i][1]] = 2;
			dfs(arr, i + 1);
			return;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			bool ok = 1;
			for (int k = 0; k < i; k++)
				if (arr[k] == 2)
					ok = 0;
			for (int k = i; k < j; k++)
				if (arr[k] == 0)
					ok = 0;
			for (int k = j; k < n; k++)
				if (arr[k] == 2)
					ok = 0;
			if (ok)
				ans[j - i] ^= 1;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int m;
	cin >> n >> m;
	vector<char> arr(n, 1);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		a.push_back({u - 1, v - 1});
	}
	dfs(arr, 0);
	for (int i = 1; i <= n; i++)
		cout << ans[i] << " ";
}