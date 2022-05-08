#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int k, n, m; cin >> k >> n >> m;
	vector<lint> a(k), s;
	for(auto &i : a) cin >> i;
	s = a; sort(all(s));
	auto count = [&](lint x, lint y){
		return upper_bound(all(s), y) - lower_bound(all(s), x);
	};
	int G = (k + 11) / 12; // if strictly large is >= G, fail
	lint U = 100 * (n - m);
	if(U == 0){
		for(int i = 0; i < k; i++){
			if(count(a[i] + 1, 1e18) < G){
				cout << i+1 << "\n";
			}
		}
		cout << "--------\n";
		for(int i = 0; i < k; i++){
			if(count(a[i] + 1, 1e18) < G){
				cout << i+1 << "\n";
			}
		}
		return 0;
	}
	for(int i = 0; i < k; i++){
		if(count(a[i] - U + 1, 1e18) - 1 < G){
			cout << i+1 << "\n";
		}
	}
	cout << "--------\n";
	for(int i = 0; i < k; i++){
		if(count(a[i] + U + 1, 1e18) < G){
			cout << i+1 << "\n";
		}
	}
}
