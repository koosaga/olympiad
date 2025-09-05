#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int mod = 1e9 + 7;

int go() {
	int x;
	cin >> x;
	if (x == 1)
		exit(0);
	return x;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		vector<int> offsets(n);
		for (int j = 0; j < n; j++) {
			offsets[j] = go();
			cout << i + 1 << " " << 1 << endl;
		}
		go();
		int pos = max_element(all(offsets)) - offsets.begin();
		cout << i + 1 << " " << pos << endl;
	}
	// n(n+1) + 1 + (n-1)n3 + (n-1)
	assert(go() == n);
	vector<int> offs(n);
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "1 -1" << endl;
			go();
			cout << i + 1 << " " << (j + 1) << endl;
			int q = go();
			cout << i + 1 << " " << -(j + 1) << endl;
			go();
			if (j < n - 1 && q == n)
				offs[i] = j + 1;
		}
	}
	for (int i = 1; i < n; i++) {
		cout << i + 1 << " " << offs[i] << endl;
		go();
	}
	assert(0);
}