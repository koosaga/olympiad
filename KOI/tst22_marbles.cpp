#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;

std::vector<long long> find_minimum_costs(int N, std::vector<int> A, std::vector<int> B) {
	vector<int> ptr(sz(A));
	vector<lint> dp(N + 1);
	dp[0] = -1e18;
	dp[1] = 0;
	{
		vector<lint> v;
		for(int i = 0; i < sz(ptr); i++) v.push_back(A[i] + B[i]);
		sort(all(v));
		dp[2] = v[1];
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i = 0; i < sz(ptr); i++){
		pq.emplace(dp[ptr[i] + 1] + 1ll * A[i] * (ptr[i] + 1) + B[i], i);
	}
	lint ret = 0;
	auto advance = [&](int thresh){
		pi minv = pq.top();
		pq.pop();
		int i = minv.second;
		ptr[i]++;
		ret = max(ret, dp[ptr[i]] + 1ll * A[i] * ptr[i] + B[i]);
		return i;
	};
	for(int i = 1; i <= N; i++){
		int j = advance(i);
		if(i >= 3) dp[i] = ret;
		pq.emplace(dp[ptr[j] + 1] + 1ll * A[j] * (ptr[j] + 1) + B[j], j);
	}
	dp.erase(dp.begin());
	return dp;
}
