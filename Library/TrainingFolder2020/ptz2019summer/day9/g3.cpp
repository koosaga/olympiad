#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50050;
using lint = long long;
using pi = pair<lint, int>;
#define sz(v) ((int)(v).size())

int n, k;
lint a[MAXN];
pi dp[MAXN];

lint cost(int x, int y){
	return 2 * (y - x) * (a[y] - a[x]);
}

pi trial(lint x){
	deque<int> dq;
	for(int i=1; i<=n; i++){
		auto cross = [&](int p, int q){
			int st = max(p, q) + 1, ed = n + 1;
			while(st != ed){
				int m = (st+ed)/2;
				if(dp[p].first + cost(p, m) < dp[q].first + cost(q, m)) st = m + 1;
				else ed = m;
			}
			return st;
		};
		auto eval = [&](int v){
			return dp[v].first + cost(v, i) + x;
		};
		while(sz(dq) >= 2 && cross(dq[sz(dq) - 2], dq.back()) >= cross(dq.back(), i-1)) dq.pop_back();
		dq.push_back(i-1);
		while(sz(dq) >= 2 && eval(dq[0]) >= eval(dq[1])) dq.pop_front();
		dp[i].first = eval(dq[0]);
		dp[i].second = dp[dq[0]].second + 1;
	}
	return dp[n];
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%lld",&a[i]);
		a[i] += a[i-1];
	}
	lint s = 0, e = 1e15;
	while(s != e){
		lint m = (s+e)/2;
		if(trial(2 * m + 1).second > k) s = m + 1;
		else e = m;
	}
	cout << (trial(2 * s).first - k * (2 * s)) / 2 << endl;
}
