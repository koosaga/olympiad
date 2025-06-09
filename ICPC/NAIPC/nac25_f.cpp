#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;

void solve(int N, int M, int U, int R, int D, int L) {
	int gauche = D + R - (M - 1);
	int droite = U + L - (N - 1);
	vector<string> ans(N, string(M, '*'));
	int px = 0, py = M - 1;
	int cur = 0;
	while (px < N - 1 || py > 0) {
		if (px < N - 1 && cur + py <= gauche) {
			cur += py;
			px++;
			ans[px][py] = 'U';
		} else {
			py--;
			ans[px][py] = 'R';
		}
	}
	assert(cur == gauche);
	assert(px == N - 1 && py == 0);
	R -= M - 1;
	U -= N - 1;
	vector<pi> points[2];
	for (int i = 0; i < N; i++) {
		int is_droite = false;
		for (int j = 0; j < M - (i == 0); j++) {
			if (ans[i][j] != '*')
				is_droite = true;
			else
				points[is_droite].push_back({i, j});
		}
	}
	assert(sz(points[0]) == gauche);
	assert(sz(points[1]) == droite);

	for (auto &[i, j] : points[0]) {
		if (D)
			ans[i][j] = 'D', D--;
		else
			ans[i][j] = 'R', R--;
	}
	for (auto &[i, j] : points[1]) {
		if (L)
			ans[i][j] = 'L', L--;
		else
			ans[i][j] = 'U', U--;
	}
	for (int i = 0; i < N; i++) {
		cout << ans[i];
		if (i + 1 < N)
			cout << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	for (int it = 0; it < t; it++) {
		int N, M, U, R, D, L;
		cin >> N >> M >> U >> R >> D >> L;
		if (R < M - 1 || U < N - 1) {
			cout << "impossible";
		} else {
			solve(N, M, U, R, D, L);
		}
		if (it < t - 1) {
			cout << "\n\n";
		}
	}
}