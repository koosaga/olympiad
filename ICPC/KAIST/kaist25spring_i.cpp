#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int M = 28;

vector<int> input() {
	string s;
	cin >> s;
	vector<int> v(sz(s));
	for (int i = 0; i < sz(v); i++)
		v[i] = s[i] - '0';
	return v;
}
lint ccw(pi a, pi b) { return a[0] * b[1] - b[0] * a[1]; }

void ainta() {
	cout << M << endl;
	int n;
	cin >> n;
	vector<array<lint, 2>> a(n);
	for (int i = 0; i < n; i++) {
		lint v[4];
		for (int j = 0; j < 4; j++)
			cin >> v[j];
		a[i] = {v[0] - v[2], v[1] - v[3]};
		if (a[i][0] < 0) {
			a[i][0] *= -1;
			a[i][1] *= -1;
		}
	}
	int m = n * (n + 1) / 2 + 1;
	vector<vector<int>> down(m);
	vector<int> h(m);
	vector<vector<int>> vect(n + 1);
	for (int i = 0; i < m; i++) {
		down[i] = input();
		for (auto &v : down[i])
			v = 1 - v;
		h[i] = count(all(down[i]), 1);
		vect[h[i]].push_back(i);
	}
	auto cmp = [&](int x, int y) {
		if (x == y)
			return false;
		vector<int> ch[2];
		for (int i = 0; i < n; i++) {
			if (down[x][i] != down[y][i])
				ch[down[x][i]].push_back(i);
		}
		return ccw(a[ch[0][0]], a[ch[1][0]]) < 0;
	};
	for (int i = 0; i <= n; i++) {
		sort(all(vect[i]), cmp);
		//		for (auto &x : vect[i])
		//		cerr << x << " ";
		//		cerr << endl;
	}
	vector<vector<int>> lo(m), hi(m);
	for (int i = 0; i < n * n; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		//		cerr << "drog " << u << " " << v << endl;
		if (h[u] > h[v])
			swap(u, v);
		hi[u].push_back(v);
		lo[v].push_back(u);
	}
	vector<int> code(m);
	for (int i = 0; i <= n; i++) {
		if (i % 4 < 2)
			continue;
		for (auto &j : vect[i])
			code[j] |= 1;
	}
	for (int i = 0; i < m; i++) {
		sort(all(lo[i]), cmp);
		sort(all(hi[i]), cmp);
	}
	vector<int> nextL(m, -1), nextR(m, -1), up(m);
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < sz(vect[i]); j++) {
			if (sz(hi[vect[i][j]]))
				nextL[vect[i][j]] = hi[vect[i][j]].back();
			if (sz(lo[vect[i][j]]))
				nextR[vect[i][j]] = lo[vect[i][j]].back();
			//		cerr << vect[i][j] << " " << nextL[vect[i][j]] << " " << nextR[vect[i][j]] << endl;
		}
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < sz(vect[i]) - 1; j++) {
			if (nextR[nextL[vect[i][j]]] == vect[i][j + 1]) {
				up[vect[i][j]] = 1;
				code[nextL[vect[i][j]]] |= 2;
			} else {
				assert(nextL[nextR[vect[i][j]]] == vect[i][j + 1]);
				code[nextR[vect[i][j]]] |= 4;
			}
		}
	}
	for (int i = 0; i <= n; i++) {
		int f = 0;
		for (int j = 0; j < sz(vect[i]); j++) {
			if (j && up[vect[i][j - 1]] != up[vect[i][j]])
				f = (f + 1) % 3;
			code[vect[i][j]] += 8 * f;
		}
	}
	code[vect[n][0]] = 27;
	code[vect[0][0]] = 26;
	for (int i = 1; i < n; i++) {
		code[vect[i][0]] = 24 + up[vect[i][0]];
	}
	for (int i = 0; i < m; i++) {
		cout << code[i] + 1 << " " << h[i] << endl;
	}
}

void report(int x) {
	assert(x != -1);
	cout << x + 1 << endl;
	int pos;
	cin >> pos;
	if (pos)
		exit(0);
	return;
}

void binta() {
	int x1, h1, x2, h2;
	int n;
	cin >> n;
	cin >> x1 >> h1 >> x2 >> h2;
	x1--;
	x2--;
	int p = 0;
	while (x1 < 24) {
		int dest = -1;
		vector<int> v = input();
		for (int j = 0; j < M; j++) {
			if (!v[j])
				continue;
			if (j >= 24)
				dest = j;
			else if ((j ^ p) & 1)
				dest = j;
		}
		report(dest);
		p = x1;
		x1 = dest;
	}
	while (x1 < 26) {
		vector<int> v = input();
		int nxt = -1;
		for (int j = 24; j < M; j++) {
			if (v[j])
				nxt = max(nxt, j);
		}
		report(nxt);
		x1 = nxt;
	}
	while (x1 != 26) {
		vector<int> v = input();
		int nxt = -1;
		for (int j = 24; j < M; j++) {
			if (v[j])
				nxt = max(nxt, j);
		}
		if (nxt == -1)
			nxt = -2;
		report(nxt);
		x1 = nxt;
	}
	assert(h2 > 0);
	for (int i = 0; i < h2; i++) {
		vector<int> v = input();
		int nxt = -1;
		for (int j = 24; j < M; j++) {
			if (v[j])
				nxt = max(nxt, j);
		}
		if (nxt == -1)
			nxt = -2;
		report(nxt);
		x1 = nxt;
	}
	// now in the head of list
	// explore everything in 2n query, i think
	bool is_up = (x1 == 25);
	while (true) {
		vector<int> v = input();
		if (is_up) {
			int to_rep = -1;
			for (int j = 0; j < 24; j++) {
				if ((j & 2) && (j % 2 == ((h2 + 1) / 2) % 2) && v[j]) {
					to_rep = j;
					break;
				}
			}
			if (to_rep == -1) {
				for (int j = 24; j < M; j++) {
					if (v[j])
						to_rep = max(to_rep, j);
				}
				if (to_rep == -1)
					to_rep = -2;
			}
			report(to_rep);
			v = input();
			for (int j = 0; j < 24; j++) {
				if ((j % 2 == ((h2) / 2) % 2) && v[j]) {
					int prev_color = (x1 / 8) % 3;
					int new_color = j / 8;
					if ((new_color - prev_color + 3) % 3 <= 1) {
						report(j);
						x1 = j;
						if (new_color != prev_color)
							is_up ^= 1;
						break;
					}
				}
			}
		} else {
			int to_rep = -1;
			for (int j = 0; j < 24; j++) {
				if ((j & 4) && (j % 2 == ((h2 - 1) / 2) % 2) && v[j]) {
					to_rep = j;
					break;
				}
			}
			if (to_rep == -1) {
				if (x1 >= 24)
					to_rep = -2;
				else {
					for (int j = 24; j < M; j++) {
						if (v[j])
							to_rep = max(to_rep, j);
					}
				}
			}
			report(to_rep);
			v = input();
			for (int j = 0; j < 24; j++) {
				if ((j % 2 == ((h2) / 2) % 2) && v[j]) {
					int prev_color = (x1 / 8) % 3;
					int new_color = j / 8;
					if ((new_color - prev_color + 3) % 3 <= 1) {
						report(j);
						x1 = j;
						if (new_color != prev_color)
							is_up ^= 1;
						break;
					}
				}
			}
		}
	}
}

int main() {
	int t;
	cin >> t;
	if (t == 0)
		ainta();
	else
		binta();
}