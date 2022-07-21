#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2005;
const int mod = 998244353;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n, q; cin >> n >> q;
	vector<pi> dx(n + 2);
	auto add = [&](int s, int e, int p, int q){
		dx[s].first += p;
		dx[s].second += q;
		dx[e + 1].first -= p;
		dx[e + 1].second -= q;
	};
	while(q--){
		string s; cin >> s;
		int l, r; cin >> l >> r;
		if(s == "R") add(l, r, 0, 1);
		else if(s == "D") add(l, r, 0, -1);
		else if(s == "H"){
			int m = (l + r) / 2;
			add(l, m, 1, -(l - 1));
			add(m+1, r, -1, r + 1);
		}
		else{
			int m = (l + r) / 2;
			add(l, m, -1, (l - 1));
			add(m+1, r, 1, -(r + 1));
		}
	}
	for(int i = 1; i <= n; i++){
		dx[i].first += dx[i - 1].first;
		dx[i].second += dx[i - 1].second;
		cout << dx[i].first * i + dx[i].second << "\n";
	}
}
