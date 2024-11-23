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
	int n, hmax;
	string s;
	cin >> n >> hmax >> s;
	int ans = 0, h = 0;
	for (int i = 0; i < n;) {
		int j = i;
		while (j < n && s[j] == s[i])
			j++;
		if (s[i] == '(') {
			h += (j - i);
			while (h > hmax) {
				h -= 2;
				ans += 1;
			}
		} else {
			h -= (j - i);
			while (h < 0) {
				h += 2;
				ans += 1;
			}
		}
		i = j;
	}
	ans += h / 2;
	cout << ans << "\n";
}