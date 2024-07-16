#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int is_inv(int u, int v) {
	assert(u < v);
	if (u + 1 == v) {
		cout << "? " << u << " " << v << endl;
		int g;
		cin >> g;
		return g;
	}

	cout << "? " << u << " " << v << endl;
	int g1;
	cin >> g1;
	cout << "? " << u + 1 << " " << v << endl;
	int g2;
	cin >> g2;
	cout << "? " << u << " " << v - 1 << endl;
	int g3;
	cin >> g3;
	cout << "? " << u + 1 << " " << v - 1 << endl;
	int g4;
	cin >> g4;
	return g1 ^ g2 ^ g3 ^ g4;
}

int main() {
	vector<int> plist;
	for (int i = 1; i <= 1000; i++) {
		int s = 0, e = sz(plist);
		while (s != e) {
			int m = (s + e) / 2;
			if (is_inv(plist[m], i))
				e = m;
			else
				s = m + 1;
		}
		plist.insert(plist.begin() + s, i);
	}
	vector<int> ans(1000);
	for (int i = 0; i < sz(plist); i++)
		ans[plist[i] - 1] = i + 1;
	cout << "!" << endl;
	for (auto &x : ans)
		cout << x << " ";
	cout << endl;
}