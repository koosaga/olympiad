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
	vector<lint> a(n);
	auto trial = [&](lint C){
		lint p = 0;
		for(auto &i : a){
			lint cashUse = min(C, i);
			lint pointUse = (i - cashUse) * 10;
			if(p < pointUse) return false;
			p -= pointUse;
			C -= cashUse;
			p += cashUse;
		}
		return true;
	};
	for(auto &i : a) cin >> i;
	lint s = 0, e = 1e15;
	while(s != e){
		lint m = (s + e) / 2;
		if(trial(m)) e = m;
		else s = m + 1;
	}
	cout << s << "\n";
}
