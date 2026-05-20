#include <bits/stdc++.h>

using namespace std;

using lint = long long;

const int MOD = int(1e9) + 7;

const int N_ = 305;

vector<int> gph[N_];
int N;
int B[N_];
int root;

const int INVX = 300;
int _inv[INVX + 2];

int inv (int x) {
	if(x <= INVX) return _inv[x];
	return lint(MOD - MOD / x) * inv(MOD % x) % MOD;
}

struct state {
	vector<int> coef;
	int r;
	state() : coef(), r(int(2e9)) { }
	state(int b) : coef(1, inv(b)), r(b) { }
	state operator* (const state &p) const {
		state ret;
		ret.coef.resize(coef.size() + p.coef.size() - 1);
		for(int i = 0; i < int(coef.size()); i++) {
			for(int j = 0; j < int(p.coef.size()); j++) {
				(ret.coef[i + j] += (lint)coef[i] * p.coef[j] % MOD) %= MOD;
			}
		}
		ret.r = min(r, p.r);
		return ret;
	}
	
};

state tb[N_];

void dfs (int u) {
	state now(B[u]);
	for(int v : gph[u]) {
		dfs(v);
		now = now * tb[v];
	}
	/*
	printf("u = %d: %d\n", u, now.r);
	for(int x : now.coef) printf(", %d", x);
	puts("");*/
	
	state ret;
	ret.coef.resize(now.coef.size() + 1);
	for(int i = 0; i < now.coef.size(); i++) {
		ret.coef[i + 1] += (lint)now.coef[i] * inv(i + 1) % MOD;
	}
	
	int sang = 0;
	for(int i = ret.coef.size(); --i >= 0; ) {
		sang = ((lint)sang * now.r + ret.coef[i]) % MOD;
		ret.coef[i] = (MOD-ret.coef[i]) % MOD;
	}
	assert(ret.coef[0] == 0);
	ret.coef[0] = sang;
	ret.r = now.r;
	tb[u] = ret;
	/*
	for(int x : ret.coef) {
		printf("%d ", x);
	}
	puts("");*/
}

/*
u = 2: 1000000000
, 857142863
1 142857144 
u = 1: 1000000000
, 857142863, 551020412
16859216 142857144 530268183 
16859216

u = 1: 2
, 500000004
1 500000003 
u = 2: 2
, 500000004
1 500000003 
u = 4: 2
, 500000004
1 500000003 
u = 5: 2
, 500000004
1 500000003 
u = 3: 1
, 1, 1000000005, 500000005, 500000003, 562500004
-4122042 1000000006 538276602 111081288 583310970 771453197 
-4122042
*/

int main() {
	_inv[1] = 1;
	for(int i = 2; i <= INVX; i++) {
		_inv[i] = lint(MOD - MOD / i) * _inv[MOD % i] % MOD;
	}
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		int p;
		scanf("%d%d", &B[i], &p);	
		if(p == 0) {
			root = i;
		}else {
			gph[p].push_back(i);
		}
	}
	
	dfs(root);
	
	printf("%d\n", tb[root].coef[0]);
	return 0;
}
