#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
#include "art.h"

void solve(int n){
	vector<int> p(n); iota(all(p), 1);
	vector<int> ans(n + 1);
	for(int i = 0; i < n; i++){
		ans[i] = publish(p);
		rotate(p.begin(), p.begin() + 1, p.end());
	}
	ans[n] = ans[0];
	vector<int> v(n);
	for(int i = 0; i < n; i++){
		int g = ans[i + 1] - ans[i] + (n - 1);
		v[g / 2] = i + 1;
	}
	reverse(all(v));
	answer(v);
}

