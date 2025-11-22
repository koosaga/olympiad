#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const lint M4 = 19;
const lint M28 = (1ll << 28) + (1ll << 3) + 1;

lint MUL(lint a, lint b, lint d, lint M) {
	if (a > b)
		swap(a, b);
	lint ans = 0;
	for (int i = 0; a; i++) {
		if (a & 1)
			ans ^= b;
		if ((b >> (d - 1)) & 1) {
			b <<= 1;
			b ^= M;
		} else
			b <<= 1;
		a >>= 1;
	}
	return ans;
}

struct GF4 {
	lint x;
	GF4() { x = 0; }
	GF4(lint a) { x = a; }
	GF4 operator+(const GF4 &t) { return GF4(x ^ t.x); }
	GF4 operator-(const GF4 &t) { return GF4(x ^ t.x); }
	GF4 operator*(const GF4 &t) { return GF4(MUL(x, t.x, 4, M4)); }
	GF4 eval(const vector<GF4> &p) {
		GF4 cur;
		for (int i = sz(p) - 1; i >= 0; i--) {
			cur = cur * x + p[i].x;
		}
		return cur;
	}
	GF4 inv() {
		GF4 ans = 1, a = *this;
		for (int p = (1 << 4) - 2; p; p /= 2, a = a * a)
			if (p & 1)
				ans = ans * a;
		return ans;
	}
};

struct GF28 {
	lint x;
	GF28() { x = 0; }
	GF28(lint a) { x = a; }
	GF28 operator+(const GF28 &t) { return GF28(x ^ t.x); }
	GF28 operator-(const GF28 &t) { return GF28(x ^ t.x); }
	GF28 operator*(const GF28 &t) { return GF28(MUL(x, t.x, 28, M28)); }
	GF28 eval(const vector<GF28> &p) {
		GF28 cur;
		for (int i = sz(p) - 1; i >= 0; i--) {
			cur = cur * x + p[i].x;
		}
		return cur;
	}
	GF28 inv() {
		GF28 ans = 1, a = *this;
		for (int p = (1 << 28) - 2; p; p /= 2, a = a * a)
			if (p & 1)
				ans = ans * a;
		return ans;
	}
};

template <typename T> vector<T> interp(vector<array<T, 2>> p) {
	vector<T> ans(7);
	for (int i = 0; i < 7; i++) {
		vector<T> g = {T(1)};
		T h = 1;
		for (int j = 0; j < 7; j++) {
			if (i != j) {
				h = h * (p[i][0] - p[j][0]);
				vector<T> ng = g;
				ng.insert(ng.begin(), T(0));
				for (int k = 0; k < sz(g); k++) {
					ng[k] = ng[k] - p[j][0] * g[k];
				}
				g = ng;
			}
		}
		h = h.inv();
		h = h * p[i][1];
		for (int i = 0; i < 7; i++) {
			ans[i] = ans[i] + h * g[i];
		}
	}
	return ans;
}

void Gi() {
	string s;
	cin >> s;
	vector<GF28> P;
	for (int i = 0; i < 7; i++) {
		lint ans = 0;
		for (int j = 28 * i; j < 28 * i + 28; j++) {
			if (s[j] == '1')
				ans |= (1ll << (j - 28 * i));
		}
		P.push_back(GF28(ans));
	}
	for (int i = 0; i < 13; i++) {
		lint ans = GF28(i).eval(P).x;
		vector<GF4> Q;
		for (int j = 0; j < 7; j++) {
			Q.push_back(GF4((ans >> (4 * j)) & 15));
		}
		for (int j = 0; j < 13; j++) {
			cout << GF4(j).eval(Q).x << " ";
		}
		cout << "\n";
	}
}

void Bum() {
	vector<int> R(7), C(7);
	for (int i = 0; i < 7; i++)
		cin >> R[i], R[i]--;
	for (int i = 0; i < 7; i++)
		cin >> C[i], C[i]--;
	vector<array<GF28, 2>> p;
	for (int i = 0; i < 7; i++) {
		vector<array<GF4, 2>> pcol;
		for (int j = 0; j < 7; j++) {
			int q;
			cin >> q;
			pcol.push_back({GF4(C[j]), GF4(q)});
		}
		auto q = interp(pcol);
		lint ans = 0;
		for (int j = 0; j < 7; j++) {
			ans |= (q[j].x << (4 * j));
		}
		p.push_back({GF28(R[i]), GF28(ans)});
	}
	auto ans = interp(p);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 28; j++) {
			cout << (ans[i].x >> j) % 2;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	if (t == 0)
		Gi();
	else
		Bum();
}