#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 530000;
const int mod = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<int> cnt(n);
	for(int i = 0; i < n; i++){
		int x; cin >> x; cnt[x-1]++;
	}
	int rem = 0;
	lint ans = 1;
	for(int i = 0; i < n; i++){
		if(!cnt[i]) continue;
		rem += cnt[i] - 1;
		ans *= cnt[i];
		ans %= mod;
	}
	for(int i = 1; i <= rem; i++) ans = (ans * i) % mod;
	cout << ans << "\n";
}
