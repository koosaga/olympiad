
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<lint, lint>;

int rh, rv, sh, sv;

int solve(int x1, int y1, int x2, int y2){
	return max((x2 + x1 - 1) / x1, (y2 + y1 - 1) / y1);
}

int main(){
	freopen("giant.in", "r", stdin);
	freopen("giant.out", "w", stdout);
	cin >> rh >> rv >> sh >> sv;
	int q; cin >> q;
	lint ret = 1e18;
	while(q--){
		int irh, irv, ish, isv, p;
		cin >> irh >> irv >> ish >> isv >> p;
		lint vert = solve(irh, ish, rh, sh) * solve(irv, isv, rv, sv);
		swap(irh, irv);
		swap(ish, isv);
		lint vert2 = solve(irh, ish, rh, sh) * solve(irv, isv, rv, sv);
		ret = min(ret, vert * p);
		ret = min(ret, vert2 * p);
	}
	cout << ret << endl;
}

