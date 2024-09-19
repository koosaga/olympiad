#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

pi parse(string s) {
	int y = 0, m = 0, d = 0;
	for (int i = 0; i < 4; i++) {
		y = y * 10 + s[i] - '0';
	}
	for (int i = 5; i < 7; i++) {
		m = m * 10 + s[i] - '0';
	}
	for (int i = 8; i < 10; i++) {
		d = d * 10 + s[i] - '0';
	}
	for (int i = 0; i < m - 1; i++)
		d += days[i];
	return pi{y, d};
}

void outp(int d) {
	for (int i = 0; i < 12; i++) {
		if (d <= days[i]) {
			cout << (i + 1) / 10;
			cout << (i + 1) % 10;
			cout << "-";
			cout << d / 10;
			cout << d % 10;
			cout << "\n";
			return;
		}
		d -= days[i];
	}
}

int cnt[3000000];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, y, d;
	cin >> n >> y >> d;
	int sdays = 0;
	cnt[0]++;
	cnt[2999999]--;
	for (int i = 0; i < n; i++) {
		{
			string s;
			cin >> s;
			auto [x, y] = parse(s);
			x += 1005;
			cnt[x * 365 + y] -= 1;
		}
		{
			string s;
			cin >> s;
			auto [x, y] = parse(s);
			x += 1005;
			cnt[x * 365 + y + 1] += 1;
			sdays = max(sdays, x * 365 + y + 1);
		}
	}
	for (int i = 1; i < 3000000; i++)
		cnt[i] += cnt[i - 1];
	for (int i = 1; i < 3000000; i++)
		cnt[i] += cnt[i - 1];
	pi ans{int(1e9), int(1e9)};
	for (int i = 1; i <= 365; i++) {
		int consex = 0;
		for (int yr = 0; yr <= 7010; yr++) {
			int l = (yr - 1) * 365 + i;
			int r = yr * 365 + i - 1;
			l = max(l, 1);
			if (cnt[r] - cnt[l - 1] >= d)
				consex++;
			else
				consex = 0;
			if (yr * 365 + i >= sdays && consex >= y) {
				ans = min(ans, pi{yr - 1005, i});
			}
		}
	}
	cout << ans[0] / 1000;
	cout << (ans[0] % 1000) / 100;
	cout << (ans[0] % 100) / 10;
	cout << (ans[0] % 10) / 1;
	cout << "-";
	outp(ans[1]);
}
