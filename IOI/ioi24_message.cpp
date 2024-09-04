#include "message.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;

void send_message(vector<bool> M, vector<bool> C) {
	vector<int> h(sz(C));
	for (int i = 0; i < sz(C); i++) {
		if (C[i] == 0) {
			for (int j = 1; j < 31; j++) {
				if (C[(i + j) % 31] == 0) {
					h[i] = j;
					break;
				}
			}
		}
	}
	int z = M.back() ^ 1;
	while (sz(M) < 1025)
		M.push_back(z);
	vector<vector<bool>> R(66, vector<bool>(31));
	int p = 0;
	for (int i = 0; i < sz(C); i++) {
		if (C[i] == 1)
			continue;
		R[h[i] - 1][i] = 1;
		for (int j = h[i]; j < 66; j++) {
			R[j][i] = M[p++];
		}
	}
	assert(p == 1025);
	for (auto &v : R)
		send_packet(v);
}

std::vector<bool> receive_message(std::vector<std::vector<bool>> R) {
	vector<int> nxt(31), goodRow(31);
	for (int i = 0; i < 31; i++) {
		int j = 0;
		while (j < sz(R) && R[j][i] == 0)
			j++;
		j++;
		nxt[i] = (i + j) % 31;
	}
	for (int i = 0; i < 31; i++) {
		int p = i;
		for (int j = 0; j < 16; j++) {
			p = nxt[p];
			if (j < 15 && p == i) {
				p = -1;
				break;
			}
		}
		if (p == i) {
			for (int j = 0; j < 16; j++) {
				goodRow[p] = 1;
				p = nxt[p];
			}
			break;
		}
	}
	assert(count(all(goodRow), 1) == 16);
	vector<bool> ans;
	for (int i = 0; i < sz(goodRow); i++) {
		if (goodRow[i] == 0)
			continue;
		int h = (nxt[i] - i + 31) % 31;
		for (int j = h; j < 66; j++) {
			ans.push_back(R[j][i]);
		}
	}
	assert(sz(ans) == 1025);
	int z = ans.back();
	while (ans.back() == z)
		ans.pop_back();
	return ans;
}