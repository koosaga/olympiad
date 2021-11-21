#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 1000005;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k; cin >> n >> k;
	vector<int> a(n), cnt(k);
	for(int i = 0; i < n; i++){
		cin >> a[i]; a[i]--; cnt[a[i]]++;
	}
	int ans = 1e9;
	for(int i = 0; i < n; i++){
		vector<int> tcnt(k);
		int zeroes = k;
		for(int j = i; j < n; j++){
			if(tcnt[a[j]] == 0) zeroes--;
			tcnt[a[j]]++;
			if(tcnt[a[j]] == cnt[a[j]]) break;
			if(zeroes == 0) ans = min(ans, j - i + 1);
		}
	}
	if(ans > 1e8) ans = 0;
	cout << ans << endl;
}

