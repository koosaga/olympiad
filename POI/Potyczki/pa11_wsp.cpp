#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		int x, y; cin >> x >> y;
		a[i] = x + y;
	}
	int ans = 0;
	for(int i = 0; i < n; ){
		int j = i;
		lint l = 0, r = 1e18;
		lint foo = 0;
		while(j < n){
			foo = a[j] - foo;
			if(i % 2 == j % 2) r = min(r, foo);
			else l = max(l, -foo);
			if(l > r) break;
			j++;
		}
		ans++;
		i = j;
	}
	cout << n - ans << "\n";
}
