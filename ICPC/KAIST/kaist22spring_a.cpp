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
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		a[i] ^= a[i-1];
	}
	for(int i = 1; i <= n; i++){
		cin >> b[i];
		b[i] ^= b[i-1];
	}
	if(a[n] != b[n]) cout << "-1\n";
	else{
		int ans = 0;
		for(int i = 1; i < n; i++){
			if(a[i] != b[i]) ans++;
		}
		cout << ans << "\n";
	}
}
