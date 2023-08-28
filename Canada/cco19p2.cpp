#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
typedef long long lint;
typedef pair<int, int> pi;

int n, m;
vector<string> str, ret;
vector<vector<int>> cmp, hei;

bool ok(int x, int y) { return x >= 0 && y >= 0 && x < n && y < m && !cmp[x][y] && str[x][y] == '#'; }

queue<pi> que;

void bfs(int x, int y, int c) {
	que.push(pi(x, y));
	cmp[x][y] = c;
	while (!que.empty()) {
		auto x = que.front();
		que.pop();
		for (int i = 0; i < 4; i++) {
			if (ok(x.first + dx[i], x.second + dy[i])) {
				cmp[x.first + dx[i]][x.second + dy[i]] = c;
				hei[x.first + dx[i]][x.second + dy[i]] = hei[x.first][x.second] + dx[i];
				que.push(pi(x.first + dx[i], x.second + dy[i]));
			}
		}
	}
}

vector<pi> gph[2000005];
int dis[2000005];
char buf[1000005];

int main() {
	scanf("%d %d", &n, &m);
	str.resize(n);
	ret.resize(n);
	cmp.resize(n);
	hei.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%s", buf);
		str[i] = buf;
		ret[i].resize(m);
		hei[i].resize(m);
		cmp[i].resize(m);
	}
	int cnt = 0;
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++) {
			if (!cmp[i][j] && str[i][j] == '#') {
				bfs(i, j, ++cnt);
			}
		}
	}
	for (int i = 0; i < m; i++) {
		int prv = 0, prp = 0;
		for (int j = n - 1; j >= 0; j--) {
			if (cmp[j][i] && prv != cmp[j][i]) {
				int cst = prp - j - 1;
				gph[prv].push_back(pi(cst, cmp[j][i]));
				prv = cmp[j][i];
			}
			if (cmp[j][i])
				prp = j;
		}
	}
	memset(dis, 0x3f, sizeof(dis));
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	auto enq = [&](int x, int d) {
		if (dis[x] > d) {
			dis[x] = d;
			pq.push({d, x});
		}
	};
	enq(0, n);
	while (!pq.empty()) {
		auto [d, x] = pq.top();
		pq.pop();
		if (dis[x] != d)
			continue;
		for (auto &i : gph[x]) {
			enq(i.second, dis[x] + i.first);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			ret[i][j] = '.';
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (str[i][j] == '.')
				continue;
			int cur = dis[cmp[i][j]];
			ret[i + cur][j] = '#';
		}
	}
	for (int i = 0; i < n; i++)
		puts(ret[i].c_str());
}
