#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 1000005;

bool query(lint x){
	cout << "? " << x << endl;
	int q; cin >> q; return q;
}

void solve(lint n){
	// get witness
	lint l = 0, r = 0, pos = 0;
	lint s = 1, e = n;
	bool flag = 0;
	while(s != e){
		lint m = (s + e - 1) / 2;
		if(flag) pos += m;
		else pos -= m;
		s = m + 1;
		l = min(l, pos);
		r = max(r, pos);
		flag ^= 1;
	}
	pos = (1 - l);
	
	s = 1, e = n;
	flag = 0;
	query(pos);
	while(s != e){
		lint m = (s+e-1)/2;
		if(flag) pos += m;
		else pos -= m;
		if(query(pos)) e = m;
		else s = m + 1;
		flag ^= 1;
	}
	cout << "= " << s << endl;
}

int main(){
	int t; cin >> t;
	while(t--){
		lint n; cin >> n;
		solve(n);
	}
}
