#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

const ll MX = 1'000'000'000'000LL;

const bool debug = 0;

struct SEG {
	struct NOD {
		NOD() : c(0), s(0), l(0), r(0) {}

		int c;
		ll s;
		NOD *l, *r;

		void update(ll s, ll e) {
			if (0 < c) {
				this->s = e - s + 1;
			} else {
				this->s = 0;
				if (this->l) {
					this->s += this->l->s;
				}
				if (this->r) {
					this->s += this->r->s;
				}
			}
		}

		void upd(ll s, ll e, ll p, ll q, int w) {
			if (q < p || e < p || q < s || !w) {
				return;
			}

			if (p <= s && e <= q) {
				this->c += w;
				update(s, e);
				return;
			}

			ll m = (s + e) / 2;

			if (!this->l) {
				this->l = new NOD();
			}
			this->l->upd(s, m, p, q, w);

			if (!this->r) {
				this->r = new NOD();
			}
			this->r->upd(m + 1, e, p, q, w);

			update(s, e);
		}
	};

	NOD *rt;

	SEG() { rt = new NOD(); }

	void upd(ll s, ll e, ll p, ll q, ll r) {
		s += MX;
		e += MX;
		p += MX;
		q += MX;
		if (debug) {
			cout << p << ' ' << q << ' ' << r << endl;
		}
		rt->upd(s, e, p, q, r);
		if (debug) {
			cout << "rt = " << rt->s << endl;
		}
	}

	ll get() { return rt->s; }
} seg;

multiset<ll> LV, RV;

ll W;

void printAns() {
	ll x = seg.get();
	if (debug) {
		cout << "x = " << x << endl;
	}

	if (!LV.empty()) {
		ll t = *prev(LV.end());
		if (debug) {
			cout << "lv = " << t << endl;
		}
		x -= t;
	}

	if (!RV.empty()) {
		ll t = *prev(RV.end());
		if (debug) {
			cout << "rv = " << t << endl;
		}
		x -= t;
	}

	printf("%.30Lf\n", (long double)(sqrt(2)) * x);
}

void updWithPoints(pll o, pll s, pll e, int c) {
	if (0 == s.fi) {
		if (c < 0) {
			LV.erase(LV.find(s.se));
		}
		if (0 < c) {
			LV.emplace(s.se);
		}
	}

	if (e.fi == W) {
		if (c < 0) {
			RV.erase(RV.find(e.se));
		}
		if (0 < c) {
			RV.emplace(e.se);
		}
	}

	seg.upd(-MX, MX, o.fi - o.se, o.fi + o.se - 1, c);

	// segA.upd(-MX, MX, s.fi - s.se, e.fi - e.se - 1, c);
	// segB.upd(-MX, MX, s.fi + s.se, e.fi + e.se - 1, c);
}

void upd(ll x, ll y, int c) {
	pll s, e;

	if (0 <= x - y) {
		s = pll(x - y, 0);
	} else {
		s = pll(0, y - x);
	}

	if (x + y <= W) {
		e = pll(x + y, 0);
	} else {
		e = pll(W, x + y - W);
	}

	if (debug) {
		cout << "s = " << s.fi << ", " << s.se << endl;
		cout << "e = " << e.fi << ", " << e.se << endl;
	}

	updWithPoints(pll(x, y), s, e, c);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int Q;
	cin >> Q >> W;

	set<pll> PV;

	while (Q--) {
		pll v;
		cin >> v.fi >> v.se;

		auto it = PV.find(v);
		if (PV.end() != it) {
			PV.erase(it);

			upd(v.fi, v.se, -1);
		} else {
			PV.emplace(v);

			upd(v.fi, v.se, 1);
		}

		printAns();
	}

	return 0;
}