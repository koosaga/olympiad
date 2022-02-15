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
	int n, m;
	cin >> n;
	vector<pi> a;
	for(int i = 1; i <= n; i++){
		lint x; cin >> x;
		lint c = 1;
		while(x % 2 == 0){
			x /= 2;
			c *= 2;
		}
		a.emplace_back(c, x);
	}
	int p = 0;
	lint sum = 0;
	cin >> m;
	while(m--){
		lint k; cin >> k;
		while(p < n && sum + a[p].first < k){
			sum += a[p++].first;
		}
		cout << a[p].second << "\n";
	}
}
