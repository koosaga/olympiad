#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000005;
const int inf = 1e9;

pi merge(pi a, pi b){
	return pi(min(inf, a.first + b.first), max(-inf, min(a.second, a.first + b.second)));
}

pi nxt[41][MAXN];
int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	int m; cin >> m;
	string s; cin >> s;
	for(int i = 0; i < m; i++){
		if(s[i] == 'W') nxt[0][i] = pi(1, 0);
		else nxt[0][i] = pi(-1, -1);
	}
	for(int i = 1; i < 41; i++){
		for(int j = 0; j < m; j++){
			int k = (j + n * (1ll << (i - 1))) % m;
			nxt[i][j] = merge(nxt[i - 1][j], nxt[i - 1][k]);
		}
	}
	lint ret = 2e18;
	for(int i = 0; i < n; i++){
		pi cur(a[i], a[i]);
		lint ans = i;
		int pos = i % m;
		bool good = 0;
		for(int j = 40; j >= 0; j--){
			if(merge(cur, nxt[j][pos]).second > 0){
				cur = merge(cur, nxt[j][pos]);
				ans += n * (1ll << j);
				pos += n * (1ll << j) % m;
				pos %= m;
			}
			else good = 1;
		}
		if(good) ret = min(ret, ans);
	}
	if(ret > 1.8e18) ret = -1;
	else ret++;
	cout << ret << "\n";
}
