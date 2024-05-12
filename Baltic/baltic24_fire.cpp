#include <algorithm>
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
#include <utility>
#include <vector>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int k, n;
vector<pi> v1, v2;
vector<pi> intv;
int suc[1000005][20];

int query(int s, int e) {
	if (s > e)
		return 0;
	s = lower_bound(intv.begin(), intv.end(), pi(s + 1, -1e9)) - intv.begin() - 1;
	if (s < 0)
		return 1e9;
	int cnt = 1;
	for (int i = 19; i >= 0; i--) {
		if (intv[suc[s][i]].second < e) {
			s = suc[s][i];
			cnt += (1 << i);
		}
	}
	if (intv[s].second >= e)
		return cnt;
	s = suc[s][0];
	cnt++;
	if (intv[s].second >= e)
		return cnt;
	return 1e9;
}

vector<int> crd;
int main() {
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		pi a;
		scanf("%d %d", &a.first, &a.second);
		crd.push_back(a.first);
		crd.push_back(a.second);
		crd.push_back(a.first + k);
		crd.push_back(a.second + k);
		a.first++;
		if (a.first <= a.second) {
			v1.push_back(a);
			a.first += k;
			a.second += k;
			v1.push_back(a);
		} else {
			a.second += k;
			v1.push_back(a);
		}
	}
	sort(crd.begin(), crd.end());
	crd.resize(unique(crd.begin(), crd.end()) - crd.begin());
	for (auto &[u, v] : v1) {
		u = lower_bound(crd.begin(), crd.end(), u - 1) - crd.begin() + 1;
		v = lower_bound(crd.begin(), crd.end(), v) - crd.begin();
	}
	sort(v1.begin(), v1.end(), [&](const pi &a, const pi &b) { return a.first == b.first ? (a.second > b.second) : (a.first < b.first); });
	for (auto &i : v1) {
		if (intv.empty() || intv.back().second < i.second) {
			intv.push_back(i);
		}
	}
	for (int i = 0; i < intv.size(); i++) {
		suc[i][0] = lower_bound(intv.begin(), intv.end(), pi(intv[i].second + 2, -1e9)) - intv.begin() - 1;
	}
	for (int j = 1; j <= 19; j++) {
		for (int i = 0; i < intv.size(); i++) {
			suc[i][j] = suc[suc[i][j - 1]][j - 1];
		}
	}
	k = crd.size() / 2;
	int ret = 1e9;
	for (int i = 1; i <= k; i++) {
		ret = min(ret, query(i, i + k - 1));
	}
	if (ret > 1e8)
		puts("-1");
	else
		printf("%d", ret);
}