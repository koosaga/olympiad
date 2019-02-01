#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

int query(int u, int d, int n){
	int s = 0, e = n;
	while(s != e){
		int m = (s+e)/2;
		if(u * m - d * (n - m) > 0){
			e = m;
		}
		else s = m+1;
	}
	return u * s - d * (n - s);
}

int main(){
	int ret = 2e9;
	int n, m; cin >> n >> m;
	while(m--){
		int u, d; cin >> u >> d;
		ret = min(ret, query(u, d, n));
	}
	cout << ret << endl;
}
