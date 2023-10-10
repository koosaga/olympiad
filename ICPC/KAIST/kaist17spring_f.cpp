#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 9;

int main(){
	int n;
	cin >> n;
	lint ans = 1;
	for(int i=1; i<=n; i++){
		ans *= 2 * i - 1;
		ans %= mod;
	}
	cout << ans;
}
