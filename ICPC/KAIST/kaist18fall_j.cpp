#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

int n;
pi a[MAXN];

lint ccw(pi a, pi b, pi c){
	lint dx1 = b.first - a.first;
	lint dy1 = b.second - a.second;
	lint dx2 = c.first - a.first;
	lint dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

int main(){
	cin >> n;
	n *= 2;
	for(int i=0; i<n; i++){
		cin >> a[i].first;
		if(i == 0) continue;
		if(i % 2 == 1) a[i].second = a[i-1].second + (a[i].first - a[i-1].first);
		else a[i].second = a[i-1].second - (a[i].first - a[i-1].first);
	}
	int q; cin >> q;
	if(q == a[0].first){
		puts("0");
		return 0;
	}
	int l = lower_bound(a, a + n, pi(q, -1)) - a - 1;
	pi crd(q, 0);
	if(a[l].second > a[l+1].second){
		crd.second = a[l].second - (q - a[l].first);
	}
	else{
		crd.second = a[l].second + (q - a[l].first);
	}
	int s = 0, e = 1e7;
	while(s != e){
		int m = (s+e)/2;
		bool bad = false;
		for(int j=0; j<=l; j++){
			if(ccw(crd, a[j], pi(0, m)) > 0) bad = true;
		}
		if(bad) s = m + 1;
		else e = m;
	}
	cout << s << endl;
}
