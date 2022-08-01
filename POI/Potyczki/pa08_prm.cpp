#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 200005;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q; cin >> n >> q;
	int d = n / 2;
	int only = -1;
	while(q--){
		int x, v;
		cin >> x >> v;
		if(x == v){
			if(x <= n) d = min(d, n - x);
			else d = min(d, x - (n + 1));
		}
		else if(x < v){
			if(only != -1 && only != v - x){
				cout << "0\n";
				return 0;
			}
			if(!(x <= n && v > n)){
				cout << "0\n";
				return 0;
			}
			only = v - x;
		}
		else if(x > v){
			if(only != -1 && only != x - v){
				cout << "0\n";
				return 0;
			}
			if(!(v <= n && x > n)){
				cout << "0\n";
				return 0;
			}
			only = x - v;
		}
	}
	if(only != -1){
		if(only <= d) cout << "1\n";
		else cout << "0\n";
	}
	else cout << d + 1 << "\n";
}
