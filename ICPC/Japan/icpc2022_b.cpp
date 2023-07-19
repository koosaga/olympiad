#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const lint mod = 998244353;

int main() {
	auto query = [&](lint x) {
		cout << "query " << x << endl;
		lint z;
		cin >> z;
		return z;
	};
	lint sum = query(0);
	lint noround = 0;
	lint pwr = 1;
	for (int i = 0; i < 18; i++) {
		lint s = 0, e = 9;
		while (s != e) {
			lint m = (s + e + 1) / 2;
			if (query(noround + pwr * m) >= sum + m)
				s = m;
			else
				e = m - 1;
		}
		noround += pwr * s;
		sum += s;
		pwr *= 10;
	}
	cout << "answer " << pwr - noround - 1 << endl;
}