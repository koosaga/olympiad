#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXQ = 200'005;

int O[20], G[20], R[20];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string o, g, r;
	cin >> o >> g >> r;
	vector<pii> ans;
	int i;
	o.insert(o.begin(), '0');
	g.insert(g.begin(), '0');
	r.insert(r.begin(), '0');
	auto get = [&](int f, int t) {
		t--;
		f--;
		if (f <= t)
			return t - f;
		else
			return t + 10 - f;
	};
	auto f = [&](int a, int b){
		string ns = "0";
		if(!b) return;
		ans.emplace_back(a, b);
		int i;
		if(a == 0) {
			for(i=11-b;i<=10;i++) ns.push_back(o[i]);
			for(i=1;i<=10-b;i++) ns.push_back(o[i]);
			o = ns;
		}
		if(a == 1) {
			for(i=11-b;i<=10;i++) ns.push_back(g[i]);
			for(i=1;i<=10-b;i++) ns.push_back(g[i]);
			g = ns;
		}
		if(a == 2) {
			for(i=11-b;i<=10;i++) ns.push_back(r[i]);
			for(i=1;i<=10-b;i++) ns.push_back(r[i]);
			r = ns;
		}
		if(a == 3) {
			for(int k = 1;k<=b;k++) {
				for(i=1;i<=3;i++) {
					auto t = r[i];
					r[i] = o[i];
					o[i] = g[i];
					g[i] = t;
				}
			}
		}
	};
	while (1) {
		int a, b, c;
		a = b = c = 0;
		for (i = 1; i <= 10; i++) {
			if (o[i] != 'o') {
				a = i;
				break;
			}
		}
		//cout<<'a'<<a<<'\n';
		if (a) {
			f(0, get(a, 3));
			for (i = 1; i <= 10; i++) {
				if (g[i] == 'o') {
					b = i;
					break;
				}
			}
			if (b) {
				f(1, get(b, 10));
				f(3, 2);
				f(1, 1);
				f(3, 1);
			} else {
				for (i = 1; i <= 10; i++) {
					if (r[i] == 'o') {
						b = i;
						break;
					}
				}
				f(2, get(b, 10));
				f(3, 1);
				f(2, 1);
				f(3, 2);
			}
		} else {
			for (i = 1; i <= 10; i++) {
				if (g[i] == 'r') {
					a = i;
					break;
				}
			}
			for (i = 1; i <= 10; i++) {
				if (r[i] == 'g') {
					b = i;
					break;
				}
			}
			if (!a)
				break;
			
			f(1, get(a, 3));
			f(2, get(b, 10));
			f(3, 2);
			f(2, 1);
			f(3, 1);
		}
	}
	int cnt = 0;
	for (auto &[a, b] : ans) {
		if (b)
			cnt++;
	}
	cout << cnt << '\n';
	string ss = "ogrc";
	for (auto &[a, b]:ans) {
		if (b) {
			cout << ss[a] << b << '\n';
		}
	}
	return 0;
}