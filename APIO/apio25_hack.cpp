#include "hack.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int hack() {
	int s = (int)5e8 + 1, e = (int)1e9;
	while (s != e) {
		int m = (s + e) / 2;
		vector<lint> vect;
		int sq = (int)sqrt(m - s + 1);
		for (int i = 1; i <= sq; i++)
			vect.push_back(i);
		for (int i = s + sq; i <= m; i += sq)
			vect.push_back(i);
		vect.push_back(m + 1);
		if (collisions(vect))
			e = m;
		else
			s = m + 1;
	}
	for (int i = 2; i * i <= e; i++) {
		if (e % i == 0) {
			while (e % i == 0)
				e /= i;
			while (s % i == 0 && collisions(vector<lint>({1, s / i + 1})))
				s /= i;
		}
	}
	while (e>1 && s % e == 0 && collisions(vector<lint>({1, s / e + 1})))
		s /= e;

	return s;
}