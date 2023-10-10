#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, m;

int main(){
	cin >> n >> m;
	lint ans = 1;
	while(n--){
		int x;
		cin >> x;
		ans *= max(x, 1);
		ans %= m;
	}
	cout << ans % m;
}
