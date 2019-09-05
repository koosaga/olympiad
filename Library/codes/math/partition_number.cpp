vector<pair<int, int>> gp;
lint P[MAXN+1] = {};
gp.emplace_back(0, 0);
for(int i = 1; gp.back().second <= MAXN; i++) {
	gp.emplace_back(i % 2 ? 1 : -1, i * (3*i - 1) / 2);
	gp.emplace_back(i % 2 ? 1 : -1, i * (3*i + 1) / 2);
}
P[1] = 1;
for(int n = 2; n <= MAXN; n++) {
	for(auto it : gp) if(n >= it.second) P[n] += P[n - it.second] * it.first + MOD;
	P[n] %= MOD;
}