#include "paint.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int mod = 1e9 + 7;

vector<int> use[MAXN]; // which worker can work on the color

int minimumInstructions(
		int N, int M, int K, std::vector<int> C,
		std::vector<int> A, std::vector<std::vector<int>> B) {
	for(int i=0; i<M; i++){
		for(auto &j : B[i]){
			use[j].push_back(i);
		}
	}
	vector<pi> op(M);
	for(int i=0; i<M; i++){
		op[i] = pi(-1e9, 0);
	}
	auto insert = [&](int i, int time){
		if(op[i].first + 1 == time) op[i] = pi(time, op[i].second + 1);
		else op[i] = pi(time, 1);
		if(op[i].second >= M) return 1;
		return 0;
	};
	vector<int> dp(N + 1);
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i=0; i<N; i++){
		pq.emplace(dp[i], i);
		dp[i + 1] = 1e9;
		bool good = 0;
		for(auto &j : use[C[i]]){
			int kappa = (i - j + M - 1) % M;
			good |= insert(kappa, i);
		}
		if(good){
			while(sz(pq) && pq.top().second < i + 1 - M) pq.pop();
			dp[i + 1] = pq.top().first + 1;
		}
	}
	if(dp[N] > 1e8) return -1;
	return dp[N];
}
