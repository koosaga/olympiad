#include "migrations.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 10000;

vector<int> gph[MAXN];
int dep[MAXN];

pi dfs(int x, int p = -1) {
	pi ans{0, x};
	for (auto &y : gph[x]) {
		if (y != p) {
			dep[y] = dep[x] + 1;
			auto dis = dfs(y, x);
			dis[0]++;
			ans = max(ans, dis);
		}
	}
	return ans;
}

int u, v, d;
queue<pi> que;
vector<int> ucand, vcand;

static const string T[5] = {"00 01 10 11 0C 1C C0 C1 0A CA", "22 20 2A 2C A2 AC C0 A0 C2 CA", "02 0B 0C 1C 12 1A C2 CA CB CB", "21 2C 1B 2B AB CB 1C AC C1 C1", "A1 AC B0 B1 B2 BC C0 C1 C2 C2"};
static const string P = "012ABCD";

void filt(vector<int> &v, int m, int d) {
	vector<int> w;
	for (int i = m; i < sz(v); i += d) {
		w.push_back(v[i]);
	}
	v = w;
}

int pack() {
	if (u % 30 > v % 30)
		swap(u, v);
	int t = 0;
	for (int i = 0; i < 30; i++) {
		for (int j = i; j < 30; j++) {
			if (u % 30 == i && v % 30 == j) {
				filt(ucand, i, 30);
				filt(vcand, j, 30);
				return t;
			}
			t++;
		}
	}
	assert(0);
}

void unpack(int t) {
	for (int i = 0; i < 30; i++) {
		for (int j = i; j < 30; j++) {
			if (t == 0) {
				filt(ucand, i, 30);
				filt(vcand, j, 30);
				return;
			}
			t--;
		}
	}
	assert(0);
}

int X, Y;

vector<string> GEN() {
	string c1 = T[X].substr(6 * Y, 2);
	string c2 = T[X].substr(6 * Y + 3, 2);
	vector<string> pat = {c1, c2};
	if (c1[0] == c2[0]) {
		pat.push_back(string({c1[0], 'D'}));
		pat.push_back(string({'D', c1[1]}));
		pat.push_back(string({'D', c2[1]}));
	} else {
		pat.push_back(string({c1[0], 'D'}));
		pat.push_back(string({c2[0], 'D'}));
		pat.push_back(string({'D', c1[1]}));
	}
	return pat;
}

void dbg() {
	return;
	cout << "(u, v) " << u << " " << v << endl;
	cout << "ucand : ";
	for (auto &x : ucand)
		cout << x << " ";
	cout << endl;
	cout << "vcand : ";
	for (auto &x : vcand)
		cout << x << " ";
	cout << endl;
}

int send_message(int N, int i, int Pi) {
	auto norm = [&](string s) {
		if (s[0] >= 'A' && s[1] >= 'A')
			sort(all(s));
		return s;
	};
	gph[Pi].push_back(i);
	gph[i].push_back(Pi);
	if (i == N - 149) {
		u = dfs(0)[1];
		auto fuck = dfs(u);
		d = fuck[0];
		v = fuck[1];
		cr(ucand, N - 148);
		cr(vcand, N - 148);
		iota(all(ucand), 0);
		iota(all(vcand), 0);
		que.push({116, pack()});
		dbg();
	}
	if (i > N - 149) {
		ucand.push_back(i);
		vcand.push_back(i);
		dep[i] = 0;
		dfs(i);
		if (dep[u] > dep[v]) {
			if (dep[u] > d) {
				v = i;
				d = dep[u];
			}
		} else if (dep[v] > d) {
			u = i;
			d = dep[v];
		}
	}
	auto go = [&](int A) {
		int D = (int)round(sqrt(4 * A + 1));
		int p1 = find(all(ucand), u) - ucand.begin();
		int p2 = find(all(vcand), v) - vcand.begin();
		p1 %= D;
		p2 %= D;
		filt(ucand, p1, D);
		filt(vcand, p2, D);
		que.push({A, p1 * D + p2});
		dbg();
	};
	if (i == N - 33)
		go(20);
	if (i == N - 13)
		go(6);
	if (i == N - 7)
		go(2);
	if (i == N - 5) {
		go(2);
		assert(sz(ucand) <= 3);
		assert(sz(vcand) <= 3);
		while (sz(ucand) < 3)
			ucand.push_back(-1);
		while (sz(vcand) < 3)
			vcand.push_back(-1);
		dbg();
	}
	if (i == N - 3) {
		int p1 = find(all(ucand), u) - ucand.begin();
		int p2 = find(all(vcand), v) - vcand.begin();
		string s;
		s.push_back(P[p1]);
		s.push_back(P[p2]);
		s = norm(s);

		for (int i = 0; i < 5; i++) {
			if (T[i].find(s) != string::npos) {
				X = i;
				break;
			}
		}
		que.push({1, X});
	}
	if (i == N - 2) {
		int p1 = find(all(ucand), u) - ucand.begin();
		int p2 = find(all(vcand), v) - vcand.begin();
		string s;
		s.push_back(P[p1]);
		s.push_back(P[p2]);
		s = norm(s);
		for (int i = 0; i < 10; i++) {
			if (norm(T[X].substr(3 * i, 2)) == s) {
				Y = i / 2;
				break;
			}
		}
		que.push({1, Y});
	}
	if (i == N - 1) {
		vector<string> pat = GEN();
		string s;
		int p1 = find(all(ucand), u) - ucand.begin();
		int p2 = find(all(vcand), v) - vcand.begin();
		s.push_back(P[p1]);
		s.push_back(P[p2]);
		dbg();
		int pos = -1;
		for (int i = 0; i < 5; i++) {
			if (norm(s) == norm(pat[i])) {
				pos = i;
			}
		}
		assert(0 <= pos && pos <= 4);
		que.push({1, pos});
	}
	if (sz(que) == 0)
		return 0;
	auto tp = que.front();
	que.front()[0]--;
	que.front()[1] -= 4;
	if (que.front()[0] == 0)
		que.pop();
	if (tp[1] > 0 && tp[1] <= 4)
		return tp[1];
	else
		return 0;
}

pair<int, int> longest_path(vector<int> S) {
	auto decode = [&](int x, int l) {
		for (int j = x; j < x + l; j++) {
			if (S[j])
				return (j - x) * 4 + S[j];
		}
		return 0;
	};
	auto go = [&](int x, int A) {
		int val = decode(x, A);
		int D = (int)round(sqrt(4 * A + 1));
		int p1 = val / D;
		int p2 = val % D;
		filt(ucand, p1, D);
		filt(vcand, p2, D);
		for (int j = x; j < x + A; j++) {
			ucand.push_back(j + 1);
			vcand.push_back(j + 1);
		}
	};
	int N = 10000;
	cr(ucand, N - 148);
	cr(vcand, N - 148);
	iota(all(ucand), 0);
	iota(all(vcand), 0);
	unpack(decode(N - 149, 116));
	for (int j = N - 148; j < N - 32; j++) {
		ucand.push_back(j);
		vcand.push_back(j);
	}
	go(N - 33, 20);
	go(N - 13, 6);
	go(N - 7, 2);
	go(N - 5, 2);
	assert(sz(ucand) <= 5);
	assert(sz(vcand) <= 5);
	while (sz(ucand) < 5) {
		ucand.insert(ucand.end() - 2, -1);
	}
	while (sz(vcand) < 5) {
		vcand.insert(vcand.end() - 2, -1);
	}
	ucand.push_back(N - 2);
	ucand.push_back(N - 1);
	vcand.push_back(N - 2);
	vcand.push_back(N - 1);
	X = S[N - 3];
	Y = S[N - 2];
	auto ans = GEN()[S[N - 1]];
	int p1 = ucand[find(all(P), ans[0]) - P.begin()];
	int p2 = vcand[find(all(P), ans[1]) - P.begin()];
	return make_pair(p1, p2);
}