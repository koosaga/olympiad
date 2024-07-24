#include <algorithm>
#include <assert.h>
#include <bitset>
#include <deque>
#include <functional>
#include <iostream>
#include <limits.h>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, -1, 0, 1};

int n;
lint x[200005], y[200005], d[200005];
lint t[200005];

vector<lint> comp;

struct cls {
	int p1, p2;
	lint t;
	bool operator<(const cls &a) const { return t < a.t; }
	bool operator>(const cls &a) const { return t > a.t; }
};

struct tup {
	lint piv, pos;
	int type, idx;
	bool operator<(const tup &a) const { return pi(piv, pos) < pi(a.piv, a.pos); }
};

typedef set<tup>::iterator aauto;
set<tup> s[6];
priority_queue<cls, vector<cls>, greater<cls>> pq;

void process(int idx) {
	if (s[idx].size() < 2)
		return;
	aauto it1 = s[idx].begin(), it2 = ++s[idx].begin();
	while (it2 != s[idx].end()) {
		if (it1->type == 0 && it2->type == 1 && it1->piv == it2->piv) {
			pq.push((cls){it1->idx, it2->idx, it2->pos - it1->pos});
		}
		it1++;
		it2++;
	}
}

void remove(tup x, int idx) {
	s[idx].erase(x);
	aauto it = s[idx].lower_bound(x);
	if (it == s[idx].begin() || it == s[idx].end())
		return;
	aauto bef = it;
	bef--;
	if (bef->type == 0 && it->type == 1 && bef->piv == it->piv) {
		pq.push((cls){bef->idx, it->idx, it->pos - bef->pos});
	}
}

map<pi, int> mp;

int parse(char c) {
	if (c == 'E')
		return 0;
	if (c == 'W')
		return 2;
	if (c == 'N')
		return 1;
	return 3;
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		char dd[5];
		scanf("%lld %lld %s", &x[i], &y[i], dd);
		d[i] = parse(dd[0]);
		mp[pi(x[i], y[i])] = i;
		if (d[i] == 0 || d[i] == 1)
			s[0].insert((tup){x[i] - y[i], x[i] + y[i], d[i] != 0, i});
		if (d[i] == 0 || d[i] == 2)
			s[1].insert((tup){y[i], x[i], d[i] != 0, i});
		if (d[i] == 0 || d[i] == 3)
			s[2].insert((tup){x[i] + y[i], x[i] - y[i], d[i] != 0, i});
		if (d[i] == 1 || d[i] == 2)
			s[3].insert((tup){x[i] + y[i], x[i] - y[i], d[i] != 1, i});
		if (d[i] == 1 || d[i] == 3)
			s[4].insert((tup){x[i], y[i], d[i] != 3, i});
		if (d[i] == 2 || d[i] == 3)
			s[5].insert((tup){x[i] - y[i], x[i] + y[i], d[i] != 3, i});
	}
	for (int i = 0; i < 6; i++) {
		process(i);
	}
	while (1) {
		cls event;
		while (!pq.empty()) {
			event = pq.top();
			pq.pop();
			if (t[event.p1] || t[event.p2])
				continue;
			pq.push(event);
			break;
		}
		if (pq.empty())
			break;
		lint min_time = (event.t + 1) / 2;
		int min_pos = event.p1;
		pi grnd = pi(x[min_pos] + min_time * dx[d[min_pos]], y[min_pos] + min_time * dy[d[min_pos]]);
		for (int i = 0; i < 4; i++) {
			pi nxt = pi(grnd.first + min_time * dx[i], grnd.second + min_time * dy[i]);
			if (mp.find(nxt) != mp.end()) {
				int i = mp[nxt];
				if (!t[i] && pi(x[i] + min_time * dx[d[i]], y[i] + min_time * dy[d[i]]) == grnd) {
					t[i] = min_time;
					if (d[i] == 0 || d[i] == 1)
						remove((tup){x[i] - y[i], x[i] + y[i], d[i] != 0, i}, 0);
					if (d[i] == 0 || d[i] == 2)
						remove((tup){y[i], x[i], d[i] != 0, i}, 1);
					if (d[i] == 0 || d[i] == 3)
						remove((tup){x[i] + y[i], x[i] - y[i], d[i] != 0, i}, 2);
					if (d[i] == 1 || d[i] == 2)
						remove((tup){x[i] + y[i], x[i] - y[i], d[i] != 1, i}, 3);
					if (d[i] == 1 || d[i] == 3)
						remove((tup){x[i], y[i], d[i] != 3, i}, 4);
					if (d[i] == 2 || d[i] == 3)
						remove((tup){x[i] - y[i], x[i] + y[i], d[i] != 3, i}, 5);
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		x[i] /= 2;
		y[i] /= 2;
		if (!t[i]) {
			printf("%d\n", i + 1);
		}
	}
}
