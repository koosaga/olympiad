#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000005;

int fail[MAXN], a[MAXN], b[MAXN];

int context(int x, int y){
	if(x <= y) return -1;
	return y;
}

int findP(char* text, char* patt, int n, int m){
	int mp[256];
	fill(mp, mp + 256, -1e9);
	for(int i=0; i<n; i++){
		a[i] = i - mp[text[i]];
		mp[text[i]] = i;
	}
	fill(mp, mp + 256, -1e9);
	for(int i=0; i<m; i++){
		b[i] = i - mp[patt[i]];
		mp[patt[i]] = i;
	}
	int p = 0;
	for(int i=1; i<m; i++){
		while(p && context(p + 1, b[p]) != context(p + 1, b[i])){
			p = fail[p];
		}
		if(context(p + 1, b[p]) == context(p + 1, b[i])) p++;
		fail[i + 1] = p;
	}
	p = 0;
	int dap = 0;
	for(int i=0; i<n; i++){
		while(p && context(p + 1, a[i]) != context(p + 1, b[p])) p = fail[p];
		if(context(p + 1, b[p]) == context(p + 1, a[i])) p++;
		if(p == m){
			dap++;
			p = fail[p];
		}
	}
	return dap;
}


