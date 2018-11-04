#include <bits/stdc++.h>
using namespace std;

int cnt[1005];

int main(){
	int n, m;
	cin >> n >> m;
	while(m--){
		int l, r; cin >> l >> r;
		fill(cnt + l, cnt + r, 1);
	}
	cout << n + 1 + 2 * count(cnt, cnt + 1005, 1) << endl;
}
