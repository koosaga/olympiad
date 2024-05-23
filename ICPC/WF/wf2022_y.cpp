#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	s.resize(unique(all(s)) - s.begin());
	if (sz(s) >= 4)
		s.resize(2 + sz(s) % 2);
	cout << s << "\n";
}