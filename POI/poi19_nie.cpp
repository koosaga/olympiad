#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int ext(string s, string t, string ans) {
	vector<int> ls(sz(ans) + 1), rs(sz(ans) + 1);
	vector<int> lt(sz(ans) + 1), rt(sz(ans) + 1);
	{
		int j = 0;
		for (int i = 0; i < sz(ans); i++) {
			while (j < sz(s) && s[j] != ans[i])
				j++;
			ls[i + 1] = ++j;
		}
	}
	{
		int j = 0;
		for (int i = 0; i < sz(ans); i++) {
			while (j < sz(t) && t[j] != ans[i])
				j++;
			lt[i + 1] = ++j;
		}
	}
	{
		int j = sz(s);
		rs.back() = j;
		for (int i = sz(ans) - 1; i >= 0; i--) {
			while (j > 0 && s[j - 1] != ans[i])
				j--;
			rs[i] = --j;
		}
	}
	{
		int j = sz(t);
		rt.back() = j;
		for (int i = sz(ans) - 1; i >= 0; i--) {
			while (j > 0 && t[j - 1] != ans[i])
				j--;
			rt[i] = --j;
		}
	}
	int cnt[256][2] = {};
	int l[2] = {}, r[2] = {};
	for (int i = 0; i <= sz(ans); i++) {
		while (l[0] < ls[i]) {
			cnt[s[l[0]]][0]--;
			l[0]++;
		}
		while (r[0] < rs[i]) {
			cnt[s[r[0]]][0]++;
			r[0]++;
		}
		while (l[1] < lt[i]) {
			cnt[t[l[1]]][1]--;
			l[1]++;
		}
		while (r[1] < rt[i]) {
			cnt[t[r[1]]][1]++;
			r[1]++;
		}
		for (int i = 65; i <= 122; i++) {
			if (cnt[i][0] && cnt[i][1])
				return false;
		}
	}
	return true;
}

const string pat = "ACGT";
int ch2i(char c) { return find(all(pat), c) - pat.begin(); }

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s[2];
	cin >> s[0] >> s[1];
	vector<array<int, 4>> idx[2];
	vector<int> put[2], nxt[2];
	for (int i = 0; i < 2; i++) {
		idx[i].resize(sz(s[i]) + 1);
		fill(all(idx[i][sz(s[i])]), sz(s[i]));
		for (int j = sz(s[i]) - 1; j >= 0; j--) {
			idx[i][j] = idx[i][j + 1];
			idx[i][j][ch2i(s[i][j])] = j;
		}
	}
	for (int it = 0; it < 10; it++) {
		nxt[0].clear();
		nxt[1].clear();
		put[0].push_back(sz(s[0]));
		put[1].push_back(sz(s[1]));
		int i = 0, j = 0;
		for (int x = 0; x < sz(put[0]); x++) {
			while (i < put[0][x] && j < put[1][x]) {
				pi toadd = pi{int(1e9), -1};
				for (int k = 0; k < 4; k++) {
					int n1 = idx[0][i][k];
					int n2 = idx[1][j][k];
					if (n1 >= put[0][x] || n2 >= put[1][x])
						continue;
					toadd = min(toadd, pi{n1, k});
				}
				if (toadd[1] == -1)
					break;
				i = idx[0][i][toadd[1]] + 1;
				j = idx[1][j][toadd[1]] + 1;
				nxt[0].push_back(i - 1);
				nxt[1].push_back(j - 1);
			}
			if (x + 1 < sz(put[0])) {
				int ch = ch2i(s[0][put[0][x]]);
				i = idx[0][i][ch] + 1;
				j = idx[1][j][ch] + 1;
				nxt[0].push_back(i - 1);
				nxt[1].push_back(j - 1);
			}
		}
		put[0] = nxt[0];
		put[1] = nxt[1];
		for (int i = 0; i < 2; i++) {
			int ptr = sz(s[i]);
			vector<int> v(sz(put[i]));
			for (int j = sz(put[i]) - 1; j >= 0; j--) {
				char ch = s[i][put[i][j]];
				while (ptr > 0 && s[i][ptr - 1] != ch)
					ptr--;
				v[j] = --ptr;
			}
			put[i] = v;
		}
	}
	string ans;
	for (int i = 0; i < sz(put[0]); i++)
		ans.push_back(s[0][put[0][i]]);
	cout << ans << "\n";
}