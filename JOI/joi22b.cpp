#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 500005;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, m;
	cin >> n >> m;
	vector<lint> a(n), b(n);
	for(auto &i : a) cin >> i;
	for(auto &i : b) cin >> i;
	auto trial = [&](lint X){
		lint ret = 0;
		for(int i = 0; i < n; i++){
			if(a[i] <= b[i]){
				ret += (X + b[i] - 1) / b[i];
			}
			else{
				lint kappa = (X + a[i] - 1) / a[i];
				kappa = min(kappa, m);
				lint upd = 1e18;
				for(lint j = max(kappa - 2, 0ll); j <= kappa; j++){
					lint rem = max(0ll, X - a[i] * j);
					upd = min(upd,j + (rem + b[i] - 1) / b[i]);
				}
				ret += upd;
			}
			if(ret > n * m) return 0;
		}
		return 1;
	};
	lint s = 0, e = 1e18;
	while(s != e){
		lint m = (1 + s + e) / 2;
		if(trial(m)) s = m;
		else e = m - 1;
	}
	cout << s << "\n";
}
