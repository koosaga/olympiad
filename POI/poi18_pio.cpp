#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int n;
pi a[600005];

lint hyp(lint a, lint b) { return a * a + b * b; }
lint ccw(pi a, pi b) { return a.first * b.second - b.first * a.second; }
lint dot(pi a, pi b) { return a.first * b.first + a.second * b.second; }
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i].first >> a[i].second;
		if (a[i] == pi(0, 0)) {
			i--;
			n--;
		}
	}
	if (n == 0) {
		cout << "0\n";
		return 0;
	}
	sort(a, a + n, [&](const pi &a, const pi &b) {
		if ((a < pi(0, 0)) != (b < pi(0, 0))) {
			return (a < pi(0, 0)) < (b < pi(0, 0));
		} else
			return ccw(a, b) > 0;
	});
	{
		vector<pi> b;
		for (int i = 0; i < n;) {
			int j = i;
			while (j < n && ccw(a[i], a[j]) == 0 && dot(a[i], a[j]) > 0)
				j++;
			int sx = 0, sy = 0;
			for (int k = i; k < j; k++) {
				sx += a[k].first;
				sy += a[k].second;
			}
			b.push_back({sx, sy});
			i = j;
		}
		n = b.size();
		for (int i = 0; i < n; i++)
			a[i] = a[i + n] = b[i];
	}
	lint ret = 0;
	int e = 0, px = 0, py = 0;
	for (int i = 0; i < n; i++) {
		while (e < i + n && ccw(a[i], a[e]) >= 0) {
			px += a[e].first;
			py += a[e].second;
			ret = max(ret, hyp(px, py));
			e++;
		}
		ret = max(ret, hyp(px, py));
		px -= a[i].first;
		py -= a[i].second;
		ret = max(ret, hyp(px, py));
	}
	cout << ret;
}
