#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 1005;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q; cin >> q;
	lint sum = 0;
	while(q--){
		string f; cin >> f; cin >> f;
		int x; cin >> x;
		if(f == "R") sum += x;
		else sum -= x;
	}
	int y; cin >> y; sum += y;
	cout << sum << "\n";
}
