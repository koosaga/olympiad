#include <bits/stdc++.h>
#include <vector>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

#include "goat.h"
// Given point set A, B, respond to query (i, j, k)
// where we find a # of points in B included in convex hull of a[i], a[j], a[k]
// coordinates in int32 range
// O(NM log (NM) + Q)
// credit: Nachia @ https://judge.yosupo.jp/submission/183555

struct CountPointsTriangle {
	using pi = array<lint, 2>;
	pi sub(pi a, pi b) { return pi{a[0] - b[0], a[1] - b[1]}; }
	lint ccw(pi a, pi b) { return a[0] * b[1] - b[0] * a[1]; }
	bool cmp(pi a, pi b) { return pi{a[1], a[0]} < pi{b[1], b[0]}; }
	vector<pi> A, B;
	vector<int> pointL, pointM;
	vector<vector<int>> edgeL, edgeM;
	void init(vector<pi> a, vector<pi> b) {
		A = a, B = b;
		int N = sz(A), M = sz(B);
		pointL = vector<int>(N); // bx < Ax
		pointM = vector<int>(N); // bx = Ax
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (A[i][1] == B[j][1]) {
					if (B[j][0] < A[i][0])
						pointL[i]++;
					if (B[j][0] == A[i][0])
						pointM[i]++;
				}
			}
		}
		edgeL = vector<vector<int>>(N, vector<int>(N)); // bx < lerp(Ax, Bx)
		edgeM = vector<vector<int>>(N, vector<int>(N)); // bx = lerp(Ax, Bx)
		for (int a = 0; a < N; a++) {
			struct PointId {
				int i;
				int c;
				pi v;
			};
			vector<PointId> points;
			for (int b = 0; b < N; b++)
				if (A[a][1] < A[b][1])
					points.push_back({b, 0, sub(A[b], A[a])});
			for (int b = 0; b < M; b++)
				if (A[a][1] < B[b][1])
					points.push_back({b, 1, sub(B[b], A[a])});
			for (int b = 0; b < N; b++)
				if (A[a][1] < A[b][1])
					points.push_back({b, 2, sub(A[b], A[a])});
			sort(points.begin(), points.end(), [&](const PointId &l, const PointId &r) {
				lint det = ccw(l.v, r.v);
				if (det != 0)
					return det < 0;
				return l.c < r.c;
			});
			int qN = points.size();
			vector<int> queryOrd(qN);
			iota(queryOrd.begin(), queryOrd.end(), 0);
			sort(queryOrd.begin(), queryOrd.end(), [&](int l, int r) { return make_pair(points[l].v[1], points[l].c % 2) < make_pair(points[r].v[1], points[r].c % 2); });
			vector<int> BIT(qN);
			for (int qi = 0; qi < qN; qi++) {
				int q = queryOrd[qi];
				if (points[q].c == 0) {
					int buf = 0;
					int p = q + 1;
					while (p > 0) {
						buf += BIT[p - 1];
						p -= p & -p;
					}
					edgeL[a][points[q].i] = buf;
				} else if (points[q].c == 1) {
					int p = q + 1;
					while (p <= qN) {
						BIT[p - 1]++;
						p += p & -p;
					}
				} else {
					int buf = 0;
					int p = q + 1;
					while (p > 0) {
						buf += BIT[p - 1];
						p -= p & -p;
					}
					edgeM[a][points[q].i] = buf;
				}
			}
			for (int b = 0; b < N; b++)
				edgeM[a][b] -= edgeL[a][b];
		}
	}
	// count_borders
	int query(int a, int b, int c, bool count_borders = false) {
		if (cmp(A[b], A[a]))
			swap(a, b);
		if (cmp(A[c], A[b]))
			swap(b, c);
		if (cmp(A[b], A[a]))
			swap(a, b);
		// c   ^y
		// b   |
		// a   +---> x

		//      c
		// nega |
		//      v posi
		//      a
		auto det = ccw(sub(A[a], A[c]), sub(A[b], A[c]));
		int ans = 0;
		if (det != 0) {
			if (A[a][1] == A[b][1]) { // A[a][0] < A[b][0]
				//   c
				// a   b
				ans = edgeL[b][c] - (edgeL[a][c] + edgeM[a][c]);
				if (count_borders) {
					ans += edgeM[b][c] + (pointL[b] - pointL[a] - pointM[a]) + edgeM[a][c] + pointM[a] + pointM[b] + pointM[c];
				}
			} else if (A[b][1] == A[c][1]) { // A[b][0] < A[c][0]
				// b   c
				//   a
				ans = edgeL[a][c] - (edgeL[a][b] + edgeM[a][b]);
				if (count_borders) {
					ans += edgeM[a][b] + (pointL[c] - pointL[b] - pointM[b]) + edgeM[a][c] + pointM[a] + pointM[b] + pointM[c];
				}
			} else if (det < 0) {
				//    c
				// b
				//    a
				ans += edgeL[a][c];
				ans -= edgeL[b][c] + edgeM[b][c];
				ans -= edgeL[a][b] + edgeM[a][b];
				ans -= pointL[b] + pointM[b];
				if (count_borders) {
					ans += edgeM[a][b] + edgeM[b][c] + edgeM[a][c] + pointM[a] + pointM[b] + pointM[c];
				}
			} else {
				// c
				//    b
				// a
				ans += edgeL[a][b];
				ans += edgeL[b][c];
				ans += pointL[b];
				ans -= edgeL[a][c] + edgeM[a][c];
				if (count_borders) {
					ans += edgeM[a][b] + edgeM[b][c] + edgeM[a][c] + pointM[a] + pointM[b] + pointM[c];
				}
			}
		} else if (det == 0 && count_borders) {
			if (A[a][1] == A[c][1])
				return pointL[c] - pointL[a] + pointM[c];
			else
				return edgeM[a][c] + pointM[c] + pointM[a];
		}
		return ans;
	}
} ds;

void init(std::vector<int> X, std::vector<int> Y) {
	vector<pi> a, b;
	for (int i = 0; i < sz(X); i++) {
		a.push_back({X[i], Y[i]});
	}
	b = a;
	ds.init(a, b);
}

int count(int A, int B, int C) { return ds.query(A, B, C, true); }
