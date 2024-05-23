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
	int a[5];
	cout << "1 0 0" << endl;
	cin >> a[0];
	cout << "0 1 0" << endl;
	cin >> a[1];
	cout << "0 0 1" << endl;
	cin >> a[2];
	cout << "1 1 1" << endl;
	cin >> a[3];
	cout << "1 2 3" << endl;
	cin >> a[4];
	if (a[0] + a[1] + a[2] == a[3]) {
		cout << a[0] << " " << a[1] << " " << a[2] << endl;
		return 0;
	}
	if (a[0] + 2 * a[1] + 3 * a[2] == a[4]) {
		cout << a[0] << " " << a[1] << " " << a[2] << endl;
		return 0;
	}
	for (int i = 0; i < 3; i++) {
		int za = a[i];
		a[i] = a[3] - a[(i + 1) % 3] - a[(i + 2) % 3];
		if (a[0] + 2 * a[1] + 3 * a[2] == a[4]) {
			cout << a[0] << " " << a[1] << " " << a[2] << endl;
			return 0;
		}
		a[i] = za;
	}
}