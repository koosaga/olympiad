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
	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		int good = 0, flip = 0;
		for (int i = 0; i < n; i++) {
			string s;
			cin >> s;
			if (i == 0)
				continue;
			if (s == "010" || s == "101")
				continue;
			if (s == "111")
				good++, flip++;
			else
				flip++;
		}
		if (good % 2 || flip % 2)
			cout << "Yesyes\n";

		else
			cout << "Nono\n";
	}
}