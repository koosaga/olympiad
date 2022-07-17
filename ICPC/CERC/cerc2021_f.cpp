#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;
const int mod = 998244353; //1e9 + 7;//998244353;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n, m, q; cin >> n >> m >> q;
	string Q; if(q) cin >> Q;
	vector<string> s(n);
	for(int i = 0; i < n; i++) cin >> s[i];
	auto rot = [&](){
		int n = sz(s), m = sz(s[0]);
		vector<string> t(m, string(n, '.'));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				t[m-1-j][i]= s[i][j];
			}
		}
		s = t;
	};

	for(auto &x : Q){
		if(x == 'D') rot(), rot(), rot();
		if(x == 'R') rot(), rot();
		if(x == 'U') rot();
		for(int i = 0; i < sz(s); i++){
			string t;
			for(int j = 0; j < sz(s[i]); j++){
				if(s[i][j] != '.') t.push_back(s[i][j]);
			}
			while(sz(t) < sz(s[i])) t.push_back('.');
			s[i] = t;
		}
		if(x == 'U') rot(), rot(), rot();
		if(x == 'R') rot(), rot();
		if(x == 'D') rot();
	}
	for(auto &x : s) cout << x << "\n";
}
