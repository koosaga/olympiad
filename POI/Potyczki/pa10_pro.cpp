#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

lint bin(int x, int y){
	return 1ll * x * (x + 1) / 2;
}

int main(){
	int n, m, p;
	cin >> n >> m >> p;
	lint ret = 0;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(2 * i + 2 * j < p) continue;
			ret += 1ll * (n + 1 - i) * (m + 1 - j);
		}
	}
	cout << ret << endl;
}
