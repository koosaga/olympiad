#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 20005;

lint m;
int t, n, a[MAXN];

lint sum(lint x, lint c){
	return 2 * x * c * (c + 1) + 4 * t * ((c + 1) * c * (c - 1) / 3);
}

pi trial(lint v){
	pi ret(0, 0);
	for(int i=0; i<n; i++){
		if(v < a[i]) break;
		lint cnt = (v - a[i]) / t + 1;
		if(cnt > 1e6){
			ret.first = m + 10ll;
			return ret;
		}
		ret.first += cnt * (cnt + 1) * 2;
		ret.second += sum(a[i], cnt);
	}
	return ret;
}

int main(){
	cin >> m >> t >> n;
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	lint s = 0, e = 1e14;
	while(s != e){
		lint mi = (s+e+1)/2;
		if(trial(mi).first <= m) s = mi;
		else e = mi-1;
	}
	auto x = trial(s);
	cout << x.second + (m - x.first) * (s + 1) << endl;
}
