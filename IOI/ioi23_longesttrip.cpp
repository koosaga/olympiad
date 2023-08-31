#include "longesttrip.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

vector<int> longest_trip(int N, int D) {
	vector<int> p1, p2;
	p1.push_back(N - 1);
	if (N % 2 == 0) {
		if (are_connected({N - 2}, {N - 1})) {
			p1.push_back(N - 2);
		} else {
			p2.push_back(N - 2);
		}
	}
	for (int i = 0; i < N - 2; i += 2) {
		if (sz(p2) == 0) {
			bool v1 = are_connected({i}, {i + 1});
			bool v2 = are_connected({p1.back()}, {i});
			bool v3 = are_connected({p1.back()}, {i + 1});
			if (v1) {
				if (v2) {
					p1.push_back(i);
					p1.push_back(i + 1);
				} else if (v3) {
					p1.push_back(i + 1);
					p1.push_back(i);
				} else {
					p2.push_back(i);
					p2.push_back(i + 1);
				}
			} else {
				if (v2) {
					p1.push_back(i);
					p2.push_back(i + 1);
				} else {
					p2.push_back(i);
					p1.push_back(i + 1);
				}
			}
		} else {
			int v = i, w = i + 1;
			bool v1 = are_connected({v}, {w});
			if (v1) {
				if (!are_connected({p1.back()}, {v}))
					swap(p1, p2);
				if (are_connected({p2.back()}, {w})) {
					p1.push_back(v);
					p1.push_back(w);
					for (int i = sz(p2) - 1; i >= 0; i--)
						p1.push_back(p2[i]);
					p2.clear();
				} else {
					p1.push_back(v);
					p1.push_back(w);
				}
			} else {
				if (!are_connected({p1.back()}, {v}))
					swap(p1, p2);
				if (are_connected({p2.back()}, {w})) {
					p1.push_back(v);
					p2.push_back(w);
				} else {
					p1.push_back(w);
					p2.push_back(v);
				}
			}
		}
	}
	if (sz(p1) < sz(p2))
		swap(p1, p2);
	if (sz(p2) == 0)
		return p1;
	if (!are_connected(p1, p2)) {
		return p1;
	}
	if ((sz(p1) <= 2 || are_connected({p1.front()}, {p1.back()})) && (sz(p2) <= 2 || are_connected({p2.front()}, {p2.back()}))) {
		int s1 = 0, e1 = sz(p1);
		int s2 = 0, e2 = sz(p2);
		while (e2 - s2 > 1) {
			int m2 = (s2 + e2) / 2;
			vector<int> q(p2.begin() + s2, p2.begin() + m2);
			if (are_connected(p1, q))
				e2 = m2;
			else
				s2 = m2;
		}
		while (e1 - s1 > 1) {
			int m1 = (s1 + e1) / 2;
			vector<int> q(p1.begin() + s1, p1.begin() + m1);
			if (are_connected(q, {p2[s2]}))
				e1 = m1;
			else
				s1 = m1;
		}
		rotate(p1.begin(), p1.begin() + s1, p1.end());
		rotate(p2.begin(), p2.begin() + s2, p2.end());
		reverse(all(p2));
		for (auto &x : p1)
			p2.push_back(x);
		return p2;
	}
	if (are_connected({p1[0]}, {p2[0]})) {
		reverse(all(p2));
		for (auto &x : p1)
			p2.push_back(x);
		return p2;
	}
	if (are_connected({p1[0]}, {p2.back()})) {
		for (auto &x : p1)
			p2.push_back(x);
		return p2;
	}
	if (are_connected({p1.back()}, {p2[0]})) {
		for (auto &x : p2)
			p1.push_back(x);
		return p1;
	}
	if (are_connected({p1.back()}, {p2.back()})) {
		reverse(all(p2));
		for (auto &x : p2)
			p1.push_back(x);
		return p1;
	}
	assert(0);
}