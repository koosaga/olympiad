#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 155;
const lint inf = 1e12;

int n, s[MAXN];
lint a, b, r[MAXN];
int THR;

lint dp1[MAXN][MAXN], dp2[MAXN][MAXN];

lint f(int pos, int mine, int yours);
lint g(int pos, int mine, int yours);

lint f(int pos, int mine, int yours){ // minimizer
	if(pos == n) return mine >= THR ? -inf : inf;
	if(~dp1[pos][mine]) return dp1[pos][mine];
	return dp1[pos][mine] = min(
	max(f(pos + 1, mine, yours + s[pos]) + 1 + r[pos], 1ll)
	,
	g(pos + 1, yours, mine + s[pos]) - r[pos]
	);
}

lint g(int pos, int mine, int yours){ // maximizer
	if(pos == n) return yours >= THR ? -inf : inf;
	if(~dp2[pos][mine]) return dp2[pos][mine];
	return dp2[pos][mine] = max(
	min(-1ll, g(pos + 1, mine, yours + s[pos]) - 1 - r[pos])
	,
	f(pos + 1, yours, mine + s[pos]) + r[pos]
	);
}

bool trial(int m){
	THR = m;
	memset(dp1, -1, sizeof(dp1));
	memset(dp2, -1, sizeof(dp2));
	return f(0, 0, 0) <= a - b;
}

int main(){
	cin >> n >> a >> b;
	for(int i=0; i<n; i++) cin >> r[i] >> s[i];
	int st = 0, ed = 150;
	while(st != ed){
		int m = (st + ed + 1) / 2;
		if(trial(m)) st = m;
		else ed = m - 1;
	}
	cout << st << " " << accumulate(s, s + n, -st) << endl;
}