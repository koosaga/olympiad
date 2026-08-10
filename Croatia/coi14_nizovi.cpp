#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
void reverse(int s, int e) { cout << "reverse " << s << " " << e << endl; }
void norm(int s, int m, int e) {
	if (s == m || m == e)
		return;
	reverse(s, e - 1);
	reverse(s, s + (e - m) - 1);
	reverse(s + (e - m), e - 1);
}

int cmp(int a, int b) {
	cout << "cmp " << a << " " << b << endl;
	int z;
	cin >> z;
	return z;
}

int main() {
	int A, B;
	cin >> A >> B;
	int pnt = A + 1;
	for (int i = 1; i <= A; i++) {
		int s = pnt - 1, e = A + B;
		while (s != e) {
			int m = (s + e + 1) / 2;
			if (cmp(pnt - (A - i + 1), m) == 1)
				s = m;
			else
				e = m - 1;
		}
		s++;
		norm(pnt - (A - i + 1), pnt, s);
		pnt = s;
	}
	cout << "end" << endl;
}