#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
using lint = long long;
using pi = pair<int, int>;

int n, c[MAXN];
vector<int> key_loc[MAXN];

int L[20][MAXN], R[20][MAXN];
int up[MAXN], dn[MAXN];
pi rng[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++) scanf("%d",&c[i]);
	for(int i=1; i<=n; i++){
		int x; scanf("%d",&x);
		for(int j=0; j<x; j++){
			int y; scanf("%d",&y);
			key_loc[y].push_back(i);
		}
	}
	for(int i=1; i<n; i++){
		auto p = lower_bound(key_loc[c[i]].begin(), key_loc[c[i]].end(), i + 1);
		if(p == key_loc[c[i]].end()) R[0][i] = n + 1;
		else R[0][i] = *p;
		if(p == key_loc[c[i]].begin()) L[0][i] = 0;
		else L[0][i] = *prev(p);
	}
	R[0][0] = n + 1;
	L[0][n + 1] = 0;
	for(int i=1; i<20; i++){
		for(int j=0; j<=n+1; j++){
			L[i][j] = L[i-1][j];
			R[i][j] = R[i-1][j];
			if(j >= (1 << (i - 1))){
				L[i][j] = min(L[i][j], L[i-1][j - (1 << (i-1))]);
				R[i][j] = max(R[i][j], R[i-1][j - (1 << (i-1))]);
			}
		}
	}
	memset(dn, 0x3f, sizeof(dn));
	for(int i=1; i<=n; i++){
		int pos = R[0][i - 1] - 1;
		for(int j=19; j>=0; j--){
			if(pos >= (1 << j) && L[j][pos] >= i){
				pos -= (1 << j);
			}
		}
		if(L[0][pos] >= i) pos--;
		if(pos >= i) up[i] = max(up[i], pos);
	}
	for(int i=1; i<=n; i++){
		int pos = L[0][i];
		for(int j=19; j>=0; j--){
			if(pos + (1 << j) <= n && R[j][pos + (1<<j) - 1] <= i){
				pos += (1 << j);
			}
		}
		if(R[0][pos] <= i) pos++;
		pos++;
		if(pos <= i) dn[i] = min(dn[i], pos);
	}
	vector<pi> stk;
	for(int i=1; i<=n; i++){
		while(!stk.empty() && stk.back().first <= max(i - 1, up[i])){
			stk.pop_back();
		}
		if(up[i] >= i) stk.emplace_back(up[i], i);
		if(stk.size()) rng[i].first = stk.back().second;
		else rng[i].first = 1;
	}
	stk.clear();
	for(int i=n; i; i--){
		while(!stk.empty() && stk.back().first >= min(i + 1, dn[i])){
			stk.pop_back();
		}
		if(dn[i] <= i) stk.emplace_back(dn[i], i);
		if(stk.size()) rng[i].second = stk.back().second;
		else rng[i].second = n;
	}
	int q; scanf("%d",&q);
	while(q--){
		int x, y; scanf("%d %d",&x,&y);
		puts(rng[x].first <= y && y <= rng[x].second ? "YES" : "NO");
	}
}
