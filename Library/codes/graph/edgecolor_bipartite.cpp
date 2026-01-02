
vector<int> split(int n, vector<pi> &edges) {
	if (sz(edges) == 0)
		return {};
	vector<int> gph(n, -1);
	vector<int> nxt(sz(edges) * 2), vis(sz(edges) * 2);
	auto reg = [&](int p, int v) {
		if (gph[p] == -1)
			gph[p] = v;
		else {
			nxt[gph[p]] = (v ^ 1);
			nxt[v] = gph[p] ^ 1;
			gph[p] = -1;
		}
	};
	for (int i = 0; i < sz(edges); i++) {
		auto [u, v] = edges[i];
		reg(u, 2 * i);
		reg(v + n / 2, 2 * i + 1);
	}
	vector<int> ans;
	for (int i = 0; i < sz(edges) * 2; i++) {
		if (!vis[i]) {
			for (int j = i; !vis[j]; j = nxt[j]) {
				ans.push_back(j >> 1);
				vis[j] = vis[j ^ 1] = 1;
			}
		}
	}
	return ans;
}

vector<int> EdgeColoringPowerOfTwo(int n, int k, vector<pi> edges) {
	vector<vector<pi>> matchings(2 * k - 1);
	vector<vector<int>> indices(2 * k - 1);
	matchings[0] = edges;
	cr(indices[0], sz(edges));
	iota(all(indices[0]), 0);
	for (int i = 0; i < k - 1; i++) {
		auto decomp = split(2 * n, matchings[i]);
		for (int j = 0; j < sz(matchings[i]); j++) {
			matchings[2 * i + 1 + j % 2].push_back(matchings[i][decomp[j]]);
			indices[2 * i + 1 + j % 2].push_back(indices[i][decomp[j]]);
		}
	}
	vector<int> ans(sz(edges));
	for (int i = 0; i < k; i++) {
		for (auto &j : indices[i + k - 1])
			ans[j] = i;
	}
	return ans;
}

vector<int> EdgeColoringRegular(int n, int k, vector<pi> edges) {
	/*cerr << n << " " << k << " " << sz(edges) << endl;
	for (auto &[u, v] : edges)
		cout << u << " " << v << endl;*/
	assert(k > 0);
	if ((k & -k) == k) {
		return EdgeColoringPowerOfTwo(n, k, edges);
	}
	if (k % 2 == 0) {
		auto decomp = split(2 * n, edges);
		vector<pi> sub[2];
		for (int i = 0; i < sz(decomp); i++) {
			sub[i % 2].push_back(edges[decomp[i]]);
		}
		vector<int> rec[2];
		rec[0] = EdgeColoringRegular(n, k / 2, sub[0]);
		int phi = 1;
		while (phi < k / 2)
			phi *= 2;
		vector<int> ans(sz(edges));
		int ptr = sz(sub[1]);
		for (int i = 0; i < sz(decomp) / 2; i++) {
			ans[decomp[2 * i]] = rec[0][i];
			if (rec[0][i] >= k - phi) {
				sub[1].push_back(edges[decomp[2 * i]]);
			}
		}
		rec[1] = EdgeColoringPowerOfTwo(n, phi, sub[1]);
		for (int i = 0; i < sz(decomp); i++) {
			if (i % 2 == 0 && ans[decomp[i]] >= k - phi) {
				ans[decomp[i]] = rec[1][ptr++] + k - phi;
			} else if (i % 2 == 1) {
				ans[decomp[i]] = rec[1][i / 2] + k - phi;
			}
		}
		return ans;
	}
	int t = 0;
	while ((1 << t) < k * n)
		t++;
	vector<array<int, 4>> todnc;
	int alph = (1 << t) / k;
	int beta = (1 << t) - k * alph; // < k
	for (int i = 0; i < sz(edges); i++) {
		todnc.push_back({edges[i][0], edges[i][1] + n, alph, i});
	}
	if (beta > 0) {
		for (int i = 0; i < n; i++) {
			todnc.push_back({i, i + n, beta, -1});
		}
	}
	for (int i = 0; i < t; i++) {
		vector<pi> toeuler;
		vector<array<int, 4>> sub[2];
		for (auto &[u, v, k, idx] : todnc) {
			if (k % 2)
				toeuler.push_back({u, v - n});
		}
		sub[1] = sub[0];
		auto pth = split(2 * n, toeuler);
		vector<int> parity(sz(toeuler));
		for (int i = 1; i < sz(pth); i += 2)
			parity[pth[i]] = 1;
		int ptr = 0, bal = 0;
		for (auto &[u, v, k, idx] : todnc) {
			int l = k / 2, r = k / 2;
			if (k % 2) {
				if (parity[ptr++])
					r++;
				else
					l++;
			}
			if (idx == -1)
				bal += l - r;
			if (l)
				sub[0].push_back({u, v, l, idx});
			if (r)
				sub[1].push_back({u, v, r, idx});
		}
		if (bal >= 0)
			todnc = sub[1];
		else
			todnc = sub[0];
	}
	vector<int> ans(sz(edges), -1);
	for (auto &[u, v, z, idx] : todnc) {
		assert(z == 1 && idx != -1);
		ans[idx] = k - 1;
	}
	vector<pi> sub;
	for (int i = 0; i < sz(edges); i++) {
		if (ans[i] == -1)
			sub.push_back(edges[i]);
	}
	int piv = 0;
	auto sol = EdgeColoringRegular(n, k - 1, sub);
	for (int i = 0; i < sz(edges); i++) {
		if (ans[i] == -1)
			ans[i] = sol[piv++];
	}
	return ans;
}

vector<int> EdgeColoring(int l, int r, vector<pi> edges) {
	if (sz(edges) == 0)
		return vector<int>();
	vector<int> d[2];
	cr(d[0], l);
	cr(d[1], r);
	for (auto &[x, y] : edges)
		d[0][x]++, d[1][y]++;
	int k = max(*max_element(all(d[0])), *max_element(all(d[1])));
	for (int i = 0; i < 2; i++) {
		vector<int> ord(l);
		iota(all(ord), 0);
		sort(all(ord), [&](int x, int y) { return d[i][x] < d[i][y]; });
		vector<int> maps(l);
		int nl = 0;
		for (int j = 0; j < sz(ord);) {
			int nxt = j, sum = 0;
			while (nxt < sz(ord) && sum + d[i][ord[nxt]] <= k) {
				sum += d[i][ord[nxt]];
				maps[ord[nxt]] = nl;
				nxt++;
			}
			nl++;
			j = nxt;
		}
		for (auto &e : edges) {
			e[i] = maps[e[i]];
		}
		l = nl;
		swap(l, r);
	}
	int n = max(l, r);
	cr(d[0], n);
	cr(d[1], n);
	for (auto &[x, y] : edges)
		d[0][x]++, d[1][y]++;
	int j = 0;
	int orig = sz(edges);
	for (int i = 0; i < n; i++) {
		while (d[0][i] < k) {
			while (d[1][j] == k)
				j++;
			edges.push_back({i, j});
			d[0][i]++;
			d[1][j]++;
		}
	}
	auto sol = EdgeColoringRegular(n, k, edges);
	sol.resize(orig);
	return sol;
}