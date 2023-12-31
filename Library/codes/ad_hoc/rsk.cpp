struct tableau {
	vector<vector<int>> H, T;
	int size() { return sz(H); }
};

tableau RSK_partial(int n, vector<int> a, int k) {
	tableau ans;
	for (int x = 0; x < n; x++) {
		int y = a[x];
		for (int i = 0; i <= ans.size() && i < k; i++) {
			if (i == ans.size()) {
				ans.H.emplace_back();
				ans.T.emplace_back();
			}
			int pos = lower_bound(all(ans.T[i]), y) - ans.T[i].begin();
			if (pos == sz(ans.T[i])) {
				ans.H[i].push_back(x);
				ans.T[i].push_back(y);
				break;
			} else {
				int yp = ans.T[i][pos];
				ans.T[i][pos] = y;
				y = yp;
			}
		}
	}
	return ans;
}

// Generate RSK Tableau in O(n sqrt n log n) time
// Tested (kinda poorly) in https://loj.ac/p/2265
tableau RSK(int n, vector<int> a) {
	int k = 0;
	while (k * k <= n)
		k++;
	auto tab = RSK_partial(n, a, k);
	reverse(all(a));
	auto TT = RSK_partial(n, a, k).T;
	reverse(all(a));
	for (int i = 0; i < n; i++) {
		a[i] = n - 1 - a[i];
	}
	auto HT = RSK_partial(n, a, k).H;
	assert(sz(HT) == sz(TT));
	for (int i = 0; i < sz(HT); i++) {
		assert(sz(HT[i]) == sz(TT[i]));
		if (sz(tab.H) < sz(HT[i])) {
			tab.H.resize(sz(HT[i]));
			tab.T.resize(sz(HT[i]));
		}
		for (int j = k; j < sz(HT[i]); j++) {
			tab.H[j].push_back(HT[i][j]);
			tab.T[j].push_back(TT[i][j]);
		}
	}
	return tab;
}
