#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

int cnt[MAXN];

int main(){
	int n, h, w;
	cin >> n >> h >> w;
	for(int i=0; i<n; i++){
		int s = w * i, e = w * i + w;
		int x; cin >> x;
		if(i % 2 == 0) s += x, e += x;
		else s -= x, e -= x;
		fill(cnt + s, cnt + e, 1);
	}
	cout << count(cnt, cnt + n * w, 0) * h << endl;
}
