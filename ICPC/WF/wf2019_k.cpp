#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int T = 2520;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<int> promote(101);
	promote[1] = 11;
	for(int i = 2; i <= 100; i++){
		bool isprime = 1;
		for(int j = 2; j * j <= i; j++){
			if(i % j == 0) isprime = 0;
		}
		if(isprime){
			int goal = i;
			while(goal * i <= 100) goal *= i;
			for(int k = i; k <= 100; k *= i) promote[k] = goal;
		}
	}
	vector<int> x(n), r(n), t(n);
	for(int i = 0; i < n; i++){
		cin >> x[i] >> r[i] >> t[i];
		t[i] += r[i];
	}
	vector<double> ans(n + 1);
	for(int i = 0; i < T; i++){
		double p = 1;
		int chk[105][105] = {}, cnt[105] = {};
		for(int j = 2; j <= 100; j++){
			if(promote[j] == j){
				for(int k = 0; k < j; k++) chk[j][k] = 1, cnt[j]++;
			}
		}
		for(int j = 0; j < n; j++){
			int period = t[j] / gcd(t[j], T);
			period = promote[period];
			assert(period);
			int curcnt = cnt[period];
			for(int k = 0; k < period; k++){
				int cur = x[j] + T * k + i;
				if(cur % t[j] < r[j]){
					if(chk[period][k]) cnt[period]--;
					chk[period][k] = 0;
				}
			}
			if(curcnt != cnt[period]){
				ans[j] += p * (curcnt - cnt[period]) / (curcnt * T);
				p /= curcnt;
				p *= cnt[period];
			}
		}
		ans[n] += p / T;
	}
	for(int i = 0; i <= n; i++) cout << setprecision(69) << ans[i] << "\n";
}
