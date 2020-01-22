#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;
const int MAXT = 270000;

bool has(int x, int a, int d, int m){
	return x >= a && x % d == a % d && (x - a) / d < m;
}

int nxt(int ord, int a, int d, int m){
	int curmod = ord % d;
	int nxtmod = a % d;
	ord += (nxtmod - curmod + d) % d;
	if((ord - a) / d >= m) return (1<<31) - 1;
	return ord;
}

pi dp[15][1<<15][2];
int tot = 0;

pi f(int i, int ord, int modv, int a, int d, int m){
	if(i < 0) return pi(0, 0);
	if(ord + (1<<(i+1))-2 < a) return pi(0, 0);
	if(ord > a + (m-1)*d) return pi(0, 0);
	int nv = nxt(ord, a, d, m) - ord;
	if(nv > (1<<(i+1)) - 2) return pi(0, 0);
	bool memable = (i < 15 && a <= ord && ord + (1<<(i+1))-2 <= a + (m-1)*d);
	if(memable && ~dp[i][nv][modv].first){
		return dp[i][nv][modv];
	}
	auto f1 = f(i - 1, ord, 0, a, d, m);
	auto f2 = f(i - 1, ord + (1<<i) - 1, 1, a, d, m);
	auto ans = pi(f1.first * 2 + f2.first * 2, f1.second + f2.second + f2.first);
	if(has(ord + (1<<(i+1))-2, a, d, m)){
		ans.first += 1;
		ans.second += -modv;
	}
	if(memable) dp[i][nv][modv] = ans;
	return ans;
}

int main(){
	int k, q; cin >> k >> q;
	while(q--){
		int a, d, m;
		cin >> a >> d >> m;
		a--;
		lint cur = 0;
		lint ans = 0;
		for(int i=0; i<15; i++){
			for(int j=0; j<(2<<i); j++){
				dp[i][j][0] = dp[i][j][1] = pi(-1, -1);
			}
		}
		for(int i=k-1; i>=1; i--){
			lint sbsz = (1 << i) - 1;
			lint pos = (1<<(k-i)) - 1;
			auto fn = f(i - 1, cur, 0, a, d, m);
			ans += ((pos * 2) * fn.first + fn.second) / 2;
			cur += sbsz;
			if(has(cur, a, d, m)) ans += 2 * pos + 1;
			cur++;
		}
		cout << ans << endl;
	}
}
